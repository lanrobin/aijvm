#include "runtime/heap.h"
#include "runtime/opcode.h"

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
// Heap
// ============================================================================

Heap::Heap(std::unique_ptr<GarbageCollector> gc)
    : gc_(std::move(gc)) {}

Heap::~Heap() = default;
Heap::Heap(Heap&&) noexcept = default;
Heap& Heap::operator=(Heap&&) noexcept = default;

JObject* Heap::allocate_object(const std::string& class_name) {
    auto obj = std::make_unique<JObject>();
    obj->class_name = class_name;
    obj->kind = ObjectKind::Instance;
    auto* ptr = obj.get();
    objects_.push_back(std::move(obj));
    return ptr;
}

JObject* Heap::allocate_primitive_array(std::uint8_t atype, std::int32_t length) {
    if (length < 0) {
        throw std::runtime_error(std::format(
            "NegativeArraySizeException: {}", length));
    }
    auto obj = std::make_unique<JObject>();
    auto len = static_cast<std::size_t>(length);
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
    objects_.push_back(std::move(obj));
    return ptr;
}

JObject* Heap::allocate_ref_array(const std::string& element_class,
                                  std::int32_t length) {
    if (length < 0) {
        throw std::runtime_error(std::format(
            "NegativeArraySizeException: {}", length));
    }
    auto obj = std::make_unique<JObject>();
    obj->class_name = "[L" + element_class + ";";
    obj->kind = ObjectKind::ArrayRef;
    obj->array_ref.resize(static_cast<std::size_t>(length), nullptr);
    auto* ptr = obj.get();
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

    // Mark well-known system classes as already initialized
    // (they don't have real <clinit> methods we can execute)
    set_class_init_state("java/lang/Object", ClassInitState::Initialized);
    set_class_init_state("java/lang/System", ClassInitState::Initialized);
    set_class_init_state("java/io/PrintStream", ClassInitState::Initialized);
    set_class_init_state("java/lang/String", ClassInitState::Initialized);
    set_class_init_state("java/lang/Class", ClassInitState::Initialized);
    set_class_init_state("java/lang/StringBuilder", ClassInitState::Initialized);
    set_class_init_state("java/lang/AbstractStringBuilder", ClassInitState::Initialized);
}

Heap::ClassInitState Heap::get_class_init_state(const std::string& class_name) const {
    auto it = class_init_states_.find(class_name);
    return it != class_init_states_.end() ? it->second : ClassInitState::Uninitialized;
}

void Heap::set_class_init_state(const std::string& class_name, ClassInitState state) {
    class_init_states_[class_name] = state;
}

} // namespace aijvm::runtime
