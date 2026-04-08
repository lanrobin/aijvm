#include "classfile/jmod_reader.h"
#include "utils/logger.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>

using namespace aijvm::classfile;
namespace fs = std::filesystem;

// The test jmod shipped with OpenJDK 25.
static constexpr auto kJmodPath = "/usr/lib/jvm/java-25-openjdk-amd64/jmods/java.base.jmod";

// Initialize logger once (suppressed during tests).
struct LoggerInit {
    LoggerInit() { aijvm::log::init(aijvm::log::Level::Off); }
};
static LoggerInit logger_init_;

// ── Open / basic accessors ───────────────────────────────────────────────────

TEST(JmodReaderTest, OpenValidJmod) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());
    EXPECT_EQ(reader->path(), kJmodPath);
    EXPECT_GT(reader->entry_count(), 100u);
}

TEST(JmodReaderTest, OpenNonexistentFails) {
    auto reader = JmodReader::open("/tmp/nonexistent_file.jmod");
    EXPECT_FALSE(reader.has_value());
}

// ── read_file ────────────────────────────────────────────────────────────────

TEST(JmodReaderTest, ReadKnownClassFile) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    // java.lang.Object.class must exist in every java.base.jmod
    auto data = reader->read_file("classes/java/lang/Object.class");
    ASSERT_TRUE(data.has_value());
    EXPECT_GT(data->size(), 4u);

    // First 4 bytes of any .class file: 0xCAFEBABE
    EXPECT_EQ((*data)[0], 0xCA);
    EXPECT_EQ((*data)[1], 0xFE);
    EXPECT_EQ((*data)[2], 0xBA);
    EXPECT_EQ((*data)[3], 0xBE);
}

TEST(JmodReaderTest, ReadNonexistentEntryReturnsNullopt) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto data = reader->read_file("classes/does/not/Exist.class");
    EXPECT_FALSE(data.has_value());
}

// ── list_files ───────────────────────────────────────────────────────────────

TEST(JmodReaderTest, ListFilesNonRecursive) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    // "classes/java/lang" should have direct children like Object.class, String.class, etc.
    auto entries = reader->list_files("classes/java/lang", /*recursive=*/false);
    EXPECT_GT(entries.size(), 10u);

    // None of them should contain an extra '/' past the prefix (except trailing '/' for dirs).
    for (const auto& e : entries) {
        std::string_view after = std::string_view(e.name).substr(std::string_view("classes/java/lang/").size());
        auto slash = after.find('/');
        if (slash != std::string_view::npos) {
            EXPECT_EQ(slash, after.size() - 1) << "Non-recursive list leaked: " << e.name;
        }
    }
}

TEST(JmodReaderTest, ListFilesRecursive) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto non_recursive = reader->list_files("classes/java/lang", false);
    auto recursive      = reader->list_files("classes/java/lang", true);

    // Recursive must contain at least as many entries (sub-packages like annotation/, invoke/ etc.)
    EXPECT_GE(recursive.size(), non_recursive.size());
}

TEST(JmodReaderTest, ListTopLevelFolders) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    // This jmod has no explicit directory entries at the top level.
    // Listing root non-recursively returns direct children (files like "bin/java").
    auto entries = reader->list_files("bin", false);
    EXPECT_GE(entries.size(), 1u);

    bool has_java = std::any_of(entries.begin(), entries.end(),
        [](const JmodEntry& e) { return e.name == "bin/java"; });
    EXPECT_TRUE(has_java);
}

// ── search ───────────────────────────────────────────────────────────────────

TEST(JmodReaderTest, SearchFromRoot) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto results = reader->search("Object.class");
    EXPECT_GE(results.size(), 1u);

    bool found_lang = std::any_of(results.begin(), results.end(),
        [](const std::string& s) { return s == "classes/java/lang/Object.class"; });
    EXPECT_TRUE(found_lang);
}

TEST(JmodReaderTest, SearchWithinFolder) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto results = reader->search("Object.class", "classes/java/lang");
    ASSERT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0], "classes/java/lang/Object.class");
}

TEST(JmodReaderTest, SearchNonexistentFile) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto results = reader->search("ThisDoesNotExist12345.class");
    EXPECT_TRUE(results.empty());
}

// ── extract_all ──────────────────────────────────────────────────────────────

TEST(JmodReaderTest, ExtractAllCreatesFiles) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    // Use a unique temp dir so tests don't interfere.
    fs::path output = fs::temp_directory_path() / "aijvm_jmod_extract_test";
    fs::remove_all(output);  // clean slate

    ASSERT_TRUE(reader->extract_all(output));

    // Verify a known file was extracted.
    fs::path obj_class = output / "classes" / "java" / "lang" / "Object.class";
    EXPECT_TRUE(fs::exists(obj_class));
    EXPECT_GT(fs::file_size(obj_class), 0u);

    // Cleanup.
    fs::remove_all(output);
}

TEST(JmodReaderTest, ExtractAllEmptyDirFails) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    EXPECT_FALSE(reader->extract_all(""));
}

// ── Move semantics ───────────────────────────────────────────────────────────

TEST(JmodReaderTest, MoveConstruction) {
    auto reader = JmodReader::open(kJmodPath);
    ASSERT_TRUE(reader.has_value());

    auto count = reader->entry_count();
    JmodReader moved(std::move(*reader));
    EXPECT_EQ(moved.entry_count(), count);
}
