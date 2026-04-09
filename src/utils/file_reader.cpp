#include "utils/file_reader.h"
#include "utils/logger.h"

#include <fstream>

#if defined(_WIN32)
#include <array>
#include <cstdlib>
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace aijvm::utils {

// ============================================================================
// Internal helpers
// ============================================================================

static std::optional<std::vector<std::uint8_t>>
read_file_bytes(const std::filesystem::path& path) {
    std::error_code ec;
    auto canonical = std::filesystem::canonical(path, ec);
    if (ec) {
        AIJVM_LOG_WARN("Cannot resolve path '{}': {}", path.string(), ec.message());
        return std::nullopt;
    }

    if (!std::filesystem::is_regular_file(canonical, ec) || ec) {
        AIJVM_LOG_WARN("Not a regular file: '{}'", canonical.string());
        return std::nullopt;
    }

    std::ifstream ifs(canonical, std::ios::binary | std::ios::ate);
    if (!ifs) {
        AIJVM_LOG_WARN("Failed to open file: '{}'", canonical.string());
        return std::nullopt;
    }

    auto size = ifs.tellg();
    if (size < 0) {
        AIJVM_LOG_WARN("Failed to determine file size: '{}'", canonical.string());
        return std::nullopt;
    }

    ifs.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
    if (size > 0 && !ifs.read(reinterpret_cast<char*>(data.data()), size)) {
        AIJVM_LOG_WARN("Failed to read file: '{}'", canonical.string());
        return std::nullopt;
    }

    return data;
}

static std::filesystem::path get_home_directory() {
#if defined(_WIN32)
    // USERPROFILE is the standard home dir on Windows
    // Using _dupenv_s for thread safety
    char* buf = nullptr;
    std::size_t len = 0;
    if (_dupenv_s(&buf, &len, "USERPROFILE") == 0 && buf != nullptr) {
        std::filesystem::path home(buf);
        free(buf);
        return home;
    }
#else
    const char* home = std::getenv("HOME");  // NOLINT(concurrency-mt-unsafe)
    if (home != nullptr) {
        return std::filesystem::path(home);
    }
#endif
    return {};
}

static std::filesystem::path get_executable_directory() {
    std::error_code ec;
#if defined(__linux__)
    auto exe = std::filesystem::read_symlink("/proc/self/exe", ec);
    if (!ec) {
        return exe.parent_path();
    }
#elif defined(__APPLE__)
    // _NSGetExecutablePath approach isn't in <filesystem>, use /proc alternative
    // macOS: use realpath on argv[0] is fragile; prefer _NSGetExecutablePath
    // but for C++20 cross-platform, /proc isn't available. Use current_path fallback.
    // A more robust approach would use _NSGetExecutablePath + realpath.
    char path_buf[4096];
    uint32_t buf_size = sizeof(path_buf);
    if (_NSGetExecutablePath(path_buf, &buf_size) == 0) {
        auto exe = std::filesystem::canonical(path_buf, ec);
        if (!ec) {
            return exe.parent_path();
        }
    }
#elif defined(_WIN32)
    // On Windows, use GetModuleFileName (WinAPI)
    // Since the project prefers C++20 standard, we use a constrained approach
    wchar_t path_buf[32768];
    auto len = GetModuleFileNameW(nullptr, path_buf, sizeof(path_buf) / sizeof(wchar_t));
    if (len > 0 && len < sizeof(path_buf) / sizeof(wchar_t)) {
        auto exe = std::filesystem::path(path_buf);
        return exe.parent_path();
    }
#endif
    // Fallback: current working directory
    auto cwd = std::filesystem::current_path(ec);
    if (!ec) {
        return cwd;
    }
    return {};
}

// ============================================================================
// Public API
// ============================================================================

std::optional<std::vector<std::uint8_t>>
FileReader::read_from_absolute(const std::filesystem::path& path) {
    if (!path.is_absolute()) {
        AIJVM_LOG_WARN("Expected absolute path, got: '{}'", path.string());
        return std::nullopt;
    }
    return read_file_bytes(path);
}

std::optional<std::vector<std::uint8_t>>
FileReader::read_from_home(const std::filesystem::path& relative_path) {
    if (relative_path.is_absolute()) {
        AIJVM_LOG_WARN("Expected relative path for home-based read, got: '{}'",
                        relative_path.string());
        return std::nullopt;
    }
    auto home = get_home_directory();
    if (home.empty()) {
        AIJVM_LOG_WARN("Unable to determine user home directory");
        return std::nullopt;
    }
    return read_file_bytes(home / relative_path);
}

std::optional<std::vector<std::uint8_t>>
FileReader::read_from_executable(const std::filesystem::path& relative_path) {
    if (relative_path.is_absolute()) {
        AIJVM_LOG_WARN("Expected relative path for executable-based read, got: '{}'",
                        relative_path.string());
        return std::nullopt;
    }
    auto exe_dir = get_executable_directory();
    if (exe_dir.empty()) {
        AIJVM_LOG_WARN("Unable to determine executable directory");
        return std::nullopt;
    }
    return read_file_bytes(exe_dir / relative_path);
}

} // namespace aijvm::utils
