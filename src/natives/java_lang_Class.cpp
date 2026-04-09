#include "natives/java_lang_Class.h"
#include "runtime/heap.h"
#include "runtime/opcode.h"

namespace aijvm::natives {

using namespace aijvm::runtime;

void register_java_lang_Class(NativeMethodRegistry& registry) {
    // Class.desiredAssertionStatus0:(Ljava/lang/Class;)Z — always return false
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "desiredAssertionStatus0",
            "(Ljava/lang/Class;)Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // class argument
            ctx.frame.push_int(0);     // false — assertions disabled
        });

    // Class.getPrimitiveClass:(Ljava/lang/String;)Ljava/lang/Class;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "getPrimitiveClass",
            "(Ljava/lang/String;)Ljava/lang/Class;"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // name string
            auto* cls = ctx.heap.allocate_object("java/lang/Class");
            ctx.frame.push_ref(cls);
        });

    // Class.registerNatives:()V — no-op
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "registerNatives", "()V"),
        []([[maybe_unused]] VMContext& ctx) {});

    // Class.isArray:()Z — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "isArray", "()Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // this
            ctx.frame.push_int(0);     // false
        });

    // Class.isInterface:()Z — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "isInterface", "()Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // this
            ctx.frame.push_int(0);
        });

    // Class.isPrimitive:()Z — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "isPrimitive", "()Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // this
            ctx.frame.push_int(0);
        });

    // Class.isAssignableFrom:(Ljava/lang/Class;)Z — simplified: always true
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "isAssignableFrom",
            "(Ljava/lang/Class;)Z"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // cls argument  
            (void)ctx.frame.pop_ref();  // this
            ctx.frame.push_int(1);     // true
        });

    // Class.getName0:()Ljava/lang/String; — simplified
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "getName0",
            "()Ljava/lang/String;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* cls = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            // Create a String object with the class name
            std::string name = cls ? cls->class_name : "java/lang/Object";
            auto* str = ctx.heap.allocate_object("java/lang/String");
            auto* arr = ctx.heap.allocate_primitive_array(ArrayType::T_CHAR,
                static_cast<std::int32_t>(name.size()));
            for (std::size_t i = 0; i < name.size(); ++i) {
                arr->array_char[i] = static_cast<std::uint16_t>(name[i]);
            }
            str->fields["java/lang/String.value"] = static_cast<void*>(arr);
            ctx.frame.push_ref(str);
        });

    // Class.forName0 — simplified stub
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/Class", "forName0",
            "(Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_ref();  // caller
            (void)ctx.frame.pop_ref();  // loader
            (void)ctx.frame.pop_int();  // initialize
            (void)ctx.frame.pop_ref();  // name
            auto* cls = ctx.heap.allocate_object("java/lang/Class");
            ctx.frame.push_ref(cls);
        });
}

} // namespace aijvm::natives
