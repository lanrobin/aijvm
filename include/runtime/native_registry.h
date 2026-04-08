#pragma once

#include "runtime/java_thread.h"
#include "runtime/heap.h"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace aijvm::runtime {

// ============================================================================
// Native Method Registry
// ============================================================================
//
// §2.5.6 Native Method Stacks / §6.5 invokenative semantics:
// "A Java Virtual Machine implementation may use conventional stacks,
// colloquially called 'C stacks,' to support native methods."
//
// Design: A lookup table mapping "class_name.method_name:descriptor" to a
// C++ std::function handler. The Interpreter queries this registry when it
// encounters a method with ACC_NATIVE set. If no binding exists, it throws
// NativeMethodNotFoundError.
//
// Each native handler receives:
//   - The executing thread (for frame/stack access)
//   - The current frame (to pop arguments and push return values)
//   - A reference to the heap (for object allocation)
//
// The handler is responsible for popping its arguments from the caller's
// operand stack and pushing any return value.
// ============================================================================

/// Signature for native method implementations.
/// @param thread  The executing thread
/// @param frame   Caller's frame (args are already on the operand stack)
/// @param heap    Shared heap for object allocation
using NativeMethodFn = std::function<void(JavaThread& thread, Frame& frame, Heap& heap)>;

/// Centralized registry for all native method bindings.
class NativeMethodRegistry {
public:
    NativeMethodRegistry() = default;

    /// Register a native method binding.
    /// @param key  Format: "class_name.method_name:descriptor"
    ///             e.g. "java/io/PrintStream.println:(Ljava/lang/String;)V"
    /// @param fn   The C++ handler function
    void register_method(const std::string& key, NativeMethodFn fn);

    /// Look up a native method binding.
    /// @return pointer to the handler, or nullptr if not registered
    [[nodiscard]] const NativeMethodFn* find(const std::string& key) const;

    /// Check if a native method is registered.
    [[nodiscard]] bool has(const std::string& key) const;

    /// Build the canonical key from components.
    [[nodiscard]] static std::string make_key(std::string_view class_name,
                                              std::string_view method_name,
                                              std::string_view descriptor);

    /// Register all built-in native method bindings.
    /// Called once during JVM initialization.
    void register_defaults();

private:
    std::unordered_map<std::string, NativeMethodFn> methods_;
};

} // namespace aijvm::runtime
