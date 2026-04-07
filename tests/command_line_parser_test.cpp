#include "cli/command_line_parser.h"
#include "utils/logger.h"

#include <gtest/gtest.h>

using namespace aijvm::cli;

// Initialize logger once for all tests in this file.
struct LoggerInit {
    LoggerInit() { aijvm::log::init(aijvm::log::Level::Off); }
};
static LoggerInit logger_init_;

// Helper: build an argv-style array from initializer list of C strings.
// The returned vector owns the char* pointers (they point into the literals).
static std::vector<char*> make_argv(std::initializer_list<const char*> args) {
    std::vector<char*> v;
    for (auto a : args) {
        v.push_back(const_cast<char*>(a));
    }
    return v;
}

TEST(CommandLineParserTest, FullValidInput) {
    auto argv = make_argv({"aijvm", "--bj", "/usr/lib/jvm/jmods", "--cp", "./classes", "MainClass"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    ASSERT_TRUE(opts.has_value());
    EXPECT_EQ(opts->boot_jmod_path, "/usr/lib/jvm/jmods");
    EXPECT_EQ(opts->class_path, "./classes");
    EXPECT_EQ(opts->main_class, "MainClass");
    EXPECT_TRUE(opts->program_args.empty());
    EXPECT_TRUE(opts->extra_options.empty());
}

TEST(CommandLineParserTest, OptionsInAnyOrder) {
    auto argv = make_argv({"aijvm", "--cp", "./classes", "--bj", "/jmods", "Main"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    ASSERT_TRUE(opts.has_value());
    EXPECT_EQ(opts->boot_jmod_path, "/jmods");
    EXPECT_EQ(opts->class_path, "./classes");
    EXPECT_EQ(opts->main_class, "Main");
}

TEST(CommandLineParserTest, ProgramArgsPassedThrough) {
    auto argv = make_argv({"aijvm", "--bj", "/jmods", "--cp", "./cls", "Main", "arg1", "arg2"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    ASSERT_TRUE(opts.has_value());
    ASSERT_EQ(opts->program_args.size(), 2u);
    EXPECT_EQ(opts->program_args[0], "arg1");
    EXPECT_EQ(opts->program_args[1], "arg2");
}

TEST(CommandLineParserTest, UnrecognizedOptionsStoredInMap) {
    auto argv = make_argv({
        "aijvm", "--bj", "/jmods", "--cp", "./cls",
        "--Xmx", "512m", "--verbose", "true", "Main"
    });
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    ASSERT_TRUE(opts.has_value());
    EXPECT_EQ(opts->main_class, "Main");
    ASSERT_EQ(opts->extra_options.size(), 2u);
    EXPECT_EQ(opts->extra_options.at("--Xmx"), "512m");
    EXPECT_EQ(opts->extra_options.at("--verbose"), "true");
}

TEST(CommandLineParserTest, MissingMainClassFails) {
    auto argv = make_argv({"aijvm", "--bj", "/jmods", "--cp", "./cls"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    EXPECT_FALSE(opts.has_value());
}

TEST(CommandLineParserTest, MissingBootJmodFails) {
    auto argv = make_argv({"aijvm", "--cp", "./cls", "Main"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    EXPECT_FALSE(opts.has_value());
}

TEST(CommandLineParserTest, MissingClassPathFails) {
    auto argv = make_argv({"aijvm", "--bj", "/jmods", "Main"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    EXPECT_FALSE(opts.has_value());
}

TEST(CommandLineParserTest, NoArgsFails) {
    auto argv = make_argv({"aijvm"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    EXPECT_FALSE(opts.has_value());
}

TEST(CommandLineParserTest, OptionMissingValueFails) {
    auto argv = make_argv({"aijvm", "--bj"});
    auto opts = parse_command_line(static_cast<int>(argv.size()), argv.data());

    EXPECT_FALSE(opts.has_value());
}
