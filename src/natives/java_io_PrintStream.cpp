#include "natives/java_io_PrintStream.h"
#include "runtime/heap.h"

#include <iostream>
#include <string>

namespace aijvm::natives {

using namespace aijvm::runtime;

/// Helper: extract a C++ string from a JObject representing java/lang/String
static std::string extract_java_string(JObject* str_obj) {
    if (!str_obj) return "null";

    // Our ldc String representation stores a char[] in the "value" field
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

void register_java_io_PrintStream(NativeMethodRegistry& registry) {
    // PrintStream.println:(Ljava/lang/String;)V — print string + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println",
            "(Ljava/lang/String;)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto* str_obj = static_cast<JObject*>(frame.pop_ref());  // String arg
            (void)frame.pop_ref();  // 'this' (PrintStream instance)
            std::cout << extract_java_string(str_obj) << '\n';
        });

    // PrintStream.println:(I)V — print int + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "(I)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto val = frame.pop_int();
            (void)frame.pop_ref();  // 'this'
            std::cout << val << '\n';
        });

    // PrintStream.println:()V — print newline only
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "()V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            (void)frame.pop_ref();  // 'this'
            std::cout << '\n';
        });

    // PrintStream.print:(Ljava/lang/String;)V — print string without newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "print",
            "(Ljava/lang/String;)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto* str_obj = static_cast<JObject*>(frame.pop_ref());
            (void)frame.pop_ref();  // 'this'
            std::cout << extract_java_string(str_obj);
        });

    // PrintStream.println:(J)V — print long + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "(J)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto val = frame.pop_long();
            (void)frame.pop_ref();  // 'this'
            std::cout << val << '\n';
        });

    // PrintStream.println:(D)V — print double + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "(D)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto val = frame.pop_double();
            (void)frame.pop_ref();  // 'this'
            std::cout << val << '\n';
        });

    // PrintStream.println:(Z)V — print boolean + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "(Z)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto val = frame.pop_int();
            (void)frame.pop_ref();  // 'this'
            std::cout << (val ? "true" : "false") << '\n';
        });

    // PrintStream.println:(C)V — print char + newline
    registry.register_method(
        NativeMethodRegistry::make_key("java/io/PrintStream", "println", "(C)V"),
        []([[maybe_unused]] JavaThread& thread,
           Frame& frame,
           [[maybe_unused]] Heap& heap) {
            auto val = frame.pop_int();
            (void)frame.pop_ref();  // 'this'
            std::cout << static_cast<char>(val) << '\n';
        });
}

} // namespace aijvm::natives
