#include <gtest/gtest.h>
#include <filesystem>
#include "ClassFile.h"

// ── Helpers ───────────────────────────────────────────────────────────────────

static const std::filesystem::path kDataDir = TEST_DATA_DIR;

static std::filesystem::path classFile(const char* name)
{
    return kDataDir / name;
}

// Builds a synthetic class file header for error-path tests only.
// cp_count=1 means an empty constant pool (JVM indices start at 1).
static std::vector<u1> makeSyntheticClassFile(
    u4 magic      = 0xCAFEBABE,
    u2 major      = 69,
    u2 cp_count   = 1,
    u2 access     = 0x0021)
{
    return {
        u1(magic >> 24), u1(magic >> 16), u1(magic >> 8), u1(magic),
        0x00, 0x00,
        u1(major >> 8),  u1(major & 0xFF),
        u1(cp_count >> 8), u1(cp_count & 0xFF),
        u1(access >> 8), u1(access & 0xFF),
        0x00, 0x00, 0x00, 0x00,  // this_class, super_class
        0x00, 0x00,              // interfaces_count
        0x00, 0x00,              // fields_count
        0x00, 0x00,              // methods_count
        0x00, 0x00,              // attributes_count
    };
}

// ── Error conditions (synthetic data) ────────────────────────────────────────

TEST(ClassReaderErrorTest, InvalidMagicNumberThrows)
{
    auto bytes = makeSyntheticClassFile(0xDEADBEEF);
    ClassReader reader(bytes);
    EXPECT_THROW(reader.parse(), std::runtime_error);
}

TEST(ClassReaderErrorTest, MagicOffByOneThrows)
{
    auto bytes = makeSyntheticClassFile(0xCAFEBABF);
    ClassReader reader(bytes);
    EXPECT_THROW(reader.parse(), std::runtime_error);
}

TEST(ClassReaderErrorTest, EmptyBufferThrows)
{
    ClassReader reader(std::vector<u1>{});
    EXPECT_THROW(reader.parse(), std::out_of_range);
}

TEST(ClassReaderErrorTest, TruncatedAfterMagicThrows)
{
    ClassReader reader(std::vector<u1>{ 0xCA, 0xFE, 0xBA, 0xBE });
    EXPECT_THROW(reader.parse(), std::out_of_range);
}

TEST(ClassReaderErrorTest, TruncatedMidConstantPoolThrows)
{
    // cp_count=2 means one entry expected; provide tag 0x01 (Utf8) but no length
    ClassReader reader(std::vector<u1>{
        0xCA, 0xFE, 0xBA, 0xBE,
        0x00, 0x00, 0x00, 0x45,  // minor=0, major=69
        0x00, 0x02,              // cp_count=2
        0x01,                    // tag=CONSTANT_Utf8, no length follows
    });
    EXPECT_THROW(reader.parse(), std::out_of_range);
}

TEST(ClassReaderErrorTest, UnknownConstantTagThrows)
{
    ClassReader reader(std::vector<u1>{
        0xCA, 0xFE, 0xBA, 0xBE,
        0x00, 0x00, 0x00, 0x45,
        0x00, 0x02,              // cp_count=2
        0xFF,                    // invalid tag
    });
    EXPECT_THROW(reader.parse(), std::runtime_error);
}

// ── File-path constructor error tests ────────────────────────────────────────

TEST(ClassReaderFileErrorTest, NonExistentPathThrows)
{
    EXPECT_THROW(
        ClassReader(std::filesystem::path("/nonexistent/path/Foo.class")),
        std::runtime_error
    );
}

TEST(ClassReaderFileErrorTest, DirectoryPathThrows)
{
    EXPECT_THROW(
        ClassReader(std::filesystem::temp_directory_path()),
        std::runtime_error
    );
}

// ── Parameterized tests — all three real class files ─────────────────────────

class RealClassFileTest : public ::testing::TestWithParam<const char*> {};

INSTANTIATE_TEST_SUITE_P(OpenJDK25, RealClassFileTest,
    ::testing::Values("Object.class", "String.class", "System.class"));

TEST_P(RealClassFileTest, ParsesSuccessfully)
{
    EXPECT_NO_THROW(ClassReader(classFile(GetParam())).parse());
}

