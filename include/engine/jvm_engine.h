#pragma once

#include "classloader/class_loader.h"
#include "runtime/heap.h"
#include "runtime/interpreter.h"
#include "runtime/native_registry.h"
#include "runtime/safepoint.h"
#include "runtime/java_thread.h"

#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace aijvm {

/// Thrown when the JVM cannot start or execute correctly.
class JVMError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

// ============================================================================
// JVMEngine — Top-level VM orchestration
// ============================================================================
//
// Ties together the Class Loader (§5.3), Runtime Data Areas (§2.5), and
// Execution Engine (§2.12) into a single entry point that:
//   1. Initializes the ClassLoader with boot jmod path and classpath.
//   2. Creates the shared Heap (§2.5.3) with a GC strategy.
//   3. Loads the main class and locates its `main([Ljava/lang/String;)V` method.
//   4. Creates a JavaThread with an initial Frame from the Code attribute.
//   5. Runs the Interpreter dispatch loop.
//
// The ClassLoader supports on-demand loading: classes referenced during
// execution (via invokevirtual, new, etc.) are loaded lazily through the
// Interpreter's class_loader_ reference rather than requiring upfront
// recursive loading.
// ============================================================================

class JVMEngine {
public:
    /// Construct the engine with bootstrap and application class paths.
    /// @param max_heap_size  Maximum heap size in bytes (from -Xmx). 0 = unlimited.
    JVMEngine(const std::filesystem::path& boot_jmod_path,
              const std::filesystem::path& class_path,
              std::size_t max_heap_size = 0);

    /// Load and execute the main method of the given class.
    /// @param main_class  Canonical class name (e.g. "HelloAdd")
    /// @param args        Program arguments (currently unused — no String[] support)
    void run(const std::string& main_class,
             const std::vector<std::string>& args = {});

private:
    classloader::ClassLoader class_loader_;
    runtime::Heap heap_;
    runtime::NativeMethodRegistry native_registry_;
    runtime::SafepointManager safepoint_mgr_;
    runtime::Interpreter interpreter_;
};

} // namespace aijvm
