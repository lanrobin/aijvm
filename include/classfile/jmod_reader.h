#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace aijvm::classfile {

/// Metadata for a single entry inside a JMOD/ZIP archive.
struct JmodEntry {
    std::string name;                 // Full path (e.g. "classes/java/lang/Object.class")
    std::uint64_t uncompressed_size;  // Original size in bytes
    bool is_directory;
};

/// Reads a .jmod file (ZIP with a 4-byte JMOD magic prefix).
///
/// Standard JMOD internal layout:
///   bin/  classes/  conf/  lib/  include/  legal/  man/
class JmodReader {
public:
    /// Open a .jmod file. Returns std::nullopt on failure (logged via spdlog).
    [[nodiscard]] static std::optional<JmodReader> open(const std::filesystem::path& jmod_path);

    ~JmodReader();
    JmodReader(JmodReader&& other) noexcept;
    JmodReader& operator=(JmodReader&& other) noexcept;
    JmodReader(const JmodReader&) = delete;
    JmodReader& operator=(const JmodReader&) = delete;

    /// Read a specific file by its full archive path and return its content.
    /// e.g. read_file("classes/java/lang/Object.class")
    [[nodiscard]] std::optional<std::vector<std::uint8_t>> read_file(std::string_view path) const;

    /// List entries under a folder (relative to archive root, e.g. "classes/java/lang").
    /// @param recursive  true = include all subdirectory entries.
    [[nodiscard]] std::vector<JmodEntry> list_files(std::string_view folder,
                                                     bool recursive = false) const;

    /// Search for a file by name. Returns all matching full paths.
    /// @param filename   e.g. "Object.class"
    /// @param folder     Optional prefix to restrict search (e.g. "classes"). Empty = root.
    [[nodiscard]] std::vector<std::string> search(std::string_view filename,
                                                   std::string_view folder = "") const;

    /// Extract every entry to output_dir, preserving the internal directory tree.
    /// @return true on success.
    bool extract_all(const std::filesystem::path& output_dir) const;

    /// The filesystem path this reader was opened from.
    [[nodiscard]] const std::filesystem::path& path() const;

    /// Total number of entries (files + directories) in the archive.
    [[nodiscard]] std::size_t entry_count() const;

private:
    JmodReader() = default;
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace aijvm::classfile
