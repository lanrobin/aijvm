#include "runtime/frame.h"

#include <bit>
#include <format>

namespace aijvm::runtime {

Frame::Frame(std::shared_ptr<classfile::ClassFile> class_file,
             const classfile::method_info* method,
             std::uint16_t max_locals,
             std::uint16_t max_stack,
             std::span<const std::uint8_t> bytecode)
    : class_file_(std::move(class_file)),
      method_(method),
      locals_(max_locals),
      operand_stack_(max_stack),
      max_stack_(max_stack),
      bytecode_(bytecode) {}

// ===== Local Variable Access (§2.6.1) =====

static void check_local_index(std::uint16_t index, std::size_t max,
                               std::string_view op) {
    if (index >= max) {
        throw FrameError(std::format("{}: index {} out of bounds (max_locals={})",
                                     op, index, max));
    }
}

void Frame::set_local_int(std::uint16_t index, std::int32_t value) {
    check_local_index(index, locals_.size(), "set_local_int");
    locals_[index] = Slot::make_int(value);
}

void Frame::set_local_float(std::uint16_t index, float value) {
    check_local_index(index, locals_.size(), "set_local_float");
    locals_[index] = Slot::make_float(value);
}

void Frame::set_local_long(std::uint16_t index, std::int64_t value) {
    // §2.6.1: long occupies slots[index] and slots[index+1]
    check_local_index(index, locals_.size(), "set_local_long");
    if (static_cast<std::size_t>(index) + 1 >= locals_.size()) {
        throw FrameError(std::format(
            "set_local_long: index+1={} out of bounds (max_locals={})",
            index + 1, locals_.size()));
    }
    locals_[index] = Slot::make_long(value);
    locals_[index + 1] = Slot::make_empty();  // invalidate upper slot
}

void Frame::set_local_double(std::uint16_t index, double value) {
    // §2.6.1: double occupies slots[index] and slots[index+1]
    check_local_index(index, locals_.size(), "set_local_double");
    if (static_cast<std::size_t>(index) + 1 >= locals_.size()) {
        throw FrameError(std::format(
            "set_local_double: index+1={} out of bounds (max_locals={})",
            index + 1, locals_.size()));
    }
    locals_[index] = Slot::make_double(value);
    locals_[index + 1] = Slot::make_empty();  // invalidate upper slot
}

void Frame::set_local_ref(std::uint16_t index, void* value) {
    check_local_index(index, locals_.size(), "set_local_ref");
    locals_[index] = Slot::make_ref(value);
}

std::int32_t Frame::get_local_int(std::uint16_t index) const {
    check_local_index(index, locals_.size(), "get_local_int");
    if (locals_[index].type != SlotType::Int) {
        throw FrameError(std::format("get_local_int: slot {} is not Int", index));
    }
    return locals_[index].value.i;
}

float Frame::get_local_float(std::uint16_t index) const {
    check_local_index(index, locals_.size(), "get_local_float");
    if (locals_[index].type != SlotType::Float) {
        throw FrameError(std::format("get_local_float: slot {} is not Float", index));
    }
    return locals_[index].value.f;
}

std::int64_t Frame::get_local_long(std::uint16_t index) const {
    check_local_index(index, locals_.size(), "get_local_long");
    if (locals_[index].type != SlotType::Long) {
        throw FrameError(std::format("get_local_long: slot {} is not Long", index));
    }
    return locals_[index].value.l;
}

double Frame::get_local_double(std::uint16_t index) const {
    check_local_index(index, locals_.size(), "get_local_double");
    if (locals_[index].type != SlotType::Double) {
        throw FrameError(std::format("get_local_double: slot {} is not Double", index));
    }
    return locals_[index].value.d;
}

void* Frame::get_local_ref(std::uint16_t index) const {
    check_local_index(index, locals_.size(), "get_local_ref");
    if (locals_[index].type != SlotType::Reference) {
        throw FrameError(std::format("get_local_ref: slot {} is not Reference", index));
    }
    return locals_[index].value.ref;
}

// ===== Operand Stack (§2.6.2) =====

void Frame::push_int(std::int32_t value) {
    if (stack_top_ >= max_stack_) {
        throw FrameError("push_int: operand stack overflow");
    }
    operand_stack_[stack_top_++] = Slot::make_int(value);
}

void Frame::push_float(float value) {
    if (stack_top_ >= max_stack_) {
        throw FrameError("push_float: operand stack overflow");
    }
    operand_stack_[stack_top_++] = Slot::make_float(value);
}

void Frame::push_long(std::int64_t value) {
    // §2.6.2: long contributes 2 units to the operand stack depth
    if (stack_top_ + 2 > max_stack_) {
        throw FrameError("push_long: operand stack overflow");
    }
    operand_stack_[stack_top_++] = Slot::make_long(value);
    operand_stack_[stack_top_++] = Slot::make_empty();  // padding slot
}

void Frame::push_double(double value) {
    // §2.6.2: double contributes 2 units to the operand stack depth
    if (stack_top_ + 2 > max_stack_) {
        throw FrameError("push_double: operand stack overflow");
    }
    operand_stack_[stack_top_++] = Slot::make_double(value);
    operand_stack_[stack_top_++] = Slot::make_empty();  // padding slot
}

void Frame::push_ref(void* value) {
    if (stack_top_ >= max_stack_) {
        throw FrameError("push_ref: operand stack overflow");
    }
    operand_stack_[stack_top_++] = Slot::make_ref(value);
}

std::int32_t Frame::pop_int() {
    if (stack_top_ == 0) {
        throw FrameError("pop_int: operand stack underflow");
    }
    auto& slot = operand_stack_[--stack_top_];
    if (slot.type != SlotType::Int) {
        ++stack_top_;  // restore
        throw FrameError("pop_int: top of stack is not Int");
    }
    return slot.value.i;
}

float Frame::pop_float() {
    if (stack_top_ == 0) {
        throw FrameError("pop_float: operand stack underflow");
    }
    auto& slot = operand_stack_[--stack_top_];
    if (slot.type != SlotType::Float) {
        ++stack_top_;
        throw FrameError("pop_float: top of stack is not Float");
    }
    return slot.value.f;
}

std::int64_t Frame::pop_long() {
    // Pop padding slot first, then the long value
    if (stack_top_ < 2) {
        throw FrameError("pop_long: operand stack underflow");
    }
    --stack_top_;  // pop padding
    auto& slot = operand_stack_[--stack_top_];
    if (slot.type != SlotType::Long) {
        stack_top_ += 2;  // restore
        throw FrameError("pop_long: top of stack is not Long");
    }
    return slot.value.l;
}

double Frame::pop_double() {
    // Pop padding slot first, then the double value
    if (stack_top_ < 2) {
        throw FrameError("pop_double: operand stack underflow");
    }
    --stack_top_;  // pop padding
    auto& slot = operand_stack_[--stack_top_];
    if (slot.type != SlotType::Double) {
        stack_top_ += 2;  // restore
        throw FrameError("pop_double: top of stack is not Double");
    }
    return slot.value.d;
}

void* Frame::pop_ref() {
    if (stack_top_ == 0) {
        throw FrameError("pop_ref: operand stack underflow");
    }
    auto& slot = operand_stack_[--stack_top_];
    if (slot.type != SlotType::Reference) {
        ++stack_top_;
        throw FrameError("pop_ref: top of stack is not Reference");
    }
    return slot.value.ref;
}

const Slot& Frame::peek_slot(std::size_t depth) const {
    if (depth >= stack_top_) {
        throw FrameError(std::format("peek_slot: depth {} exceeds stack size {}",
                                     depth, stack_top_));
    }
    return operand_stack_[stack_top_ - 1 - depth];
}

void Frame::push_slot(const Slot& slot) {
    if (stack_top_ >= max_stack_) {
        throw FrameError("push_slot: operand stack overflow");
    }
    operand_stack_[stack_top_++] = slot;
}

Slot Frame::pop_slot() {
    if (stack_top_ == 0) {
        throw FrameError("pop_slot: operand stack underflow");
    }
    return operand_stack_[--stack_top_];
}

std::size_t Frame::stack_depth() const noexcept {
    return stack_top_;
}

bool Frame::stack_empty() const noexcept {
    return stack_top_ == 0;
}

// ===== Program Counter =====

std::uint32_t Frame::pc() const noexcept {
    return pc_;
}

void Frame::set_pc(std::uint32_t offset) {
    pc_ = offset;
}

void Frame::advance_pc(std::int32_t delta) {
    pc_ = static_cast<std::uint32_t>(static_cast<std::int64_t>(pc_) + delta);
}

std::uint8_t Frame::read_u1() {
    if (pc_ >= bytecode_.size()) {
        throw FrameError(std::format("read_u1: PC {} past end of bytecode (size={})",
                                     pc_, bytecode_.size()));
    }
    return bytecode_[pc_++];
}

std::uint16_t Frame::read_u2() {
    if (pc_ + 2 > bytecode_.size()) {
        throw FrameError(std::format("read_u2: PC {} past end of bytecode (size={})",
                                     pc_, bytecode_.size()));
    }
    // Java class files use big-endian byte order (§4.1)
    auto hi = static_cast<std::uint16_t>(bytecode_[pc_++]) << 8;
    auto lo = static_cast<std::uint16_t>(bytecode_[pc_++]);
    return hi | lo;
}

std::int16_t Frame::read_s2() {
    return static_cast<std::int16_t>(read_u2());
}

std::int32_t Frame::read_s4() {
    if (pc_ + 4 > bytecode_.size()) {
        throw FrameError(std::format("read_s4: PC {} past end of bytecode (size={})",
                                     pc_, bytecode_.size()));
    }
    auto b0 = static_cast<std::int32_t>(bytecode_[pc_++]) << 24;
    auto b1 = static_cast<std::int32_t>(bytecode_[pc_++]) << 16;
    auto b2 = static_cast<std::int32_t>(bytecode_[pc_++]) << 8;
    auto b3 = static_cast<std::int32_t>(bytecode_[pc_++]);
    return b0 | b1 | b2 | b3;
}

// ===== Constant Pool & Method Access =====

const classfile::ClassFile& Frame::get_class_file() const noexcept {
    return *class_file_;
}

const classfile::method_info& Frame::get_method() const noexcept {
    return *method_;
}

std::span<const std::uint8_t> Frame::get_bytecode() const noexcept {
    return bytecode_;
}

} // namespace aijvm::runtime
