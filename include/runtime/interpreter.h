#pragma once

#include "runtime/java_thread.h"

#include <cstdint>
#include <stdexcept>

namespace aijvm::runtime {

// ============================================================================
// §6 The Java Virtual Machine Instruction Set — Opcode Definitions
// ============================================================================
// Opcode values per Chapter 7 (Opcode Mnemonics by Opcode).
// Only the subset needed for initial arithmetic interpreter is defined here.
// ============================================================================

namespace Opcode {
    // §6.5 — Constants
    constexpr std::uint8_t NOP         = 0x00;
    constexpr std::uint8_t ICONST_M1   = 0x02;  // Push int -1
    constexpr std::uint8_t ICONST_0    = 0x03;  // Push int 0
    constexpr std::uint8_t ICONST_1    = 0x04;  // Push int 1
    constexpr std::uint8_t ICONST_2    = 0x05;  // Push int 2
    constexpr std::uint8_t ICONST_3    = 0x06;  // Push int 3
    constexpr std::uint8_t ICONST_4    = 0x07;  // Push int 4
    constexpr std::uint8_t ICONST_5    = 0x08;  // Push int 5
    constexpr std::uint8_t BIPUSH      = 0x10;  // Push byte as int

    // §6.5 — Loads
    constexpr std::uint8_t ILOAD       = 0x15;  // Load int from local (1-byte index)
    constexpr std::uint8_t ILOAD_0     = 0x1A;  // Load int from local 0
    constexpr std::uint8_t ILOAD_1     = 0x1B;  // Load int from local 1
    constexpr std::uint8_t ILOAD_2     = 0x1C;  // Load int from local 2
    constexpr std::uint8_t ILOAD_3     = 0x1D;  // Load int from local 3

    // §6.5 — Stores
    constexpr std::uint8_t ISTORE      = 0x36;  // Store int to local (1-byte index)
    constexpr std::uint8_t ISTORE_0    = 0x3B;  // Store int to local 0
    constexpr std::uint8_t ISTORE_1    = 0x3C;  // Store int to local 1
    constexpr std::uint8_t ISTORE_2    = 0x3D;  // Store int to local 2
    constexpr std::uint8_t ISTORE_3    = 0x3E;  // Store int to local 3

    // §6.5 — Math
    constexpr std::uint8_t IADD        = 0x60;  // Add two ints

    // §6.5 — Returns
    constexpr std::uint8_t IRETURN     = 0xAC;  // Return int from method
    constexpr std::uint8_t RETURN      = 0xB1;  // Return void from method
} // namespace Opcode

// ============================================================================
// Interpreter
// ============================================================================
//
// Dispatch mechanism: switch-case.
//
// Justification: Computed goto (GCC/Clang &&label) is ~15-20% faster for hot
// interpreter loops by avoiding branch prediction overhead vs. switch-case.
// However, it is a compiler extension — not portable C++20 and requires
// #ifdef guards per compiler. Since our claude.md mandates strict C++20
// standard compliance and cross-platform CMake builds (MSVC included),
// switch-case is the correct choice. The compiler will typically lower a dense
// switch into a jump table anyway (GCC -O2 / MSVC /O2), achieving comparable
// dispatch performance for dense opcode ranges. If profiling later shows
// dispatch overhead as a bottleneck, we can add computed goto behind a
// platform-detection macro without changing the public API.
// ============================================================================

/// Thrown on unimplemented or illegal opcode during interpretation.
class InterpreterError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Interpreter {
public:
    Interpreter() = default;

    /// Execute the current frame on the given thread until the method returns.
    /// For `return` (void): pops the frame and returns to caller.
    /// For `ireturn`: pops the frame, pushes return value onto caller's operand stack.
    /// When the last frame returns, execution completes.
    void execute(JavaThread& thread);

    /// Execute a single bytecode instruction from the current frame.
    /// Returns false when the method has returned (frame was popped).
    [[nodiscard]] bool execute_instruction(JavaThread& thread, Frame& frame);
};

} // namespace aijvm::runtime
