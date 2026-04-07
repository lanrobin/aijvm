#include "cli/command_line_parser.h"
#include "utils/logger.h"

#include <format>

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

    return 0;
}
