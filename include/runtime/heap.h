#pragma once

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace aijvm::classfile {
    class ClassFile;  // forward declaration
}

namespace aijvm::runtime {

// ============================================================================
// §2.5.3 Heap — Object Representation
// ============================================================================
//
// "The Java Virtual Machine has a heap that is shared among all Java Virtual
// Machine threads. The heap is the run-time data area from which memory for
// all class instances and arrays is allocated."
//
// JObject is a minimal runtime representation of a Java object/array.
// Fields are stored as Slot-compatible values keyed by "class_name.field_name".
// Arrays store elements in a flat vector.
// ============================================================================

/// Field storage value — aligned with the JVM type system (§2.3).
/// We use a variant here (vs the Slot union) because field storage is
/// not on the interpreter hot path and benefits from type safety.
using FieldValue = std::variant<
    std::int32_t,   // int (also boolean, byte, char, short)
    std::int64_t,   // long
    float,          // float
    double,         // double
    void*           // reference (pointer to JObject)
>;

/// Tag for classifying JObject kind (instance vs primitive array vs ref array).
enum class ObjectKind : std::uint8_t {
    Instance,       ///< Regular class instance with named fields
    ArrayInt,       ///< int[]
    ArrayLong,      ///< long[]
    ArrayFloat,     ///< float[]
    ArrayDouble,    ///< double[]
    ArrayByte,      ///< byte[] (also boolean[])
    ArrayChar,      ///< char[]
    ArrayShort,     ///< short[]
    ArrayRef        ///< Object[] or any reference array
};

/// JObject: runtime representation of a Java heap object or array.
/// Per §2.5.3, all objects and arrays live on the shared heap.
struct JObject {
    /// Canonical class name (e.g. "java/lang/Object", "[I" for int[])
    std::string class_name;

    /// Instance or array discriminator
    ObjectKind kind = ObjectKind::Instance;

    /// Forwarding pointer for Cheney's semi-space copying GC.
    /// nullptr when object has not been forwarded. During GC, set to the
    /// address of the copy in to-space. After GC, all references are updated
    /// to point to the new copies and this field is reset to nullptr.
    JObject* forwarding_ptr = nullptr;

    // ----- Instance fields (ObjectKind::Instance) -----
    /// Fields keyed by "declaring_class.field_name" to handle inheritance.
    std::unordered_map<std::string, FieldValue> fields;

    // ----- Array data (ObjectKind::Array*) -----
    /// Element storage. Each variant branch holds the typed array data.
    /// Only one of these is active, determined by `kind`.
    std::vector<std::int32_t>  array_int;
    std::vector<std::int64_t>  array_long;
    std::vector<float>         array_float;
    std::vector<double>        array_double;
    std::vector<std::int8_t>   array_byte;    // also boolean
    std::vector<std::uint16_t> array_char;
    std::vector<std::int16_t>  array_short;
    std::vector<void*>         array_ref;     // references to other JObjects

    /// Get array length regardless of element type
    [[nodiscard]] std::int32_t array_length() const noexcept;

    // ----- Monitor (§8.13 / §17.1) -----
    /// Per-object recursive mutex for synchronized methods and monitorenter/monitorexit.
    std::recursive_mutex monitor;
    /// Condition variable for wait()/notify()/notifyAll()
    std::condition_variable_any monitor_cv;
};

// ============================================================================
// §2.5.3 Heap — Garbage Collector Interface
// ============================================================================
//
// "Heap storage for objects is reclaimed by an automatic storage management
// system (known as a garbage collector); objects are never explicitly
// deallocated."
//
// GarbageCollector is an abstract interface allowing pluggable GC strategies:
//   - NoOpGC: never collects (for initial development)
//   - Future: Semi-space copying collector per claude.md §4
// ============================================================================

/// Abstract GC interface — Strategy pattern for swappable collection algorithms.
class GarbageCollector {
public:
    virtual ~GarbageCollector() = default;

    /// Run a garbage collection cycle.
    /// @param roots  The set of root object pointers (from thread stacks, statics)
    virtual void collect(std::vector<JObject*>& all_objects,
                         const std::vector<JObject*>& roots) = 0;

