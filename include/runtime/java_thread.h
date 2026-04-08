#pragma once

#include "runtime/frame.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace aijvm::runtime {

/// Default maximum JVM stack depth (number of frames).
/// Configurable per-thread at construction time.
constexpr std::size_t kDefaultMaxStackDepth = 512;

/// Thrown when the JVM stack exceeds its permitted depth.
/// Per §2.5.2: "If the computation in a thread requires a larger Java Virtual
/// Machine stack than is permitted, the Java Virtual Machine throws a
/// StackOverflowError."
class StackOverflowError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

// ============================================================================
// §2.5.1 The pc Register / §2.5.2 Java Virtual Machine Stacks
// ============================================================================
//
// "Each Java Virtual Machine thread has its own pc register." (§2.5.1)
// "Each Java Virtual Machine thread has a private Java Virtual Machine stack,
// created at the same time as the thread. A Java Virtual Machine stack stores
// frames (§2.6)." (§2.5.2)
//
// In this implementation, the PC is stored per-Frame (as bytecode offset) since
// the interpreter dispatches from the current frame's code. The thread-level PC
// is implicitly `current_frame()->pc()`.
// ============================================================================

class JavaThread {
public:
    /// Construct a thread with the given name and optional stack depth limit.
    explicit JavaThread(std::string name = "main",
                        std::size_t max_stack_depth = kDefaultMaxStackDepth);

    // Non-copyable, moveable (thread identity semantics)
    JavaThread(const JavaThread&) = delete;
    JavaThread& operator=(const JavaThread&) = delete;
    JavaThread(JavaThread&&) noexcept = default;
    JavaThread& operator=(JavaThread&&) noexcept = default;
    ~JavaThread() = default;

    // ===== Frame Management (§2.5.2, §2.6) =====

    /// Push a new frame (method invocation). Throws StackOverflowError on overflow.
    void push_frame(std::unique_ptr<Frame> frame);

    /// Pop and return the current frame (method return/completion).
    std::unique_ptr<Frame> pop_frame();

    /// Current (topmost) frame, or nullptr if stack is empty.
    [[nodiscard]] Frame* current_frame() noexcept;
    [[nodiscard]] const Frame* current_frame() const noexcept;

    /// Number of frames on the JVM stack.
    [[nodiscard]] std::size_t frame_count() const noexcept;

    /// Check if the JVM stack is empty.
    [[nodiscard]] bool stack_empty() const noexcept;

    // ===== Thread Metadata =====

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] bool is_alive() const noexcept;
    void set_alive(bool alive) noexcept;

private:
    std::string name_;
    std::vector<std::unique_ptr<Frame>> stack_;   ///< JVM Stack (§2.5.2)
    std::size_t max_stack_depth_;
    bool alive_ = true;
};

} // namespace aijvm::runtime
