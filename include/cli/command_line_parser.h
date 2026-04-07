#pragma once

#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace aijvm::cli {

/// Parsed command-line options stored as a C++ object for later use
/// (e.g., constructing a JVM engine).
struct CommandLineOptions {
    std::filesystem::path boot_jmod_path;  // --bj <path>  : OpenJDK jmod folder
    std::filesystem::path class_path;      // --cp <path>  : user classes folder
    std::string main_class;                // positional   : main class to execute

    std::vector<std::string> program_args;  // remaining args forwarded to main(String[])

    /// Unrecognized --key value pairs preserved for future use.
    std::map<std::string, std::string> extra_options;
};

/// Lightweight CLI parser.
/// Returns std::nullopt and prints usage on error (missing required args).
[[nodiscard]] std::optional<CommandLineOptions> parse_command_line(int argc, char* argv[]);

/// Print usage information to stderr.
void print_usage(std::string_view program_name);

}  // namespace aijvm::cli
