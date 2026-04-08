#include "natives/java_lang_Object.h"
#include "runtime/heap.h"

namespace aijvm::natives {

using namespace aijvm::runtime;

void register_java_lang_Object(NativeMethodRegistry& registry) {
    // Object.<init>:()V — default constructor, no-op
    // Pop 'this' reference from the operand stack (consumed by invoke setup)
    // Nothing to do — the object is already allocated by 'new'
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "<init>", "()V"),
        []([[maybe_unused]] JavaThread& thread,
           [[maybe_unused]] Frame& frame,
           [[maybe_unused]] Heap& heap) {
            // No-op: Object constructor does nothing in our minimal JVM
        });

    // Object.hashCode:()I — return identity hash (pointer-based)
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "hashCode", "()I"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto* obj = frame.pop_ref();  // 'this'
            auto hash = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(obj) & 0x7FFFFFFF);
            frame.push_int(hash);
        });

    // Object.getClass:()Ljava/lang/Class; — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Object", "getClass", "()Ljava/lang/Class;"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           Heap& heap) {
            auto* obj = static_cast<JObject*>(frame.pop_ref());  // 'this'
            auto* cls_obj = heap.allocate_object("java/lang/Class");
            if (obj) {
                cls_obj->fields["java/lang/Class.name"] = static_cast<void*>(nullptr);
            }
            frame.push_ref(cls_obj);
        });
}

} // namespace aijvm::natives
