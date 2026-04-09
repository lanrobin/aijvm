#include "classfile/jmod_reader.h"
#include "utils/logger.h"

#include <zip.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>

namespace aijvm::classfile {

// ── JMOD file header (4 bytes) ──────────────────────────────────────────────
// JMOD files start with: 'J' 'M' (magic), followed by major version (0x01)
// and minor version (0x00).
static constexpr std::uint8_t kJmodMagicJ       = 'J';    // 0x4A
static constexpr std::uint8_t kJmodMagicM       = 'M';    // 0x4D
static constexpr std::uint8_t kJmodVersionMajor = 0x01;
static constexpr std::uint8_t kJmodVersionMinor = 0x00;
static constexpr std::array<std::uint8_t, 4> kJmodMagic = {
    kJmodMagicJ, kJmodMagicM, kJmodVersionMajor, kJmodVersionMinor
};

// ── PIMPL ────────────────────────────────────────────────────────────────────

struct JmodReader::Impl {
    zip_t* archive = nullptr;
    std::filesystem::path file_path;
    std::int64_t num_entries = 0;

    ~Impl() {
        if (archive) {
            zip_close(archive);
        }
    }
};

// ── Factory ──────────────────────────────────────────────────────────────────

std::optional<JmodReader> JmodReader::open(const std::filesystem::path& jmod_path) {
    if (!std::filesystem::exists(jmod_path)) {
        AIJVM_LOG_ERROR("JMOD file not found: {}", jmod_path.string());
        return std::nullopt;
    }

    // Detect & skip the 4-byte JMOD magic prefix if present.
    std::int64_t zip_offset = 0;
    {
        std::ifstream ifs(jmod_path, std::ios::binary);
        if (!ifs) {
            AIJVM_LOG_ERROR("Cannot open JMOD file: {}", jmod_path.string());
            return std::nullopt;
        }
        std::array<std::uint8_t, 4> magic{};
        ifs.read(reinterpret_cast<char*>(magic.data()), magic.size());
        if (ifs.gcount() == 4 && magic == kJmodMagic) {
            zip_offset = 4;
            AIJVM_LOG_DEBUG("Detected JMOD magic header, ZIP starts at offset 4");
        }
    }

    // Open via zip_source so we can specify the offset that skips the JMOD header.
    zip_error_t zerr;
    zip_error_init(&zerr);

    zip_source_t* src = zip_source_file_create(jmod_path.string().c_str(), static_cast<zip_uint64_t>(zip_offset), -1, &zerr);
    if (!src) {
        AIJVM_LOG_ERROR("zip_source_file_create failed for {}: {}", jmod_path.string(), zip_error_strerror(&zerr));
        zip_error_fini(&zerr);
        return std::nullopt;
    }

    zip_t* archive = zip_open_from_source(src, ZIP_RDONLY, &zerr);
    if (!archive) {
        AIJVM_LOG_ERROR("zip_open_from_source failed for {}: {}", jmod_path.string(), zip_error_strerror(&zerr));
        zip_source_free(src);  // only free source if zip_open failed
        zip_error_fini(&zerr);
        return std::nullopt;
    }
    zip_error_fini(&zerr);

    JmodReader reader;
    reader.impl_ = std::make_unique<Impl>();
    reader.impl_->archive = archive;
    reader.impl_->file_path = jmod_path;
    reader.impl_->num_entries = zip_get_num_entries(archive, 0);

    AIJVM_LOG_INFO("Opened JMOD: {} ({} entries)", jmod_path.string(), reader.impl_->num_entries);
    return reader;
}

// ── Special members ──────────────────────────────────────────────────────────

JmodReader::~JmodReader() = default;
JmodReader::JmodReader(JmodReader&& other) noexcept = default;
JmodReader& JmodReader::operator=(JmodReader&& other) noexcept = default;

// ── read_file ────────────────────────────────────────────────────────────────

std::optional<std::vector<std::uint8_t>> JmodReader::read_file(std::string_view path) const {
    zip_int64_t idx = zip_name_locate(impl_->archive, std::string(path).c_str(), 0);
    if (idx < 0) {
        AIJVM_LOG_WARN("Entry not found in JMOD: {}", path);
        return std::nullopt;
    }

    zip_stat_t st;
    zip_stat_init(&st);
    if (zip_stat_index(impl_->archive, static_cast<zip_uint64_t>(idx), 0, &st) != 0) {
        AIJVM_LOG_ERROR("zip_stat_index failed for: {}", path);
        return std::nullopt;
    }

    zip_file_t* zf = zip_fopen_index(impl_->archive, static_cast<zip_uint64_t>(idx), 0);
    if (!zf) {
        AIJVM_LOG_ERROR("zip_fopen_index failed for: {}", path);
        return std::nullopt;
    }

    std::vector<std::uint8_t> buf(st.size);
    zip_int64_t bytes_read = zip_fread(zf, buf.data(), buf.size());
    zip_fclose(zf);

    if (bytes_read < 0 || static_cast<std::uint64_t>(bytes_read) != st.size) {
        AIJVM_LOG_ERROR("zip_fread returned {} for {} (expected {})", bytes_read, path, st.size);
        return std::nullopt;
    }

    return buf;
}

// ── list_files ───────────────────────────────────────────────────────────────

std::vector<JmodEntry> JmodReader::list_files(std::string_view folder, bool recursive) const {
    // Normalise: ensure folder ends with '/' for prefix matching.
    std::string prefix(folder);
    if (!prefix.empty() && prefix.back() != '/') {
        prefix += '/';
    }

    std::vector<JmodEntry> result;
    for (zip_int64_t i = 0; i < impl_->num_entries; ++i) {
        const char* name = zip_get_name(impl_->archive, static_cast<zip_uint64_t>(i), 0);
        if (!name) continue;

        std::string_view sv(name);
        if (!sv.starts_with(prefix)) continue;

        // Part after the prefix.
        std::string_view remainder = sv.substr(prefix.size());
        if (remainder.empty()) continue;  // the folder entry itself

        if (!recursive) {
            // Non-recursive: only direct children (no '/' in remainder, or exactly ends with '/').
            auto slash_pos = remainder.find('/');
            if (slash_pos != std::string_view::npos && slash_pos != remainder.size() - 1) {
                continue;
            }
        }

        zip_stat_t st;
        zip_stat_init(&st);
        zip_stat_index(impl_->archive, static_cast<zip_uint64_t>(i), 0, &st);

        result.push_back({
            .name = std::string(sv),
            .uncompressed_size = (st.valid & ZIP_STAT_SIZE) ? st.size : 0,
            .is_directory = (!sv.empty() && sv.back() == '/'),
        });
    }
    return result;
}

// ── search ───────────────────────────────────────────────────────────────────

std::vector<std::string> JmodReader::search(std::string_view filename, std::string_view folder) const {
    std::string prefix(folder);
    if (!prefix.empty() && prefix.back() != '/') {
        prefix += '/';
    }

    std::vector<std::string> matches;
    for (zip_int64_t i = 0; i < impl_->num_entries; ++i) {
        const char* name = zip_get_name(impl_->archive, static_cast<zip_uint64_t>(i), 0);
        if (!name) continue;

        std::string_view sv(name);
        if (!prefix.empty() && !sv.starts_with(prefix)) continue;

        // Match: entry ends with "/<filename>" or equals "<filename>" exactly.
        if (sv == filename) {
            matches.emplace_back(sv);
        } else if (sv.size() > filename.size()) {
            auto tail = sv.substr(sv.size() - filename.size() - 1);
            if (tail.front() == '/' && tail.substr(1) == filename) {
                matches.emplace_back(sv);
            }
        }
    }
    return matches;
}

// ── extract_all ──────────────────────────────────────────────────────────────

bool JmodReader::extract_all(const std::filesystem::path& output_dir) const {
    if (output_dir.empty()) {
        AIJVM_LOG_ERROR("extract_all: output directory must be provided");
        return false;
    }

    for (zip_int64_t i = 0; i < impl_->num_entries; ++i) {
        const char* name = zip_get_name(impl_->archive, static_cast<zip_uint64_t>(i), 0);
        if (!name) continue;

        std::string_view sv(name);
        std::filesystem::path dest = output_dir / sv;

        // Directory entry.
        if (!sv.empty() && sv.back() == '/') {
            std::filesystem::create_directories(dest);
            continue;
        }

        // File entry — ensure parent directory exists.
        std::filesystem::create_directories(dest.parent_path());

        auto content = read_file(sv);
        if (!content) {
            AIJVM_LOG_ERROR("extract_all: failed to read entry: {}", sv);
            return false;
        }

        std::ofstream ofs(dest, std::ios::binary);
        if (!ofs) {
            AIJVM_LOG_ERROR("extract_all: cannot create file: {}", dest.string());
            return false;
        }
        ofs.write(reinterpret_cast<const char*>(content->data()),
                  static_cast<std::streamsize>(content->size()));
    }

    AIJVM_LOG_INFO("Extracted {} entries to {}", impl_->num_entries, output_dir.string());
    return true;
}

// ── Accessors ────────────────────────────────────────────────────────────────

const std::filesystem::path& JmodReader::path() const {
    return impl_->file_path;
}

std::size_t JmodReader::entry_count() const {
    return static_cast<std::size_t>(impl_->num_entries);
}

}  // namespace aijvm::classfile
