#include "cli/command_line_parser.h"

#include "utils/logger.h"

#include <format>

namespace aijvm::cli {

void print_usage(std::string_view program_name) {
    AIJVM_LOG_ERROR(
        "Usage: {} [options] <MainClass> [args...]\n"
        "\n"
        "Required:\n"
        "  --bj <path>   OpenJDK jmod folder (e.g. /usr/lib/jvm/java-25-openjdk-amd64/jmods)\n"
        "  --cp <path>   User classes folder\n"
        "  <MainClass>   Fully qualified class name with public static void main(String[])\n"
        "\n"
        "Any unrecognized --key value pairs are stored for future use.",
        program_name);
}

[[nodiscard]] std::optional<CommandLineOptions> parse_command_line(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return std::nullopt;
    }

    CommandLineOptions opts;
    std::vector<std::string_view> args(argv + 1, argv + argc);

    std::size_t i = 0;
    while (i < args.size()) {
        std::string_view arg = args[i];

        // Not an option flag — treat as main class (first positional).
        if (!arg.starts_with("--")) {
            break;
        }

        // Every --key requires a following value.
        if (i + 1 >= args.size()) {
            AIJVM_LOG_ERROR("option '{}' requires a value.", arg);
            print_usage(argv[0]);
            return std::nullopt;
        }

        std::string_view value = args[i + 1];

        if (arg == "--bj") {
            opts.boot_jmod_path = value;
        } else if (arg == "--cp") {
            opts.class_path = value;
        } else {
            // Unrecognized option — store for future use.
            opts.extra_options[std::string(arg)] = std::string(value);
        }
        i += 2;
    }

    // The next positional arg must be the main class.
    if (i >= args.size()) {
        AIJVM_LOG_ERROR("<MainClass> is required.");
        print_usage(argv[0]);
        return std::nullopt;
    }

    opts.main_class = std::string(args[i]);
    ++i;

    // Everything after main class becomes program_args.
    for (; i < args.size(); ++i) {
        opts.program_args.emplace_back(args[i]);
    }

    // Validate required options.
    if (opts.boot_jmod_path.empty()) {
        AIJVM_LOG_ERROR("--bj <path> is required.");
        print_usage(argv[0]);
        return std::nullopt;
    }
    if (opts.class_path.empty()) {
        AIJVM_LOG_ERROR("--cp <path> is required.");
        print_usage(argv[0]);
        return std::nullopt;
    }

    return opts;
}

}  // namespace aijvm::cli
