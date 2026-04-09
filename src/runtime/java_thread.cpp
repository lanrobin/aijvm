#include "runtime/java_thread.h"

#include <format>
#include <utility>

namespace aijvm::runtime {

JavaThread::JavaThread(std::string name, std::size_t max_stack_depth)
    : name_(std::move(name)),
      max_stack_depth_(max_stack_depth) {}

JavaThread::JavaThread(JavaThread&& other) noexcept
    : name_(std::move(other.name_)),
      stack_(std::move(other.stack_)),
      max_stack_depth_(other.max_stack_depth_),
      state_(other.state_),
      os_thread_(std::move(other.os_thread_)) {
    other.state_ = ThreadState::Terminated;
}

JavaThread& JavaThread::operator=(JavaThread&& other) noexcept {
    if (this != &other) {
        if (os_thread_.joinable()) {
            os_thread_.join();
        }
        name_ = std::move(other.name_);
        stack_ = std::move(other.stack_);
        max_stack_depth_ = other.max_stack_depth_;
        state_ = other.state_;
        os_thread_ = std::move(other.os_thread_);
        other.state_ = ThreadState::Terminated;
    }
    return *this;
}

JavaThread::~JavaThread() {
    if (os_thread_.joinable()) {
        os_thread_.join();
    }
}

void JavaThread::start(std::function<void(JavaThread&)> entry) {
    if (state_ != ThreadState::New) {
        throw StackOverflowError(std::format(
            "Cannot start thread '{}': not in NEW state", name_));
    }
    state_ = ThreadState::Runnable;
    os_thread_ = std::thread([this, entry = std::move(entry)]() {
        entry(*this);
        state_ = ThreadState::Terminated;
    });
}

void JavaThread::join() {
    if (os_thread_.joinable()) {
        os_thread_.join();
    }
}

ThreadState JavaThread::state() const noexcept {
    return state_;
}

void JavaThread::push_frame(std::unique_ptr<Frame> frame) {
    if (stack_.size() >= max_stack_depth_) {
        throw StackOverflowError(std::format(
            "StackOverflowError: thread '{}' exceeded max stack depth {}",
            name_, max_stack_depth_));
    }
    stack_.push_back(std::move(frame));
}

std::unique_ptr<Frame> JavaThread::pop_frame() {
    if (stack_.empty()) {
        throw StackOverflowError(std::format(
            "pop_frame: thread '{}' has empty stack", name_));
    }
    auto frame = std::move(stack_.back());
    stack_.pop_back();
    return frame;
}

Frame* JavaThread::current_frame() noexcept {
    return stack_.empty() ? nullptr : stack_.back().get();
}

const Frame* JavaThread::current_frame() const noexcept {
    return stack_.empty() ? nullptr : stack_.back().get();
}

std::size_t JavaThread::frame_count() const noexcept {
    return stack_.size();
}

bool JavaThread::stack_empty() const noexcept {
    return stack_.empty();
}

const std::string& JavaThread::name() const noexcept {
    return name_;
}

bool JavaThread::is_alive() const noexcept {
    return state_ == ThreadState::Runnable;
}

void JavaThread::set_alive(bool alive) noexcept {
    state_ = alive ? ThreadState::Runnable : ThreadState::Terminated;
}

void JavaThread::collect_gc_roots(std::vector<void*>& roots) const {
    for (const auto& frame : stack_) {
        if (frame) {
            frame->collect_gc_roots(roots);
        }
    }
}

void JavaThread::update_gc_references() {
    for (auto& frame : stack_) {
        if (frame) {
            frame->update_gc_references();
        }
    }
}

} // namespace aijvm::runtime
