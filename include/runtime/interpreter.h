#pragma once

#include "runtime/opcode.h"
#include "runtime/heap.h"
#include "runtime/native_registry.h"
#include "runtime/java_thread.h"

#include <cstdint>
#include <stdexcept>

namespace aijvm::classloader {
    class ClassLoader;  // forward declaration
}

namespace aijvm::runtime {

// ============================================================================
// Interpreter — Full bytecode dispatch engine
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
// dispatch performance for dense opcode ranges.
// ============================================================================

/// Thrown on unimplemented or illegal opcode during interpretation.
class InterpreterError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

/// Thrown when a native method is invoked but no native binding is registered.
/// Per prompt requirement: "raise NativeMethodNotFoundError when need to invoke
/// a native method, we will provide them in future implements."
class NativeMethodNotFoundError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Interpreter {
public:
    /// Construct interpreter with references to shared subsystems.
    /// @param heap            Shared heap for object allocation (§2.5.3)
    /// @param class_loader    For on-demand class loading during resolution (§5.3)
    /// @param native_registry Registry of native method bindings
    Interpreter(Heap& heap, classloader::ClassLoader& class_loader,
                NativeMethodRegistry& native_registry);

    /// Execute the current frame on the given thread until the method returns.
    /// For `return` (void): pops the frame and returns to caller.
    /// For value returns (ireturn, lreturn, etc.): pops the frame, pushes
    /// return value onto caller's operand stack.
    /// When the last frame returns, execution completes.
    void execute(JavaThread& thread);

    /// Execute a single bytecode instruction from the current frame.
    /// Returns false when the method has returned (frame was popped).
    [[nodiscard]] bool execute_instruction(JavaThread& thread, Frame& frame);

private:
    Heap& heap_;
    classloader::ClassLoader& class_loader_;
    NativeMethodRegistry& native_registry_;

    // --- Instruction group handlers (reduce switch-case bloat) ---

    /// §6.5 ldc / ldc_w / ldc2_w — load constant from pool
    void do_ldc(Frame& frame, std::uint16_t cp_index);

    /// §6.5 invoke* — method invocation family
    void do_invoke(JavaThread& thread, Frame& frame,
                   std::uint8_t opcode, std::uint16_t cp_index);

    /// §6.5 get/putfield, get/putstatic — field access family
    void do_field_access(JavaThread& thread, Frame& frame,
                         std::uint8_t opcode, std::uint16_t cp_index);

    /// §6.5 new — allocate object instance
    void do_new(JavaThread& thread, Frame& frame, std::uint16_t cp_index);

    /// §6.5 newarray — allocate primitive array
    void do_newarray(Frame& frame, std::uint8_t atype);

    /// §6.5 anewarray — allocate reference array
    void do_anewarray(Frame& frame, std::uint16_t cp_index);

    /// §6.5 multianewarray — allocate multi-dimensional array
    void do_multianewarray(Frame& frame, std::uint16_t cp_index, std::uint8_t dimensions);

    /// §6.5 checkcast / instanceof
    void do_checkcast(Frame& frame, std::uint16_t cp_index);
    void do_instanceof(Frame& frame, std::uint16_t cp_index);

    // ===== §5.5 Class Initialization =====

    /// Ensure a class is initialized before use. Per §5.5:
    /// "A class or interface C may be initialized only as a result of:
    ///  - The execution of new, getstatic, putstatic, or invokestatic that
    ///    references C."
    ///
    /// This method:
    ///  1. Checks the class init state in the Heap
    ///  2. If Uninitialized, recursively initializes the superclass first
    ///  3. Finds <clinit> in the ClassFile and executes it synchronously
    ///  4. Transitions class state: Uninitialized → Initializing → Initialized
    void ensure_initialized(JavaThread& thread, std::string_view class_name);
};

} // namespace aijvm::runtime
