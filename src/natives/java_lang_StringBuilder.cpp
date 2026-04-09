#include "natives/java_lang_StringBuilder.h"
#include "runtime/heap.h"
#include "runtime/opcode.h"

#include <string>

namespace aijvm::natives {

using namespace aijvm::runtime;

/// Helper: get the internal buffer string from a StringBuilder JObject
static std::string get_sb_buffer(JObject* sb) {
    if (!sb) return "";
    auto it = sb->fields.find("java/lang/StringBuilder._buffer");
    if (it == sb->fields.end()) return "";
    auto* arr_ptr = std::get_if<void*>(&it->second);
    if (!arr_ptr || !*arr_ptr) return "";
    auto* arr = static_cast<JObject*>(*arr_ptr);
    if (arr->kind != ObjectKind::ArrayChar) return "";
    std::string result;
    result.reserve(arr->array_char.size());
    for (auto c : arr->array_char) {
        result += static_cast<char>(c);
    }
    return result;
}

/// Helper: set the internal buffer on a StringBuilder JObject
static void set_sb_buffer(JObject* sb, const std::string& str, Heap& heap) {
    auto* arr = heap.allocate_primitive_array(ArrayType::T_CHAR,
        static_cast<std::int32_t>(str.size()));
    for (std::size_t i = 0; i < str.size(); ++i) {
        arr->array_char[i] = static_cast<std::uint16_t>(str[i]);
    }
    sb->fields["java/lang/StringBuilder._buffer"] = static_cast<void*>(arr);
}

/// Helper: extract a C++ string from a JObject representing java/lang/String
static std::string extract_java_string(JObject* str_obj) {
    if (!str_obj) return "null";
    auto it = str_obj->fields.find("java/lang/String.value");
    if (it == str_obj->fields.end()) return "";
    auto* char_arr_ptr = std::get_if<void*>(&it->second);
    if (!char_arr_ptr || !*char_arr_ptr) return "";
    auto* char_arr = static_cast<JObject*>(*char_arr_ptr);
    if (char_arr->kind != ObjectKind::ArrayChar) return "";
    std::string result;
    result.reserve(char_arr->array_char.size());
    for (auto c : char_arr->array_char) {
        result += static_cast<char>(c);
    }
    return result;
}

/// Helper: create a Java String JObject from a C++ string
static JObject* make_java_string(const std::string& str, Heap& heap) {
    auto* s = heap.allocate_object("java/lang/String");
    auto* arr = heap.allocate_primitive_array(ArrayType::T_CHAR,
        static_cast<std::int32_t>(str.size()));
    for (std::size_t i = 0; i < str.size(); ++i) {
        arr->array_char[i] = static_cast<std::uint16_t>(str[i]);
    }
    s->fields["java/lang/String.value"] = static_cast<void*>(arr);
    return s;
}

void register_java_lang_StringBuilder(NativeMethodRegistry& registry) {
    // StringBuilder.<init>:()V — initialize empty buffer
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "<init>", "()V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (sb) set_sb_buffer(sb, "", ctx.heap);
        });

    // StringBuilder.<init>:(Ljava/lang/String;)V — init with string
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "<init>",
            "(Ljava/lang/String;)V"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* str = static_cast<JObject*>(ctx.frame.pop_ref());  // string arg
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());   // this
            if (sb) set_sb_buffer(sb, extract_java_string(str), ctx.heap);
        });

    // StringBuilder.<init>:(I)V — init with capacity (ignore capacity)
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "<init>", "(I)V"),
        []([[maybe_unused]] VMContext& ctx) {
            (void)ctx.frame.pop_int();  // capacity
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            if (sb) set_sb_buffer(sb, "", ctx.heap);
        });

    // append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(Ljava/lang/String;)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* str = static_cast<JObject*>(ctx.frame.pop_ref());  // string arg
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());   // this
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += extract_java_string(str);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);  // return this
        });

    // append:(I)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(I)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_int();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += std::to_string(val);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(J)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(J)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_long();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += std::to_string(val);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(D)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(D)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_double();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += std::to_string(val);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(F)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(F)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_float();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += std::to_string(val);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(Z)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(Z)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_int();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += val ? "true" : "false";
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(C)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(C)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto val = ctx.frame.pop_int();
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                buf += static_cast<char>(val);
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "append",
            "(Ljava/lang/Object;)Ljava/lang/StringBuilder;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* obj = static_cast<JObject*>(ctx.frame.pop_ref());
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());
            if (sb) {
                auto buf = get_sb_buffer(sb);
                if (!obj) {
                    buf += "null";
                } else if (obj->class_name == "java/lang/String") {
                    buf += extract_java_string(obj);
                } else {
                    buf += obj->class_name + "@0x...";
                }
                set_sb_buffer(sb, buf, ctx.heap);
            }
            ctx.frame.push_ref(sb);
        });

    // toString:()Ljava/lang/String;
    registry.register_method(
        NativeMethodRegistry::make_key("java/lang/StringBuilder", "toString",
            "()Ljava/lang/String;"),
        []([[maybe_unused]] VMContext& ctx) {
            auto* sb = static_cast<JObject*>(ctx.frame.pop_ref());  // this
            auto buf = get_sb_buffer(sb);
            auto* str = make_java_string(buf, ctx.heap);
            ctx.frame.push_ref(str);
        });
}

} // namespace aijvm::natives