TEST_P(RealClassFileTest, MagicIsCAFEBABE)
{
    auto cf = ClassReader(classFile(GetParam())).parse();
    EXPECT_EQ(cf->magic, 0xCAFEBABEu);
}

TEST_P(RealClassFileTest, MajorVersionIsJava25)
{
    auto cf = ClassReader(classFile(GetParam())).parse();
    EXPECT_EQ(cf->major_version, 69);  // 44 + 25 = 69
}

TEST_P(RealClassFileTest, MinorVersionIsZero)
{
    auto cf = ClassReader(classFile(GetParam())).parse();
    EXPECT_EQ(cf->minor_version, 0);
}

TEST_P(RealClassFileTest, ConstantPoolIsPopulated)
{
    auto cf = ClassReader(classFile(GetParam())).parse();
    EXPECT_GT(cf->constant_pool_count, 1);
}

// ── Class-specific structural tests ──────────────────────────────────────────

// java.lang.Object — no superclass (super_class index = 0), no interfaces, no fields
TEST(ObjectClassTest, IsPublicSuper)
{
    auto cf = ClassReader(classFile("Object.class")).parse();
    EXPECT_EQ(cf->access_flags, 0x0021);  // ACC_PUBLIC | ACC_SUPER
}

TEST(ObjectClassTest, HasNoSuperClass)
{
    auto cf = ClassReader(classFile("Object.class")).parse();
    EXPECT_EQ(cf->super_class, 0);  // Object has no parent
}

TEST(ObjectClassTest, HasNoInterfaces)
{
    auto cf = ClassReader(classFile("Object.class")).parse();
    EXPECT_EQ(cf->interfaces_count, 0);
    EXPECT_TRUE(cf->interfaces.empty());
}

TEST(ObjectClassTest, HasNoFields)
{
    auto cf = ClassReader(classFile("Object.class")).parse();
    EXPECT_EQ(cf->fields_count, 0);
}

TEST(ObjectClassTest, ConstantPoolCount)
{
    auto cf = ClassReader(classFile("Object.class")).parse();
    EXPECT_EQ(cf->constant_pool_count, 115);
}

// java.lang.String — final class, implements 5 interfaces, has 11 fields
TEST(StringClassTest, IsPublicFinalSuper)
{
    auto cf = ClassReader(classFile("String.class")).parse();
    EXPECT_EQ(cf->access_flags, 0x0031);  // ACC_PUBLIC | ACC_FINAL | ACC_SUPER
}

TEST(StringClassTest, HasSuperClass)
{
    auto cf = ClassReader(classFile("String.class")).parse();
    EXPECT_GT(cf->super_class, 0);
}

TEST(StringClassTest, ImplementsFiveInterfaces)
{
    auto cf = ClassReader(classFile("String.class")).parse();
    EXPECT_EQ(cf->interfaces_count, 5);
    EXPECT_EQ(cf->interfaces.size(), 5u);
}

TEST(StringClassTest, HasElevenFields)
{
    auto cf = ClassReader(classFile("String.class")).parse();
    EXPECT_EQ(cf->fields_count, 11);
}

TEST(StringClassTest, ConstantPoolCount)
{
    auto cf = ClassReader(classFile("String.class")).parse();
    EXPECT_EQ(cf->constant_pool_count, 1471);
}

// java.lang.System — final class, no interfaces, 10 fields
TEST(SystemClassTest, IsPublicFinalSuper)
{
    auto cf = ClassReader(classFile("System.class")).parse();
    EXPECT_EQ(cf->access_flags, 0x0031);  // ACC_PUBLIC | ACC_FINAL | ACC_SUPER
}

TEST(SystemClassTest, HasNoInterfaces)
{
    auto cf = ClassReader(classFile("System.class")).parse();
    EXPECT_EQ(cf->interfaces_count, 0);
    EXPECT_TRUE(cf->interfaces.empty());
}

TEST(SystemClassTest, HasTenFields)
{
    auto cf = ClassReader(classFile("System.class")).parse();
    EXPECT_EQ(cf->fields_count, 10);
}

TEST(SystemClassTest, ConstantPoolCount)
{
    auto cf = ClassReader(classFile("System.class")).parse();
    EXPECT_EQ(cf->constant_pool_count, 591);
}
