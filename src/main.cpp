#include "classfile/class_file.h"
#include "classfile/jmod_reader.h"
#include "cli/command_line_parser.h"
#include "utils/logger.h"

#include <filesystem>
#include <format>

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

    return 0;
}
