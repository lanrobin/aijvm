#pragma once

#include <spdlog/spdlog.h>

#include <string_view>

namespace aijvm::log {

/// Log levels matching spdlog levels, exposed for global control.
enum class Level { Trace, Debug, Info, Warn, Error, Critical, Off };

/// Initialize the logging subsystem.
/// Must be called once at startup before any logging.
///
/// Creates the following sinks:
///   - logs/log_debug.log   (debug+  — all messages)
///   - logs/log_info.log    (info+)
///   - logs/log_warn.log    (warn+)
///   - logs/log_error.log   (error+)
///   - stderr console sink  (warn+ with colored output: yellow=warn, red=error)
///
/// All file sinks use rotating files capped at 512 MB with 5 backup files.
///
/// @param global_level  The minimum level for the entire logger.
void init(Level global_level = Level::Debug);

/// Change the global log level at runtime.
void set_level(Level level);

/// Convenience macros that embed source location (file, line, function).
/// Usage:  AIJVM_LOG_INFO("Loaded class {}", class_name);

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define AIJVM_LOG_TRACE(...)    SPDLOG_TRACE(__VA_ARGS__)
#define AIJVM_LOG_DEBUG(...)    SPDLOG_DEBUG(__VA_ARGS__)
#define AIJVM_LOG_INFO(...)     SPDLOG_INFO(__VA_ARGS__)
#define AIJVM_LOG_WARN(...)     SPDLOG_WARN(__VA_ARGS__)
#define AIJVM_LOG_ERROR(...)    SPDLOG_ERROR(__VA_ARGS__)
#define AIJVM_LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
// NOLINTEND(cppcoreguidelines-macro-usage)

}  // namespace aijvm::log
