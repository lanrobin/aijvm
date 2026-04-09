#include "runtime/safepoint.h"

namespace aijvm::runtime {

void SafepointManager::register_thread() {
    std::lock_guard<std::mutex> lock(mutex_);
    ++total_threads_;
}

void SafepointManager::unregister_thread() {
    std::lock_guard<std::mutex> lock(mutex_);
    --total_threads_;
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

    // If all threads are parked, wake the GC thread
    if (parked_threads_ >= total_threads_) {
        cv_parked_.notify_all();
    }

    // Wait until GC is complete
    cv_resume_.wait(lock, [this] { return !gc_in_progress_; });
    --parked_threads_;
}

void SafepointManager::request_stw(std::function<void()> gc_work) {
    std::unique_lock<std::mutex> lock(mutex_);

    gc_in_progress_ = true;
    gc_requested_.store(true, std::memory_order_release);

    // Wait until all mutator threads have parked
    cv_parked_.wait(lock, [this] { return parked_threads_ >= total_threads_; });

    // All threads parked — run GC
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

} // namespace aijvm::runtime
