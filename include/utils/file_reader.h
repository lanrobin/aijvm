#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace aijvm::utils {

/// Utility class with static methods for reading files into byte vectors.
class FileReader {
public:
    FileReader() = delete;

    /// Read a file from an absolute path.
    /// @param path Absolute path to the file.
    /// @return File contents as bytes, or std::nullopt on failure.
    static std::optional<std::vector<std::uint8_t>>
    read_from_absolute(const std::filesystem::path& path);

    /// Read a file relative to the user's home directory.
    /// @param relative_path Path relative to $HOME (Linux/macOS) or %USERPROFILE% (Windows).
    /// @return File contents as bytes, or std::nullopt on failure.
    static std::optional<std::vector<std::uint8_t>>
    read_from_home(const std::filesystem::path& relative_path);

    /// Read a file relative to the directory containing the running executable.
    /// @param relative_path Path relative to the executable's parent directory.
    /// @return File contents as bytes, or std::nullopt on failure.
    static std::optional<std::vector<std::uint8_t>>
    read_from_executable(const std::filesystem::path& relative_path);
};

} // namespace aijvm::utils
