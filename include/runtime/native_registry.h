#pragma once

#include "runtime/java_thread.h"
#include "runtime/heap.h"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace aijvm::classloader {
    class ClassLoader;
}

namespace aijvm::runtime {

class Interpreter;  // forward declaration

// ============================================================================
// Native Method Registry
// ============================================================================

/// Bundles all VM subsystem references needed by native method handlers.
/// Passed by reference to every native method invocation.
struct VMContext {
    JavaThread& thread;
    Frame& frame;
    Heap& heap;
    Interpreter& interpreter;
    classloader::ClassLoader& class_loader;
};

/// Signature for native method implementations.
/// @param ctx  VM context with all subsystem references
using NativeMethodFn = std::function<void(VMContext& ctx)>;

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
