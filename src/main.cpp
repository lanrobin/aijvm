#include "classfile/class_file.h"
#include "classfile/jmod_reader.h"
#include "classloader/class_loader.h"
#include "cli/command_line_parser.h"
#include "utils/logger.h"

#include <filesystem>
#include <format>
#include <string>

static void test_read_class_from_jmod(const std::filesystem::path& boot_jmod_path) {
    auto jmod_path = boot_jmod_path / "java.base.jmod";
    auto jmod = aijvm::classfile::JmodReader::open(jmod_path);
    if (!jmod) {
        AIJVM_LOG_ERROR("Failed to open {}", jmod_path.string());
        return;
    }

    auto class_data = jmod->read_file("classes/java/util/ArrayList.class");
    if (!class_data) {
        AIJVM_LOG_ERROR("Failed to read classes/java/util/ArrayList.class from jmod");
        return;
    }

    AIJVM_LOG_INFO("Read ArrayList.class: {} bytes", class_data->size());

    try {
        aijvm::classfile::ClassFile cf(std::move(*class_data));

        auto* this_cls = dynamic_cast<const aijvm::classfile::CONSTANT_Class_info*>(
            cf.constant_pool[cf.this_class].get());
        AIJVM_LOG_INFO("Class: {}", cf.get_utf8(this_cls->name_index));

        if (cf.super_class != 0) {
            auto* super_cls = dynamic_cast<const aijvm::classfile::CONSTANT_Class_info*>(
                cf.constant_pool[cf.super_class].get());
            AIJVM_LOG_INFO("Super class: {}", cf.get_utf8(super_cls->name_index));
        }

        for (auto iface_index : cf.interfaces) {
            auto* iface_cls = dynamic_cast<const aijvm::classfile::CONSTANT_Class_info*>(
                cf.constant_pool[iface_index].get());
            AIJVM_LOG_INFO("Interface: {}", cf.get_utf8(iface_cls->name_index));
        }
    } catch (const aijvm::classfile::ClassFileParseError& e) {
        AIJVM_LOG_ERROR("Failed to parse ArrayList.class: {}", e.what());
    }
}

static void load_class_hierarchy(aijvm::classloader::ClassLoader& loader,
                                 std::string_view class_name) {
    auto cf = loader.load_class(class_name);
    if (!cf) {
        AIJVM_LOG_WARN("Could not load class: {}", class_name);
        return;
    }

    AIJVM_LOG_INFO("Loaded class: {}", class_name);

    // Recursively load super class
    if (cf->super_class != 0) {
        auto* super_cls = dynamic_cast<const aijvm::classfile::CONSTANT_Class_info*>(
            cf->constant_pool[cf->super_class].get());
        if (super_cls) {
            const auto& super_name = cf->get_utf8(super_cls->name_index);
            if (!loader.is_loaded(super_name)) {
                load_class_hierarchy(loader, super_name);
            }
        }
    }

    // Recursively load all implemented interfaces
    for (auto iface_index : cf->interfaces) {
        auto* iface_cls = dynamic_cast<const aijvm::classfile::CONSTANT_Class_info*>(
            cf->constant_pool[iface_index].get());
        if (iface_cls) {
            const auto& iface_name = cf->get_utf8(iface_cls->name_index);
            if (!loader.is_loaded(iface_name)) {
                load_class_hierarchy(loader, iface_name);
            }
        }
    }
}

static void test_load_class(const std::filesystem::path& boot_jmod_path,
                             const std::filesystem::path& class_path,
                             const std::string& main_class) {
    AIJVM_LOG_INFO("=== test_load_class: loading '{}' and its hierarchy ===", main_class);

    aijvm::classloader::ClassLoader loader(boot_jmod_path, class_path);
    load_class_hierarchy(loader, main_class);

    AIJVM_LOG_INFO("=== test_load_class: done ===");
}

int main(int argc, char* argv[]) {
    aijvm::log::init();

    auto opts = aijvm::cli::parse_command_line(argc, argv);
    if (!opts) {
        return 1;
    }

    AIJVM_LOG_INFO("Boot JMod path : {}", opts->boot_jmod_path.string());
    AIJVM_LOG_INFO("Class path     : {}", opts->class_path.string());
    AIJVM_LOG_INFO("Main class     : {}", opts->main_class);

    for (const auto& arg : opts->program_args) {
        AIJVM_LOG_INFO("Program arg    : {}", arg);
    }

    for (const auto& [key, value] : opts->extra_options) {
        AIJVM_LOG_INFO("Extra option   : {} = {}", key, value);
    }

    test_read_class_from_jmod(opts->boot_jmod_path);

    test_load_class(opts->boot_jmod_path, opts->class_path, opts->main_class);

    return 0;
}