    /// Human-readable name for logging
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
};

/// No-op GC — never collects. Used for initial development and testing.
class NoOpGC : public GarbageCollector {
public:
    void collect(std::vector<JObject*>& all_objects,
                 const std::vector<JObject*>& roots) override;
    [[nodiscard]] std::string_view name() const noexcept override;
};

/// Semi-space copying GC — Cheney's algorithm.
/// Copies live objects reachable from roots into a new vector (to-space),
/// updates all internal references via forwarding pointers, then swaps.
///
/// Since our JObject uses std::unique_ptr (not a contiguous arena), the
/// "semi-space" is conceptual: from-space is the current objects_ vector,
/// to-space is a new vector. Live objects are deep-copied; dead objects
/// are released when from-space is dropped.
class SemiSpaceGC : public GarbageCollector {
public:
    void collect(std::vector<JObject*>& all_objects,
                 const std::vector<JObject*>& roots) override;
    [[nodiscard]] std::string_view name() const noexcept override;

    /// Statistics from last collection cycle.
    std::size_t last_live_count = 0;
    std::size_t last_freed_count = 0;

    /// To-space from last collection, for Heap to adopt.
    std::vector<std::unique_ptr<JObject>> to_space_;
};

// ============================================================================
// §2.5.3 Heap — Heap Area
// ============================================================================

class Heap {
public:
    /// Construct heap with the given GC strategy and max size.
    /// @param gc        GC strategy (defaults to NoOpGC)
    /// @param max_size  Maximum heap size in bytes (for GC trigger threshold).
    ///                  0 means unlimited (no automatic GC triggering).
    explicit Heap(std::unique_ptr<GarbageCollector> gc = std::make_unique<NoOpGC>(),
                  std::size_t max_size = 0);

    ~Heap();
    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;
    Heap(Heap&&) noexcept;
    Heap& operator=(Heap&&) noexcept;

    /// Allocate a new class instance on the heap.
    /// Per §2.5.3: "The heap is the run-time data area from which memory for
    /// all class instances and arrays is allocated."
    /// @param class_name  Canonical name (e.g. "java/lang/Object")
    /// @return Non-owning pointer to the allocated object (heap retains ownership)
    JObject* allocate_object(const std::string& class_name);

    /// Allocate a primitive array (§6.5 newarray).
    /// @param atype  Array type code from ArrayType namespace (T_INT=10, etc.)
    /// @param length Number of elements
    JObject* allocate_primitive_array(std::uint8_t atype, std::int32_t length);

    /// Allocate a reference array (§6.5 anewarray).
    /// @param element_class  Element type canonical name
    /// @param length        Number of elements
    JObject* allocate_ref_array(const std::string& element_class, std::int32_t length);

    /// Trigger a GC cycle with the given root set.
    void gc(const std::vector<JObject*>& roots);

    /// Check if GC should be triggered based on object count threshold.
    /// Threshold is max_heap_size / estimated_object_size.
    [[nodiscard]] bool should_gc() const noexcept;

    /// Total number of live objects on the heap.
    [[nodiscard]] std::size_t object_count() const noexcept;

    /// Estimated total memory usage of all heap objects.
    [[nodiscard]] std::size_t estimated_memory_usage() const noexcept;

    /// Maximum heap size in bytes. 0 = unlimited.
    [[nodiscard]] std::size_t max_heap_size() const noexcept;

    // ===== §2.5.4 Method Area — Static Field Storage =====
    // "The method area stores per-class structures: run-time constant pool,
    // field and method data..." (§2.5.4)
    // We co-locate static field storage in the Heap for simplicity.

    /// Set a static field value.
    /// @param key Format: "class_name.field_name"
    void set_static_field(const std::string& key, FieldValue value);

    /// Get a static field value, or nullptr-equivalent default if not set.
    [[nodiscard]] const FieldValue* get_static_field(const std::string& key) const;

    /// Initialize well-known static fields (e.g. System.out).
    /// Called once during JVM boot.
    void init_system_classes();

    // ===== §5.5 Class Initialization State Tracking =====
    // "Initialization of a class or interface consists of executing its class
    // or interface initialization method (<clinit>)." (§5.5)
    //
    // State machine per §5.5:
    //   Uninitialized → Initializing → Initialized
    //   (Error state omitted for simplicity)

    enum class ClassInitState : std::uint8_t {
        Uninitialized,  ///< <clinit> has not been invoked
        Initializing,   ///< <clinit> is currently executing (on some thread)
        Initialized     ///< <clinit> has completed successfully
    };

    /// Get the initialization state of a class.
    [[nodiscard]] ClassInitState get_class_init_state(const std::string& class_name) const;

    /// Set the initialization state of a class.
    void set_class_init_state(const std::string& class_name, ClassInitState state);

private:
    std::vector<std::unique_ptr<JObject>> objects_;
    std::unique_ptr<GarbageCollector> gc_;
    std::size_t max_heap_size_ = 0;
    std::unordered_map<std::string, FieldValue> static_fields_;
    std::unordered_map<std::string, ClassInitState> class_init_states_;
};

} // namespace aijvm::runtime
