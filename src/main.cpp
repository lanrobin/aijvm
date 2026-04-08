#include "cli/command_line_parser.h"
#include "engine/jvm_engine.h"
#include "utils/logger.h"

#include <format>
#include <string>

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

    try {
        aijvm::JVMEngine engine(opts->boot_jmod_path, opts->class_path);
        engine.run(opts->main_class, opts->program_args);
    } catch (const aijvm::JVMError& e) {
        AIJVM_LOG_ERROR("JVM Error: {}", e.what());
        return 1;
    } catch (const aijvm::runtime::InterpreterError& e) {
        AIJVM_LOG_ERROR("Interpreter Error: {}", e.what());
        return 1;
    } catch (const aijvm::runtime::FrameError& e) {
        AIJVM_LOG_ERROR("Frame Error: {}", e.what());
        return 1;
    } catch (const std::exception& e) {
        AIJVM_LOG_ERROR("Unexpected error: {}", e.what());
        return 1;
    }

    return 0;
}
