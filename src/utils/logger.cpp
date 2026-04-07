#include "utils/logger.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <memory>
#include <vector>

namespace aijvm::log {

namespace {

spdlog::level::level_enum to_spdlog_level(Level level) {
    switch (level) {
        case Level::Trace:    return spdlog::level::trace;
        case Level::Debug:    return spdlog::level::debug;
        case Level::Info:     return spdlog::level::info;
        case Level::Warn:     return spdlog::level::warn;
        case Level::Error:    return spdlog::level::err;
        case Level::Critical: return spdlog::level::critical;
        case Level::Off:      return spdlog::level::off;
    }
    return spdlog::level::info;
}

}  // namespace

void init(Level global_level) {
    // Ensure logs directory exists.
    std::filesystem::create_directories("logs");

    // Pattern: [2026-04-07 12:34:56.789] [thread 12345] [info] [source.cpp:42 function_name] message
    const std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] [%s:%# %!] %v";

    constexpr std::size_t max_size  = 512 * 1024 * 1024;  // 512 MB
    constexpr std::size_t max_files = 5;

    // Rotating file sinks at different levels.
    auto debug_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log_debug.log", max_size, max_files);
    debug_sink->set_level(spdlog::level::debug);

    auto info_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log_info.log", max_size, max_files);
    info_sink->set_level(spdlog::level::info);

    auto warn_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log_warn.log", max_size, max_files);
    warn_sink->set_level(spdlog::level::warn);

    auto error_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log_error.log", max_size, max_files);
    error_sink->set_level(spdlog::level::err);

    // Console sink: warn+ with colors (red=error, yellow=warn).
    auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);

    std::vector<spdlog::sink_ptr> sinks{
        debug_sink, info_sink, warn_sink, error_sink, console_sink};

    auto logger = std::make_shared<spdlog::logger>("aijvm", sinks.begin(), sinks.end());
    logger->set_level(to_spdlog_level(global_level));
    logger->set_pattern(pattern);

    // Register as the default logger so SPDLOG_* macros use it.
    spdlog::set_default_logger(std::move(logger));
    spdlog::flush_on(spdlog::level::warn);
}

void set_level(Level level) {
    spdlog::set_level(to_spdlog_level(level));
}

}  // namespace aijvm::log
