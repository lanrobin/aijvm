#include "runtime/slot.h"

namespace aijvm::runtime {

Slot Slot::make_int(std::int32_t v) noexcept {
    Slot s;
    s.type = SlotType::Int;
    s.value.i = v;
    return s;
}

Slot Slot::make_float(float v) noexcept {
    Slot s;
    s.type = SlotType::Float;
    s.value.f = v;
    return s;
}

Slot Slot::make_long(std::int64_t v) noexcept {
    Slot s;
    s.type = SlotType::Long;
    s.value.l = v;
    return s;
}

Slot Slot::make_double(double v) noexcept {
    Slot s;
    s.type = SlotType::Double;
    s.value.d = v;
    return s;
}

Slot Slot::make_ref(void* v) noexcept {
    Slot s;
    s.type = SlotType::Reference;
    s.value.ref = v;
    return s;
}

Slot Slot::make_return_address(std::uint32_t addr) noexcept {
    Slot s;
    s.type = SlotType::ReturnAddress;
    s.value.ret_addr = addr;
    return s;
}

Slot Slot::make_empty() noexcept {
    return Slot{};
}

bool Slot::is_category2() const noexcept {
    return type == SlotType::Long || type == SlotType::Double;
}

bool Slot::is_empty() const noexcept {
    return type == SlotType::Empty;
}

} // namespace aijvm::runtime
