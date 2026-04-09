#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>

namespace aijvm::runtime {

// ============================================================================
// Stop-The-World Safepoint Manager
// ============================================================================
//
// Since std::thread cannot be force-suspended in portable C++20, we use a
// cooperative safepoint model:
//
//   1. The GC requester sets gc_requested = true.
//   2. Each interpreter thread checks gc_requested at safepoints (backward
//      branches, method entry/return, allocation sites).
//   3. When a thread sees gc_requested, it increments a parked counter and
//      blocks on a condition variable.
//   4. When all registered threads are parked, the GC thread runs collection.
//   5. After GC completes, the GC thread wakes all parked threads.
//
// This is equivalent to HotSpot's safepoint polling mechanism.
// ============================================================================

class SafepointManager {
public:
    SafepointManager() = default;

    /// Register a mutator thread. Must be called before the thread starts
    /// executing bytecode. Thread-safe.
    void register_thread();

    /// Unregister a mutator thread. Called when the thread finishes.
    void unregister_thread();

    /// Called by mutator threads at safepoints (backward branches, alloc, etc.).
    /// If a GC is requested, this blocks until the GC is complete.
    void safepoint_poll();

    /// Request a stop-the-world pause.
    /// Blocks until all mutator threads have reached a safepoint.
    /// Then executes the given function (typically GC) while all threads are parked.
    /// After the function returns, all threads are resumed.
    void request_stw(std::function<void()> gc_work);

    /// Check whether GC is currently requested (non-blocking).
    [[nodiscard]] bool gc_requested() const noexcept;

private:
    std::atomic<bool> gc_requested_{false};
    std::mutex mutex_;
    std::condition_variable cv_parked_;    ///< GC thread waits for all to park
    std::condition_variable cv_resume_;    ///< Mutator threads wait for GC to finish
    std::size_t total_threads_ = 0;       ///< Number of registered mutator threads
    std::size_t parked_threads_ = 0;      ///< Number of threads at safepoint
    bool gc_in_progress_ = false;
};

} // namespace aijvm::runtime
