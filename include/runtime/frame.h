#pragma once

#include "runtime/slot.h"
#include "classfile/class_file.h"

#include <cstdint>
#include <memory>
#include <span>
#include <stdexcept>
#include <vector>

namespace aijvm::runtime {

/// Exception thrown on frame-level errors: stack overflow/underflow, type mismatch,
/// out-of-bounds local variable access, or invalid PC.
class FrameError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

// ============================================================================
// §2.6 Frames
// ============================================================================
//
// "A frame is used to store data and partial results, as well as to perform
// dynamic linking, return values for methods, and dispatch exceptions."
//
// Each frame contains:
//   1. Local Variable Array (§2.6.1) — sized by max_locals from Code attribute
//   2. Operand Stack (§2.6.2) — LIFO, max depth from Code attribute
//   3. Reference to run-time constant pool (§2.6.3) — via ClassFile
//   4. Program counter — bytecode offset within this method's Code
// ============================================================================

class Frame {
public:
    /// Construct a frame for a method invocation.
    /// @param class_file  ClassFile for constant pool access (§2.6.3)
    /// @param method      The method being invoked (non-owning)
    /// @param max_locals  Local variable array size (from Code attribute §4.7.3)
    /// @param max_stack   Maximum operand stack depth (from Code attribute §4.7.3)
    /// @param bytecode    View of the method's bytecode instructions
    Frame(std::shared_ptr<classfile::ClassFile> class_file,
          const classfile::method_info* method,
          std::uint16_t max_locals,
          std::uint16_t max_stack,
          std::span<const std::uint8_t> bytecode);

    // Non-copyable, moveable
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    Frame(Frame&&) noexcept = default;
    Frame& operator=(Frame&&) noexcept = default;
    ~Frame() = default;

    // ===== Local Variable Access (§2.6.1) =====
    // "A value of type long or double occupies two consecutive local variables.
    //  Such a value may only be addressed using the lesser index."

    void set_local_int(std::uint16_t index, std::int32_t value);
    void set_local_float(std::uint16_t index, float value);
    void set_local_long(std::uint16_t index, std::int64_t value);   // invalidates [index+1]
    void set_local_double(std::uint16_t index, double value);       // invalidates [index+1]
    void set_local_ref(std::uint16_t index, void* value);

    [[nodiscard]] std::int32_t  get_local_int(std::uint16_t index) const;
    [[nodiscard]] float         get_local_float(std::uint16_t index) const;
    [[nodiscard]] std::int64_t  get_local_long(std::uint16_t index) const;
    [[nodiscard]] double        get_local_double(std::uint16_t index) const;
    [[nodiscard]] void*         get_local_ref(std::uint16_t index) const;

    // ===== Operand Stack (§2.6.2) =====
    // "Each operand stack has a maximum depth, determined at compile time."
    // "Where an entry on the operand stack (or in a local variable) of type long
    //  or double, it contributes two units to the indices."

    void push_int(std::int32_t value);
    void push_float(float value);
    void push_long(std::int64_t value);     // counts as 2 depth units
    void push_double(double value);         // counts as 2 depth units
    void push_ref(void* value);

    [[nodiscard]] std::int32_t  pop_int();
    [[nodiscard]] float         pop_float();
    [[nodiscard]] std::int64_t  pop_long();
    [[nodiscard]] double        pop_double();
    [[nodiscard]] void*         pop_ref();

    /// Raw slot access for stack manipulation instructions (dup, swap, etc.)
    [[nodiscard]] const Slot& peek_slot(std::size_t depth = 0) const;
    void push_slot(const Slot& slot);
    Slot pop_slot();

    /// Current operand stack depth (category 2 types count as 2 units)
    [[nodiscard]] std::size_t stack_depth() const noexcept;

    /// Check if operand stack is empty
    [[nodiscard]] bool stack_empty() const noexcept;

    // ===== Program Counter =====

    [[nodiscard]] std::uint32_t pc() const noexcept;
    void set_pc(std::uint32_t offset);
    void advance_pc(std::int32_t delta);

    /// Sequential bytecode readers — read and advance PC
    [[nodiscard]] std::uint8_t  read_u1();
    [[nodiscard]] std::uint16_t read_u2();
    [[nodiscard]] std::int16_t  read_s2();
    [[nodiscard]] std::int32_t  read_s4();

    // ===== Constant Pool & Method Access (§2.6.3) =====

    [[nodiscard]] const classfile::ClassFile& get_class_file() const noexcept;
    [[nodiscard]] const classfile::method_info& get_method() const noexcept;
    [[nodiscard]] std::span<const std::uint8_t> get_bytecode() const noexcept;

private:
    std::shared_ptr<classfile::ClassFile> class_file_;
    const classfile::method_info* method_;

    std::vector<Slot> locals_;                ///< Local variable array (§2.6.1)
    std::vector<Slot> operand_stack_;         ///< Operand stack storage (§2.6.2)
    std::size_t stack_top_ = 0;               ///< Current stack top index

    std::uint16_t max_stack_;                 ///< Maximum operand stack depth
    std::span<const std::uint8_t> bytecode_;  ///< Method bytecode
    std::uint32_t pc_ = 0;                    ///< Program counter (bytecode offset)
};

} // namespace aijvm::runtime
