#include "natives/java_lang_Thread.h"
#include "runtime/heap.h"
#include "runtime/interpreter.h"
#include "classloader/class_loader.h"
#include "classfile/class_file.h"
#include "runtime/opcode.h"
#include "utils/logger.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

namespace aijvm::natives {

using namespace aijvm::runtime;

// ============================================================================
// Thread management for the 1:1 threading model.
//
// Each Java Thread object (JObject with class_name "java/lang/Thread") stores
// a "target" Runnable field and a C++ std::thread handle. When Thread.start()
// is called, we spawn an OS thread that invokes target.run().
// ============================================================================

/// Global list of spawned OS threads, so we can join them at shutdown.
static std::mutex g_threads_mutex;
static std::vector<std::thread> g_spawned_threads;

void register_java_lang_Thread(NativeMethodRegistry& registry) {

    // Thread.registerNatives:()V — JVM internal, no-op
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "registerNatives", "()V"),
        []([[maybe_unused]] VMContext& ctx) {});

    // Thread.<init>:(Ljava/lang/Runnable;)V — store target
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "<init>",
            "(Ljava/lang/Runnable;)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* target = ctx.frame.pop_ref();  // Runnable
            auto* self = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (self) {
                self->fields["java/lang/Thread.target"] = target;
            }
        });

    // Thread.<init>:()V — default constructor
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "<init>", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // this
        });

    // Thread.<init>:(Ljava/lang/ThreadGroup;Ljava/lang/Runnable;)V — store target
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "<init>",
            "(Ljava/lang/ThreadGroup;Ljava/lang/Runnable;)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* target = ctx.frame.pop_ref();  // Runnable
            (void)ctx.frame.pop_ref();           // ThreadGroup
            auto* self = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (self) {
                self->fields["java/lang/Thread.target"] = target;
            }
        });

    // Thread.start:()V — spawn an OS thread that calls target.run()
    // This is the core of the 1:1 threading model.
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "start", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* self = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (!self) return;

            // Get the target Runnable
            void* target_ptr = nullptr;
            auto it = self->fields.find("java/lang/Thread.target");
            if (it != self->fields.end()) {
                if (auto* v = std::get_if<void*>(&it->second)) {
                    target_ptr = *v;
                }
            }

            if (!target_ptr) {
                AIJVM_LOG_WARN("Thread.start: no target Runnable, thread does nothing");
                return;
            }

            auto* target = static_cast<JObject*>(target_ptr);

            // Mark thread object as started
            self->fields["java/lang/Thread._started"] = static_cast<std::int32_t>(1);
            self->fields["java/lang/Thread._done"] = static_cast<std::int32_t>(0);

            AIJVM_LOG_INFO("Thread.start: spawning OS thread for {}",
                           target->class_name);

            // Resolve target.run()V method
            auto& cl = ctx.class_loader;
            auto target_cf = cl.load_class(target->class_name);
            if (!target_cf) {
                AIJVM_LOG_ERROR("Thread.start: cannot load class {}",
                                target->class_name);
                return;
            }

            const classfile::method_info* run_method = nullptr;
            for (const auto& m : target_cf->methods) {
                if (target_cf->get_utf8(m.name_index) == "run" &&
                    target_cf->get_utf8(m.descriptor_index) == "()V") {
                    run_method = &m;
                    break;
                }
            }
            if (!run_method) {
                AIJVM_LOG_ERROR("Thread.start: no run()V method in {}",
                                target->class_name);
                return;
            }

            const classfile::Code_attribute* code_attr = nullptr;
            for (const auto& attr : run_method->attributes) {
                code_attr = dynamic_cast<const classfile::Code_attribute*>(attr.get());
                if (code_attr) break;
            }
            if (!code_attr) {
                AIJVM_LOG_ERROR("Thread.start: no Code attribute for {}.run()V",
                                target->class_name);
                return;
            }

            // Capture everything needed for the child thread
            auto& interp = ctx.interpreter;
            auto cf_shared = target_cf;
            auto* run_m = run_method;
            auto* code = code_attr;
            auto* target_obj = target;
            auto* thread_obj = self;

            // Spawn a real OS thread (§2.5.1: 1:1 threading model)
            std::lock_guard<std::mutex> lock(g_threads_mutex);
            g_spawned_threads.emplace_back([&interp, cf_shared, run_m, code,
                                            target_obj, thread_obj]() {
                JavaThread child_thread("worker");

                // Create frame for target.run()
                auto run_frame = std::make_unique<Frame>(
                    cf_shared, run_m,
                    code->max_locals, code->max_stack,
                    std::span<const std::uint8_t>(code->code));

                // local[0] = this (the Runnable target)
                run_frame->set_local_ref(0, target_obj);

                child_thread.push_frame(std::move(run_frame));
                interp.execute(child_thread);

                thread_obj->fields["java/lang/Thread._done"] =
                    static_cast<std::int32_t>(1);
            });
        });

    // Thread.join:()V — wait for thread to complete
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "join", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* self = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (!self) return;

            // Wait for spawned threads to complete
            std::lock_guard<std::mutex> lock(g_threads_mutex);
            for (auto& t : g_spawned_threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
            g_spawned_threads.clear();
        });

    // Thread.join:(J)V — timed join
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "join", "(J)V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_long();  // millis
            auto* self = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (!self) return;
            std::lock_guard<std::mutex> lock(g_threads_mutex);
            for (auto& t : g_spawned_threads) {
                if (t.joinable()) t.join();
            }
            g_spawned_threads.clear();
        });

    // Thread.sleep:(J)V — sleep for millis
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "sleep", "(J)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto millis = ctx.frame.pop_long();
            if (millis > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(millis));
            }
        });

    // Thread.currentThread:()Ljava/lang/Thread; — return a sentinel
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "currentThread",
            "()Ljava/lang/Thread;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* t = ctx.heap.allocate_object("java/lang/Thread");
            ctx.frame.push_ref(t);
        });

    // Thread.isAlive:()Z
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "isAlive", "()Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // this
            ctx.frame.push_int(0);     // simplified: always false
        });

    // Thread.setPriority:(I)V — no-op
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "setPriority", "(I)V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_int();  // priority
            (void)ctx.frame.pop_ref(); // this
        });

    // Thread.isInterrupted:(Z)Z — always false
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Thread", "isInterrupted", "(Z)Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_int();  // clearInterrupted
            (void)ctx.frame.pop_ref(); // this
            ctx.frame.push_int(0);
        });
}

} // namespace aijvm::natives
