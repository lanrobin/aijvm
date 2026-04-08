#include "runtime/java_thread.h"

#include <format>
#include <utility>

namespace aijvm::runtime {

JavaThread::JavaThread(std::string name, std::size_t max_stack_depth)
    : name_(std::move(name)),
      max_stack_depth_(max_stack_depth) {}

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
    return alive_;
}

void JavaThread::set_alive(bool alive) noexcept {
    alive_ = alive;
}

} // namespace aijvm::runtime
