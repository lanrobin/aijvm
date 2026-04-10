#include "runtime/heap.h"
#include "runtime/opcode.h"
#include "utils/logger.h"

#include <algorithm>
#include <format>
#include <stdexcept>

namespace aijvm::runtime {

// ============================================================================
// JObject
// ============================================================================

std::int32_t JObject::array_length() const noexcept {
    switch (kind) {
    case ObjectKind::ArrayInt:    return static_cast<std::int32_t>(array_int.size());
    case ObjectKind::ArrayLong:   return static_cast<std::int32_t>(array_long.size());
    case ObjectKind::ArrayFloat:  return static_cast<std::int32_t>(array_float.size());
    case ObjectKind::ArrayDouble: return static_cast<std::int32_t>(array_double.size());
    case ObjectKind::ArrayByte:   return static_cast<std::int32_t>(array_byte.size());
    case ObjectKind::ArrayChar:   return static_cast<std::int32_t>(array_char.size());
    case ObjectKind::ArrayShort:  return static_cast<std::int32_t>(array_short.size());
    case ObjectKind::ArrayRef:    return static_cast<std::int32_t>(array_ref.size());
    default:                      return 0;
    }
}

std::size_t JObject::estimated_size() const noexcept {
    // Base overhead: JObject struct itself (~128 bytes for vtable-less struct
    // with string, maps, vectors, mutex, etc.) — use a conservative estimate.
    constexpr std::size_t base = 128;
    std::size_t size = base;
    // Instance field map overhead
    size += fields.size() * 64;  // rough: key string + variant per entry
    // Array data
    size += array_int.capacity() * sizeof(std::int32_t);
    size += array_long.capacity() * sizeof(std::int64_t);
    size += array_float.capacity() * sizeof(float);
    size += array_double.capacity() * sizeof(double);
    size += array_byte.capacity() * sizeof(std::int8_t);
    size += array_char.capacity() * sizeof(std::uint16_t);
    size += array_short.capacity() * sizeof(std::int16_t);
    size += array_ref.capacity() * sizeof(void*);
    return size;
}

// ============================================================================
// NoOpGC
// ============================================================================

void NoOpGC::collect([[maybe_unused]] std::vector<JObject*>& all_objects,
                     [[maybe_unused]] const std::vector<JObject*>& roots) {
    // Intentionally empty — no collection performed
}

std::string_view NoOpGC::name() const noexcept {
    return "NoOpGC";
}

// ============================================================================
// SemiSpaceGC — Cheney's Algorithm
// ============================================================================
//
// §2.5.3: "Heap storage for objects is reclaimed by an automatic storage
// management system (known as a garbage collector); objects are never
// explicitly deallocated."
//
// Algorithm:
//   1. For each root reference, copy the referenced object to to-space
//      (a new vector) and set a forwarding pointer on the from-space copy.
//   2. BFS scan: iterate over to-space objects, for each reference field,
//      copy the target if not yet forwarded, or update to the forwarded copy.
//   3. After scanning, swap to-space into the heap's objects_ vector.
//      Dead objects in from-space are released by unique_ptr destructors.
//   4. Update all external references (static fields) via forwarding pointers.
// ============================================================================

/// Deep-copy a JObject to to-space. Returns the new copy.
/// Sets forwarding_ptr on the original.
static std::unique_ptr<JObject> copy_object(JObject* from) {
    auto to = std::make_unique<JObject>();
    to->class_name = from->class_name;
    to->kind = from->kind;
    to->forwarding_ptr = nullptr;
    to->fields = from->fields;
    to->array_int = from->array_int;
    to->array_long = from->array_long;
    to->array_float = from->array_float;
    to->array_double = from->array_double;
    to->array_byte = from->array_byte;
    to->array_char = from->array_char;
    to->array_short = from->array_short;
    to->array_ref = from->array_ref;
    // Note: monitor and monitor_cv are NOT copied — new object gets fresh ones.
    // This is intentional: the old object is dead after GC.
    auto* to_ptr = to.get();
    from->forwarding_ptr = to_ptr;
    return to;
}

/// If obj has been forwarded, return the forwarded address. Otherwise,
/// copy it to to-space, set forwarding, and return the copy.
static JObject* forward_or_copy(JObject* obj,
                                std::vector<std::unique_ptr<JObject>>& to_space) {
    if (!obj) return nullptr;
    if (obj->forwarding_ptr) return obj->forwarding_ptr;
    auto copy = copy_object(obj);
    auto* result = copy.get();
    to_space.push_back(std::move(copy));
    return result;
}

/// Update a void* that might point to a JObject. If the target has been
/// forwarded, update the pointer. Otherwise, copy it.
static void update_ref(void*& ref_slot,
                       std::vector<std::unique_ptr<JObject>>& to_space) {
    if (!ref_slot) return;
    auto* obj = static_cast<JObject*>(ref_slot);
    ref_slot = forward_or_copy(obj, to_space);
}

void SemiSpaceGC::collect(std::vector<JObject*>& all_objects,
                          const std::vector<JObject*>& roots) {
    std::size_t before_count = all_objects.size();

    // To-space: the new live object set
    std::vector<std::unique_ptr<JObject>> to_space;
    to_space.reserve(before_count / 2);  // heuristic

    // Phase 1: Copy all root-reachable objects to to-space
    // The roots vector contains JObject* from thread stacks and static fields.
    // We don't own them here — the caller will update pointers via forwarding.
    for (auto* root : roots) {
        if (root) {
            (void)forward_or_copy(root, to_space);
        }
    }

    // Phase 2: BFS scan — Cheney's algorithm
    // Scan position tracks how far we've processed in to-space.
    std::size_t scan = 0;
    while (scan < to_space.size()) {
        auto* obj = to_space[scan].get();

        // Scan instance fields
        for (auto& [key, fv] : obj->fields) {
            if (auto* ref = std::get_if<void*>(&fv)) {
                update_ref(*ref, to_space);
            }
        }

        // Scan reference array elements
        if (obj->kind == ObjectKind::ArrayRef) {
            for (auto& ref : obj->array_ref) {
                update_ref(ref, to_space);
            }
        }

        ++scan;
    }

    // Phase 3: Build the new all_objects pointer list (for the Heap to swap in).
    // The actual swap of unique_ptrs is done by the Heap.
    // We store the to_space temporarily on this GC instance; the Heap will
    // call us back or we communicate via the all_objects parameter.
    //
    // Since collect() receives a reference to a raw pointer vector (not the
    // unique_ptr vector), we need to signal the Heap to do the swap.
    // We'll update the all_objects to contain the new pointers.
    all_objects.clear();
    all_objects.reserve(to_space.size());
    for (auto& obj : to_space) {
        all_objects.push_back(obj.get());
    }

    last_live_count = to_space.size();
    last_freed_count = before_count >= to_space.size() ?
                       before_count - to_space.size() : 0;

    AIJVM_LOG_INFO("SemiSpaceGC: collected {} dead objects, {} live objects remain",
                   last_freed_count, last_live_count);

    // Stash to_space for the Heap to adopt (via swap in gc() method).
    // We use a small trick: store in a thread-local or member.
    // For simplicity: use a member that Heap::gc() reads after collect().
    to_space_ = std::move(to_space);
}

std::string_view SemiSpaceGC::name() const noexcept {
    return "SemiSpaceGC";
}

// ============================================================================
// Heap
// ============================================================================

Heap::Heap(std::unique_ptr<GarbageCollector> gc, std::size_t max_size)
    : gc_(std::move(gc)), max_heap_size_(max_size) {}

Heap::~Heap() = default;
Heap::Heap(Heap&&) noexcept = default;
Heap& Heap::operator=(Heap&&) noexcept = default;

JObject* Heap::allocate_object(const std::string& class_name) {
    check_heap_pressure(128);
    auto obj = std::make_unique<JObject>();
    obj->class_name = class_name;
    obj->kind = ObjectKind::Instance;
    auto* ptr = obj.get();
    current_usage_ += ptr->estimated_size();
    objects_.push_back(std::move(obj));
    return ptr;
}

JObject* Heap::allocate_primitive_array(std::uint8_t atype, std::int32_t length) {
    if (length < 0) {
        throw std::runtime_error(std::format(
            "NegativeArraySizeException: {}", length));
    }
    // Estimate allocation size for heap pressure check
    auto len = static_cast<std::size_t>(length);
    std::size_t elem_size = 1;  // default for byte
    switch (atype) {
    case ArrayType::T_CHAR: case ArrayType::T_SHORT: elem_size = 2; break;
    case ArrayType::T_INT: case ArrayType::T_FLOAT: elem_size = 4; break;
    case ArrayType::T_LONG: case ArrayType::T_DOUBLE: elem_size = 8; break;
    default: break;
    }
    check_heap_pressure(128 + len * elem_size);
    auto obj = std::make_unique<JObject>();
    switch (atype) {
    case ArrayType::T_BOOLEAN:
    case ArrayType::T_BYTE:
        obj->class_name = "[B";
        obj->kind = ObjectKind::ArrayByte;
        obj->array_byte.resize(len, 0);
        break;
    case ArrayType::T_CHAR:
        obj->class_name = "[C";
        obj->kind = ObjectKind::ArrayChar;
        obj->array_char.resize(len, 0);
        break;
    case ArrayType::T_SHORT:
        obj->class_name = "[S";
        obj->kind = ObjectKind::ArrayShort;
        obj->array_short.resize(len, 0);
        break;
    case ArrayType::T_INT:
        obj->class_name = "[I";
        obj->kind = ObjectKind::ArrayInt;
        obj->array_int.resize(len, 0);
        break;
    case ArrayType::T_LONG:
        obj->class_name = "[J";
        obj->kind = ObjectKind::ArrayLong;
        obj->array_long.resize(len, 0);
        break;
    case ArrayType::T_FLOAT:
        obj->class_name = "[F";
        obj->kind = ObjectKind::ArrayFloat;
        obj->array_float.resize(len, 0.0f);
        break;
    case ArrayType::T_DOUBLE:
        obj->class_name = "[D";
        obj->kind = ObjectKind::ArrayDouble;
        obj->array_double.resize(len, 0.0);
        break;
    default:
        throw std::runtime_error(std::format(
            "Invalid newarray atype: {}", atype));
    }
    auto* ptr = obj.get();
    current_usage_ += ptr->estimated_size();
    objects_.push_back(std::move(obj));
    return ptr;
}

JObject* Heap::allocate_ref_array(const std::string& element_class,
                                  std::int32_t length) {
    if (length < 0) {
        throw std::runtime_error(std::format(
            "NegativeArraySizeException: {}", length));
    }
    check_heap_pressure(128 + static_cast<std::size_t>(length) * sizeof(void*));
    auto obj = std::make_unique<JObject>();
    obj->class_name = "[L" + element_class + ";";
    obj->kind = ObjectKind::ArrayRef;
    obj->array_ref.resize(static_cast<std::size_t>(length), nullptr);
    auto* ptr = obj.get();
    current_usage_ += ptr->estimated_size();
    objects_.push_back(std::move(obj));
    return ptr;
}

void Heap::gc(const std::vector<JObject*>& roots) {
    std::vector<JObject*> raw_ptrs;
    raw_ptrs.reserve(objects_.size());
    for (auto& o : objects_) {
        raw_ptrs.push_back(o.get());
    }
    gc_->collect(raw_ptrs, roots);

    // If the GC is SemiSpaceGC, adopt the new to-space and update static fields
    if (auto* ssgc = dynamic_cast<SemiSpaceGC*>(gc_.get())) {
        // Swap objects_ with the to-space (old objects_ will be dropped)
        objects_ = std::move(ssgc->to_space_);

        // Update static field references via forwarding pointers
        for (auto& [key, fv] : static_fields_) {
            if (auto* ref = std::get_if<void*>(&fv)) {
                if (*ref) {
                    auto* obj = static_cast<JObject*>(*ref);
                    if (obj->forwarding_ptr) {
                        *ref = obj->forwarding_ptr;
                    }
                }
            }
        }
    }

    // Record object count after GC to prevent re-triggering without new allocations
    last_gc_object_count_ = objects_.size();

    // Recompute actual memory usage after GC
    current_usage_ = 0;
    for (auto& o : objects_) {
        current_usage_ += o->estimated_size();
    }
}

bool Heap::should_gc() const noexcept {
    if (max_heap_size_ == 0) return false;
    // Don't re-trigger if no new allocations since last GC
    if (objects_.size() == last_gc_object_count_) return false;
    return current_usage_ > max_heap_size_ / 2;
}

std::size_t Heap::estimated_memory_usage() const noexcept {
    return current_usage_;
}

std::size_t Heap::max_heap_size() const noexcept {
    return max_heap_size_;
}

std::size_t Heap::object_count() const noexcept {
    return objects_.size();
}

void Heap::set_static_field(const std::string& key, FieldValue value) {
    static_fields_[key] = std::move(value);
}

const FieldValue* Heap::get_static_field(const std::string& key) const {
    auto it = static_fields_.find(key);
    return it != static_fields_.end() ? &it->second : nullptr;
}

void Heap::init_system_classes() {
    // Create System.out — a sentinel PrintStream object
    auto* out_stream = allocate_object("java/io/PrintStream");
    set_static_field("java/lang/System.out", static_cast<void*>(out_stream));

    // Create System.err — same as out for now
    auto* err_stream = allocate_object("java/io/PrintStream");
    set_static_field("java/lang/System.err", static_cast<void*>(err_stream));
}

void Heap::set_gc_trigger(GcTriggerFn fn) {
    gc_trigger_fn_ = std::move(fn);
}

void Heap::check_heap_pressure(std::size_t alloc_size) {
    if (max_heap_size_ == 0) return;  // unlimited heap

    if (current_usage_ + alloc_size > max_heap_size_ / 2) {
        // Attempt GC if possible (have a trigger callback and new allocs since last GC)
        if (gc_trigger_fn_ && objects_.size() != last_gc_object_count_) {
            AIJVM_LOG_INFO("Heap pressure: usage={}B + alloc={}B > threshold={}B, triggering GC",
                           current_usage_, alloc_size, max_heap_size_ / 2);
            gc_trigger_fn_();
        }

        // After GC (or if no GC was possible), check hard limit
        if (current_usage_ + alloc_size > max_heap_size_) {
            throw std::runtime_error(std::format(
                "OutOfMemoryError: Java heap space (used={}B, alloc={}B, max={}B)",
                current_usage_, alloc_size, max_heap_size_));
        }
    }
}

} // namespace aijvm::runtime
