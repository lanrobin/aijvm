#include "engine/jvm_engine.h"
#include "classfile/class_file.h"
#include "natives/java_lang_Object.h"
#include "natives/java_lang_Class.h"
#include "natives/java_lang_System.h"
#include "natives/java_lang_Thread.h"
#include "natives/java_lang_StringBuilder.h"
#include "natives/java_io_PrintStream.h"
#include "runtime/frame.h"
#include "utils/logger.h"

#include <format>
#include <memory>
#include <span>

namespace aijvm {

using namespace classfile;
using namespace runtime;

JVMEngine::JVMEngine(const std::filesystem::path& boot_jmod_path,
                     const std::filesystem::path& class_path,
                     std::size_t max_heap_size)
    : class_loader_(boot_jmod_path, class_path),
      heap_([&]() -> std::unique_ptr<GarbageCollector> {
                if (max_heap_size > 0) return std::make_unique<SemiSpaceGC>();
                return std::make_unique<NoOpGC>();
            }(), max_heap_size),
      interpreter_(heap_, class_loader_, native_registry_, safepoint_mgr_) {
    // Register all built-in native methods
    natives::register_java_lang_Object(native_registry_);
    natives::register_java_lang_Class(native_registry_);
    natives::register_java_lang_System(native_registry_);
    natives::register_java_lang_Thread(native_registry_);
    natives::register_java_lang_StringBuilder(native_registry_);
    natives::register_java_io_PrintStream(native_registry_);

    // Initialize well-known static fields (System.out, System.err)
    heap_.init_system_classes();
}

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

    // §2.6.1: local[0] = args (String[] reference — null for now)
    frame->set_local_ref(0, nullptr);

    // §2.5.1/§2.5.2: Create the Java main thread and spawn it on a child OS thread.
    // The OS main thread bootstraps the VM; the child thread executes Java bytecode.
    auto main_thread = std::make_unique<JavaThread>("main");
    main_thread->push_frame(std::move(frame));

    // Capture interpreter reference for the thread entry function
    auto& interp = interpreter_;
    main_thread->start([&interp](JavaThread& thread) {
        interp.execute(thread);
    });

    // OS main thread blocks until the Java main thread completes
    main_thread->join();

    AIJVM_LOG_INFO("{}.main() returned", main_class);
}

} // namespace aijvm
