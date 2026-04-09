#include "natives/java_lang_System.h"
#include "runtime/heap.h"
#include "runtime/interpreter.h"

namespace aijvm::natives {

using namespace aijvm::runtime;

void register_java_lang_System(NativeMethodRegistry& registry) {
    // System.registerNatives:()V — JVM internal, no-op
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/System", "registerNatives", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            // No-op
        });

    // System.currentTimeMillis:()J
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/System", "currentTimeMillis", "()J"),
        []([[maybe_unused]] VMContext& ctx) {
            ctx.frame.push_long(0LL);  // simplified
        });

    // System.arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/System", "arraycopy",
            "(Ljava/lang/Object;ILjava/lang/Object;II)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto length = ctx.frame.pop_int();
            auto dest_pos = ctx.frame.pop_int();
            auto* dest = static_cast<JObject*>(ctx.frame.pop_ref());
            auto src_pos = ctx.frame.pop_int();
            auto* src = static_cast<JObject*>(ctx.frame.pop_ref());
            if (!src || !dest) return;
            // Simple int array copy
            if (src->kind == ObjectKind::ArrayInt && dest->kind == ObjectKind::ArrayInt) {
                for (int i = 0; i < length; ++i) {
                    dest->array_int[static_cast<std::size_t>(dest_pos + i)] =
                        src->array_int[static_cast<std::size_t>(src_pos + i)];
                }
            } else if (src->kind == ObjectKind::ArrayRef && dest->kind == ObjectKind::ArrayRef) {
                for (int i = 0; i < length; ++i) {
                    dest->array_ref[static_cast<std::size_t>(dest_pos + i)] =
                        src->array_ref[static_cast<std::size_t>(src_pos + i)];
                }
            }
        });

    // System.gc:()V — trigger garbage collection
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/System", "gc", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            ctx.interpreter.trigger_gc(ctx.thread);
        });
}

} // namespace aijvm::natives
