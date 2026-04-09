#include "natives/java_lang_Object.h"
#include "runtime/heap.h"

#include <chrono>
#include <thread>

namespace aijvm::natives {

using namespace aijvm::runtime;

void register_java_lang_Object(NativeMethodRegistry& registry) {
    // Object.<init>:()V — default constructor, no-op
    // Must pop 'this' from the caller's operand stack (invokespecial is non-static)
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "<init>", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // pop 'this'
        });

    // Object.hashCode:()I — return identity hash (pointer-based)
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "hashCode", "()I"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = ctx.frame.pop_ref();  // 'this'
            auto hash = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(obj) & 0x7FFFFFFF);
            ctx.frame.push_int(hash);
        });

    // Object.getClass:()Ljava/lang/Class; — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "getClass", "()Ljava/lang/Class;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());  // 'this'
            auto* cls_obj = ctx.heap.allocate_object("java/lang/Class");
            if (obj) {
                cls_obj->fields["java/lang/Class.name"] = static_cast<void*>(nullptr);
            }
            ctx.frame.push_ref(cls_obj);
        });

    // Object.wait:()V — release monitor, wait for notify, reacquire monitor  
    // §17.2: "The thread releases ownership of the monitor and waits until
    // another thread notifies threads waiting on this monitor to wake up."
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "wait", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            if (obj) {
                obj->monitor_cv.wait(obj->monitor);
            }
        });

    // Object.wait:(J)V — timed wait
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "wait", "(J)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto millis = ctx.frame.pop_long();
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            if (obj && millis > 0) {
                obj->monitor_cv.wait_for(obj->monitor,
                    std::chrono::milliseconds(millis));
            } else if (obj) {
                obj->monitor_cv.wait(obj->monitor);
            }
        });

    // Object.wait:(JI)V — timed wait with nanos
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "wait", "(JI)V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_int();   // nanos
            auto millis = ctx.frame.pop_long();
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            if (obj && millis > 0) {
                obj->monitor_cv.wait_for(obj->monitor,
                    std::chrono::milliseconds(millis));
            } else if (obj) {
                obj->monitor_cv.wait(obj->monitor);
            }
        });

    // Object.notify:()V — wake up one waiting thread
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "notify", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            if (obj) obj->monitor_cv.notify_one();
        });

    // Object.notifyAll:()V — wake up all waiting threads
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "notifyAll", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            if (obj) obj->monitor_cv.notify_all();
        });
}

} // namespace aijvm::natives
