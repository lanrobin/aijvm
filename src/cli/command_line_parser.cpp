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

        // Not an option flag — check for -X style options or treat as main class.
        if (!arg.starts_with("--")) {
            // Parse -Xmx<size> (e.g., -Xmx64M, -Xmx256m, -Xmx1G)
            if (arg.starts_with("-Xmx")) {
                auto size_str = arg.substr(4);
                std::size_t multiplier = 1;
                if (size_str.ends_with("K") || size_str.ends_with("k")) {
                    multiplier = 1024;
                    size_str = size_str.substr(0, size_str.size() - 1);
                } else if (size_str.ends_with("M") || size_str.ends_with("m")) {
                    multiplier = 1024 * 1024;
                    size_str = size_str.substr(0, size_str.size() - 1);
                } else if (size_str.ends_with("G") || size_str.ends_with("g")) {
                    multiplier = 1024ULL * 1024 * 1024;
                    size_str = size_str.substr(0, size_str.size() - 1);
                }
                std::size_t val = 0;
                for (char c : size_str) {
                    if (c < '0' || c > '9') {
                        AIJVM_LOG_ERROR("Invalid -Xmx value: {}", arg);
                        return std::nullopt;
                    }
                    val = val * 10 + static_cast<std::size_t>(c - '0');
                }
                opts.max_heap_size = val * multiplier;
                ++i;
                continue;
            }
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
