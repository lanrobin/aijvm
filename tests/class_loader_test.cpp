#include "classloader/class_loader.h"
#include "classfile/class_file.h"
#include "utils/logger.h"

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace aijvm::classloader {
namespace {

// Helper: find the JDK jmods directory
static std::filesystem::path find_jmods_dir() {
    // Try common JDK locations
    for (const auto& candidate : {
             "/usr/lib/jvm/java-21-openjdk-amd64/jmods",
             "/usr/lib/jvm/java-25-openjdk-amd64/jmods",
             "/usr/lib/jvm/java-17-openjdk-amd64/jmods",
         }) {
        if (std::filesystem::exists(std::filesystem::path(candidate) / "java.base.jmod")) {
            return candidate;
        }
    }
    return {};
}

// Helper: path to test javaclasses directory
static std::filesystem::path get_test_classes_dir() {
    auto path = std::filesystem::path(__FILE__).parent_path() / "javaclasses";
    if (std::filesystem::exists(path)) {
        return path;
    }
    return std::filesystem::path("tests/javaclasses");
}

// ============================================================================
// System class loader tests (java.base.jmod)
// ============================================================================

TEST(ClassLoaderTest, LoadSystemClass_ArrayList) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }

    ClassLoader loader(jmods, "/nonexistent");
    auto cf = loader.load_class("java/util/ArrayList");
    ASSERT_NE(cf, nullptr);

    auto* this_cls = dynamic_cast<const classfile::CONSTANT_Class_info*>(
        cf->constant_pool[cf->this_class].get());
    ASSERT_NE(this_cls, nullptr);
    EXPECT_EQ(cf->get_utf8(this_cls->name_index), "java/util/ArrayList");
}

TEST(ClassLoaderTest, LoadSystemClass_Object) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }

    ClassLoader loader(jmods, "/nonexistent");
    auto cf = loader.load_class("java/lang/Object");
    ASSERT_NE(cf, nullptr);

    auto* this_cls = dynamic_cast<const classfile::CONSTANT_Class_info*>(
        cf->constant_pool[cf->this_class].get());
    ASSERT_NE(this_cls, nullptr);
    EXPECT_EQ(cf->get_utf8(this_cls->name_index), "java/lang/Object");
    // Object has no super class
    EXPECT_EQ(cf->super_class, 0u);
}

TEST(ClassLoaderTest, LoadSystemClass_NotFound) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }

    ClassLoader loader(jmods, "/nonexistent");
    auto cf = loader.load_class("com/nonexistent/FakeClass");
    EXPECT_EQ(cf, nullptr);
}

// ============================================================================
// Customer class loader tests (--cp directory)
// ============================================================================

TEST(ClassLoaderTest, LoadCustomerClass_HelloWorld) {
    auto test_classes = get_test_classes_dir();
    if (!std::filesystem::exists(test_classes / "HelloWorld.class")) {
        GTEST_SKIP() << "HelloWorld.class not found";
    }

    // Use an invalid jmods path so system loader fails, forcing customer loader
    ClassLoader loader("/nonexistent_jmods", test_classes);
    auto cf = loader.load_class("HelloWorld");
    ASSERT_NE(cf, nullptr);

    auto* this_cls = dynamic_cast<const classfile::CONSTANT_Class_info*>(
        cf->constant_pool[cf->this_class].get());
    ASSERT_NE(this_cls, nullptr);
    EXPECT_EQ(cf->get_utf8(this_cls->name_index), "HelloWorld");
}

TEST(ClassLoaderTest, LoadCustomerClass_NotFound) {
    auto test_classes = get_test_classes_dir();
    ClassLoader loader("/nonexistent_jmods", test_classes);
    auto cf = loader.load_class("NonExistentClass");
    EXPECT_EQ(cf, nullptr);
}

// ============================================================================
// Delegation: system loader first, then customer
// ============================================================================

TEST(ClassLoaderTest, DelegationOrder_SystemFirst) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }
    auto test_classes = get_test_classes_dir();

    ClassLoader loader(jmods, test_classes);

    // java/lang/String should come from system loader
    auto cf = loader.load_class("java/lang/String");
    ASSERT_NE(cf, nullptr);

    auto* this_cls = dynamic_cast<const classfile::CONSTANT_Class_info*>(
        cf->constant_pool[cf->this_class].get());
    ASSERT_NE(this_cls, nullptr);
    EXPECT_EQ(cf->get_utf8(this_cls->name_index), "java/lang/String");
}

TEST(ClassLoaderTest, DelegationOrder_FallbackToCustomer) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }
    auto test_classes = get_test_classes_dir();
    if (!std::filesystem::exists(test_classes / "HelloWorld.class")) {
        GTEST_SKIP() << "HelloWorld.class not found";
    }

    ClassLoader loader(jmods, test_classes);

    // HelloWorld is not in java.base.jmod, should fall through to customer loader
    auto cf = loader.load_class("HelloWorld");
    ASSERT_NE(cf, nullptr);

    auto* this_cls = dynamic_cast<const classfile::CONSTANT_Class_info*>(
        cf->constant_pool[cf->this_class].get());
    ASSERT_NE(this_cls, nullptr);
    EXPECT_EQ(cf->get_utf8(this_cls->name_index), "HelloWorld");
}

// ============================================================================
// Caching
// ============================================================================

TEST(ClassLoaderTest, CachingWorks) {
    auto jmods = find_jmods_dir();
    if (jmods.empty()) {
        GTEST_SKIP() << "JDK jmods directory not found";
    }

    ClassLoader loader(jmods, "/nonexistent");

    EXPECT_FALSE(loader.is_loaded("java/util/HashMap"));

    auto cf1 = loader.load_class("java/util/HashMap");
    ASSERT_NE(cf1, nullptr);
    EXPECT_TRUE(loader.is_loaded("java/util/HashMap"));

    // Second load should return the same pointer (cached)
    auto cf2 = loader.load_class("java/util/HashMap");
    EXPECT_EQ(cf1.get(), cf2.get());
}

TEST(ClassLoaderTest, IsLoadedReturnsFalseForUnloaded) {
    ClassLoader loader("/nonexistent_jmods", "/nonexistent");
    EXPECT_FALSE(loader.is_loaded("java/lang/Object"));
}

// ============================================================================
// Invalid boot path
// ============================================================================

TEST(ClassLoaderTest, InvalidBootPath_GracefulDegradation) {
    // Should not crash, just fail to load system classes
    ClassLoader loader("/totally/invalid/path", "/also/invalid");
    auto cf = loader.load_class("java/lang/Object");
    EXPECT_EQ(cf, nullptr);
}

} // anonymous namespace
} // namespace aijvm::classloader
