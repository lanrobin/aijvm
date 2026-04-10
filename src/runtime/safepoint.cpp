#include "runtime/safepoint.h"

#include <algorithm>

namespace aijvm::runtime {

void SafepointManager::register_thread(JavaThread* thread) {
    std::lock_guard<std::mutex> lock(mutex_);
    ++total_threads_;
    threads_.push_back(thread);
}

void SafepointManager::unregister_thread(JavaThread* thread) {
    std::lock_guard<std::mutex> lock(mutex_);
    --total_threads_;
    std::erase(threads_, thread);
    // If we were the last thread to unregister during a GC request,
    // wake the GC thread to avoid a deadlock.
    if (gc_requested_ && parked_threads_ >= total_threads_) {
        cv_parked_.notify_all();
    }
}

void SafepointManager::safepoint_poll() {
    if (!gc_requested_.load(std::memory_order_relaxed)) return;

    std::unique_lock<std::mutex> lock(mutex_);
    if (!gc_requested_.load()) return;

    // Park this thread
    ++parked_threads_;

    // Notify the GC requester — it may be waiting for fewer than total_threads_
    // (e.g. caller_is_mutator mode waits for total - 1).
    cv_parked_.notify_all();

    // Wait until GC is complete
    cv_resume_.wait(lock, [this] { return !gc_in_progress_; });
    --parked_threads_;
}

void SafepointManager::request_stw(std::function<void()> gc_work,
                                   bool caller_is_mutator) {
    std::unique_lock<std::mutex> lock(mutex_);

    gc_in_progress_ = true;
    gc_requested_.store(true, std::memory_order_release);

    // If the caller is a mutator thread, it won't park — wait for (total - 1).
    // Otherwise (e.g. dedicated GC thread), wait for all threads to park.
    std::size_t expected = caller_is_mutator && total_threads_ > 0
                           ? total_threads_ - 1
                           : total_threads_;

    // Wait until enough mutator threads have parked
    cv_parked_.wait(lock, [this, expected] { return parked_threads_ >= expected; });

    // All other threads parked — run GC
    lock.unlock();
    gc_work();
    lock.lock();

    // Resume all threads
    gc_requested_.store(false, std::memory_order_release);
    gc_in_progress_ = false;
    cv_resume_.notify_all();
}

bool SafepointManager::gc_requested() const noexcept {
    return gc_requested_.load(std::memory_order_relaxed);
}

const std::vector<JavaThread*>& SafepointManager::registered_threads() const noexcept {
    return threads_;
}

} // namespace aijvm::runtime
