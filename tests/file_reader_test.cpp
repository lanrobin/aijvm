#include "utils/file_reader.h"
#include "utils/logger.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace aijvm::utils {
namespace {

class FileReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        aijvm::log::init();
        // Create a temp directory for test files
        tmp_dir_ = std::filesystem::temp_directory_path() / "aijvm_file_reader_test";
        std::filesystem::create_directories(tmp_dir_);

        // Write a test file
        test_file_ = tmp_dir_ / "test.bin";
        std::ofstream ofs(test_file_, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(test_content_.data()),
                  static_cast<std::streamsize>(test_content_.size()));
    }

    void TearDown() override {
        std::error_code ec;
        std::filesystem::remove_all(tmp_dir_, ec);
    }

    std::filesystem::path tmp_dir_;
    std::filesystem::path test_file_;
    std::vector<std::uint8_t> test_content_ = {0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x01};
};

// ============================================================================
// read_from_absolute
// ============================================================================

TEST_F(FileReaderTest, ReadAbsolute_ValidFile) {
    auto result = FileReader::read_from_absolute(test_file_);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, test_content_);
}

TEST_F(FileReaderTest, ReadAbsolute_NonExistentFile) {
    auto result = FileReader::read_from_absolute(tmp_dir_ / "nonexistent.bin");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileReaderTest, ReadAbsolute_RejectsRelativePath) {
    auto result = FileReader::read_from_absolute("relative/path.bin");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileReaderTest, ReadAbsolute_Directory) {
    auto result = FileReader::read_from_absolute(tmp_dir_);
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileReaderTest, ReadAbsolute_EmptyFile) {
    auto empty_file = tmp_dir_ / "empty.bin";
    { std::ofstream ofs(empty_file, std::ios::binary); }
    auto result = FileReader::read_from_absolute(empty_file);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}

// ============================================================================
// read_from_home
// ============================================================================

TEST_F(FileReaderTest, ReadHome_RejectsAbsolutePath) {
    auto result = FileReader::read_from_home("/absolute/path.bin");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileReaderTest, ReadHome_ValidRelativePath) {
    // Create a file in $HOME for testing
#if defined(_WIN32)
    char* home_buf = nullptr;
    std::size_t home_len = 0;
    _dupenv_s(&home_buf, &home_len, "USERPROFILE");
    if (home_buf == nullptr) {
        GTEST_SKIP() << "USERPROFILE not set";
    }
    auto home = std::filesystem::path(home_buf);
    free(home_buf);
#else
    auto home_env = std::getenv("HOME");  // NOLINT(concurrency-mt-unsafe)
    if (home_env == nullptr) {
        GTEST_SKIP() << "HOME not set";
    }
    auto home = std::filesystem::path(home_env);
#endif
    auto test_subdir = home / ".aijvm_test_tmp";
    std::filesystem::create_directories(test_subdir);
    auto home_test_file = test_subdir / "test_home_read.bin";
    {
        std::ofstream ofs(home_test_file, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(test_content_.data()),
                  static_cast<std::streamsize>(test_content_.size()));
    }

    auto result = FileReader::read_from_home(".aijvm_test_tmp/test_home_read.bin");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, test_content_);

    // Cleanup
    std::error_code ec;
    std::filesystem::remove_all(test_subdir, ec);
}

// ============================================================================
// read_from_executable
// ============================================================================

TEST_F(FileReaderTest, ReadExecutable_RejectsAbsolutePath) {
    auto result = FileReader::read_from_executable("/absolute/path.bin");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileReaderTest, ReadExecutable_ValidRelativePath) {
    // The test binary itself exists relative to the executable dir
    // Get the executable directory and place a test file there
    auto exe_path = std::filesystem::read_symlink("/proc/self/exe");
    auto exe_dir = exe_path.parent_path();
    auto test_file = exe_dir / "filereader_test_tmp.bin";
    {
        std::ofstream ofs(test_file, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(test_content_.data()),
                  static_cast<std::streamsize>(test_content_.size()));
    }

    auto result = FileReader::read_from_executable("filereader_test_tmp.bin");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, test_content_);

    // Cleanup
    std::error_code ec;
    std::filesystem::remove(test_file, ec);
}

TEST_F(FileReaderTest, ReadExecutable_NonExistentFile) {
    auto result = FileReader::read_from_executable("this_file_does_not_exist.xyz");
    EXPECT_FALSE(result.has_value());
}

// ============================================================================
// Integration: read a real .class file
// ============================================================================

TEST_F(FileReaderTest, ReadRealClassFile) {
    auto class_path = std::filesystem::path(__FILE__).parent_path() / "javaclasses" / "HelloWorld.class";
    if (!std::filesystem::exists(class_path)) {
        GTEST_SKIP() << "HelloWorld.class not found";
    }

    auto result = FileReader::read_from_absolute(class_path);
    ASSERT_TRUE(result.has_value());
    ASSERT_GE(result->size(), 4u);
    // Check magic number
    EXPECT_EQ((*result)[0], 0xCA);
    EXPECT_EQ((*result)[1], 0xFE);
    EXPECT_EQ((*result)[2], 0xBA);
    EXPECT_EQ((*result)[3], 0xBE);
}

} // anonymous namespace
} // namespace aijvm::utils
