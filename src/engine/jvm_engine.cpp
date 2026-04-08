#include "engine/jvm_engine.h"
#include "classfile/class_file.h"
#include "runtime/frame.h"
#include "utils/logger.h"

#include <format>
#include <memory>
#include <span>

namespace aijvm {

using namespace classfile;
using namespace runtime;

JVMEngine::JVMEngine(const std::filesystem::path& boot_jmod_path,
                     const std::filesystem::path& class_path)
    : class_loader_(boot_jmod_path, class_path),
      interpreter_(heap_, class_loader_) {}

void JVMEngine::run(const std::string& main_class,
                    [[maybe_unused]] const std::vector<std::string>& args) {
    // §5.3: Load the main class
    AIJVM_LOG_INFO("Loading main class: {}", main_class);
    auto cf = class_loader_.load_class(main_class);
    if (!cf) {
        throw JVMError(std::format("Could not find or load main class {}", main_class));
    }

    // §5.2: Locate the main method — public static void main(String[])
    const method_info* main_method = nullptr;
    for (const auto& method : cf->methods) {
        const auto& name = cf->get_utf8(method.name_index);
        const auto& desc = cf->get_utf8(method.descriptor_index);
        if (name == "main" && desc == "([Ljava/lang/String;)V") {
            if ((method.access_flags & MethodAccess::ACC_PUBLIC) &&
                (method.access_flags & MethodAccess::ACC_STATIC)) {
                main_method = &method;
                break;
            }
        }
    }
    if (!main_method) {
        throw JVMError(std::format(
            "Main method not found in class {} "
            "(expected: public static void main(String[]))",
            main_class));
    }

    // §4.7.3: Extract the Code attribute from the main method
    const Code_attribute* code_attr = nullptr;
    for (const auto& attr : main_method->attributes) {
        code_attr = dynamic_cast<const Code_attribute*>(attr.get());
        if (code_attr) break;
    }
    if (!code_attr) {
        throw JVMError(std::format(
            "Code attribute not found for main method in class {}", main_class));
    }

    AIJVM_LOG_INFO("Executing {}.main() — max_locals={}, max_stack={}, code_length={}",
                   main_class,
                   code_attr->max_locals,
                   code_attr->max_stack,
                   code_attr->code.size());

    // §2.6: Create the initial Frame for the main method
    auto frame = std::make_unique<Frame>(
        cf, main_method,
        code_attr->max_locals, code_attr->max_stack,
        std::span<const std::uint8_t>(code_attr->code));

    // §2.6.1: local[0] = args (String[] reference — null for now, no heap yet)
    frame->set_local_ref(0, nullptr);

    // §2.5.2: Create the main thread and push the frame
    JavaThread main_thread("main");
    main_thread.push_frame(std::move(frame));

    // §2.12: Execute the interpreter dispatch loop
    interpreter_.execute(main_thread);

    AIJVM_LOG_INFO("{}.main() returned", main_class);
}

} // namespace aijvm
