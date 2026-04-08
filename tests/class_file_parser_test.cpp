#include "classfile/class_file.h"

#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>

namespace aijvm::classfile {
namespace {

// Helper: load a .class file into a byte vector
static std::vector<std::uint8_t> load_class_file(const std::filesystem::path& path) {
    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    EXPECT_TRUE(ifs.is_open()) << "Failed to open: " << path;
    auto size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
    ifs.read(reinterpret_cast<char*>(data.data()), size);
    return data;
}

// Path to test class files (relative to test binary working directory)
static std::filesystem::path get_test_class_path() {
    // The test binary may be in build/tests/, class files in tests/javaclasses/
    auto path = std::filesystem::path(__FILE__).parent_path() / "javaclasses";
    if (std::filesystem::exists(path / "HelloWorld.class")) {
        return path;
    }
    // Fallback: try relative to current directory
    return std::filesystem::path("tests/javaclasses");
}

// ============================================================================
// Test: Invalid magic number
// ============================================================================
TEST(ClassFileTest, InvalidMagicNumber) {
    std::vector<std::uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};
    EXPECT_THROW(ClassFile cf(std::move(data)), ClassFileParseError);
}

// ============================================================================
// Test: Truncated class file
// ============================================================================
TEST(ClassFileTest, TruncatedFile) {
    // Only magic number, no version info
    std::vector<std::uint8_t> data = {0xCA, 0xFE, 0xBA, 0xBE};
    EXPECT_THROW(ClassFile cf(std::move(data)), ClassFileParseError);
}

// ============================================================================
// Test: Empty input
// ============================================================================
TEST(ClassFileTest, EmptyInput) {
    std::vector<std::uint8_t> data;
    EXPECT_THROW(ClassFile cf(std::move(data)), ClassFileParseError);
}

// ============================================================================
// Test: Parse HelloWorld.class - magic and version
// ============================================================================
TEST(ClassFileTest, HelloWorldMagicAndVersion) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    EXPECT_EQ(cf.magic, 0xCAFEBABE);
    EXPECT_GE(cf.major_version, 45u);  // At least Java 1.0
    EXPECT_LE(cf.major_version, 70u);  // Up to Java SE 26
}

// ============================================================================
// Test: Parse HelloWorld.class - constant pool
// ============================================================================
TEST(ClassFileTest, HelloWorldConstantPool) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // Constant pool should have entries (index 0 is unused)
    EXPECT_GT(cf.constant_pool.size(), 1u);
    // Index 0 should be nullptr
    EXPECT_EQ(cf.constant_pool[0], nullptr);

    // At least some entries should be non-null
    bool has_utf8 = false;
    bool has_class = false;
    bool has_methodref = false;
    for (std::size_t i = 1; i < cf.constant_pool.size(); ++i) {
        if (!cf.constant_pool[i]) continue;
        switch (cf.constant_pool[i]->tag) {
        case ConstantPoolTag::CONSTANT_Utf8: has_utf8 = true; break;
        case ConstantPoolTag::CONSTANT_Class: has_class = true; break;
        case ConstantPoolTag::CONSTANT_Methodref: has_methodref = true; break;
        default: break;
        }
    }
    EXPECT_TRUE(has_utf8) << "Expected CONSTANT_Utf8 entries";
    EXPECT_TRUE(has_class) << "Expected CONSTANT_Class entries";
    EXPECT_TRUE(has_methodref) << "Expected CONSTANT_Methodref entries";
}

// ============================================================================
// Test: Parse HelloWorld.class - this_class resolves to "HelloWorld"
// ============================================================================
TEST(ClassFileTest, HelloWorldThisClass) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // this_class should point to a CONSTANT_Class_info
    EXPECT_GT(cf.this_class, 0u);
    EXPECT_LT(cf.this_class, cf.constant_pool.size());
    auto* this_class = dynamic_cast<const CONSTANT_Class_info*>(
        cf.constant_pool[cf.this_class].get());
    ASSERT_NE(this_class, nullptr);

    // The class name should be "HelloWorld"
    const auto& class_name = cf.get_utf8(this_class->name_index);
    EXPECT_EQ(class_name, "HelloWorld");
}

// ============================================================================
// Test: Parse HelloWorld.class - super_class resolves to "java/lang/Object"
// ============================================================================
TEST(ClassFileTest, HelloWorldSuperClass) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    EXPECT_GT(cf.super_class, 0u);
    auto* super_class = dynamic_cast<const CONSTANT_Class_info*>(
        cf.constant_pool[cf.super_class].get());
    ASSERT_NE(super_class, nullptr);

    const auto& super_name = cf.get_utf8(super_class->name_index);
    EXPECT_EQ(super_name, "java/lang/Object");
}

// ============================================================================
// Test: Parse HelloWorld.class - access flags
// ============================================================================
TEST(ClassFileTest, HelloWorldAccessFlags) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // HelloWorld is public and has ACC_SUPER
    EXPECT_TRUE(cf.access_flags & ClassAccess::ACC_PUBLIC);
    EXPECT_TRUE(cf.access_flags & ClassAccess::ACC_SUPER);
    EXPECT_FALSE(cf.access_flags & ClassAccess::ACC_INTERFACE);
    EXPECT_FALSE(cf.access_flags & ClassAccess::ACC_ABSTRACT);
}

// ============================================================================
// Test: Parse HelloWorld.class - methods
// ============================================================================
TEST(ClassFileTest, HelloWorldMethods) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // HelloWorld should have at least 2 methods: <init> and main
    EXPECT_GE(cf.methods.size(), 2u);

    bool has_init = false;
    bool has_main = false;
    for (const auto& method : cf.methods) {
        const auto& name = cf.get_utf8(method.name_index);
        const auto& desc = cf.get_utf8(method.descriptor_index);
        if (name == "<init>" && desc == "()V") {
            has_init = true;
        }
        if (name == "main" && desc == "([Ljava/lang/String;)V") {
            has_main = true;
            // main should be public static
            EXPECT_TRUE(method.access_flags & MethodAccess::ACC_PUBLIC);
            EXPECT_TRUE(method.access_flags & MethodAccess::ACC_STATIC);
        }
    }
    EXPECT_TRUE(has_init) << "Expected <init> method";
    EXPECT_TRUE(has_main) << "Expected main method";
}

// ============================================================================
// Test: Parse HelloWorld.class - Code attribute exists on methods
// ============================================================================
TEST(ClassFileTest, HelloWorldCodeAttribute) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    for (const auto& method : cf.methods) {
        const auto& name = cf.get_utf8(method.name_index);
        // All methods in HelloWorld should have Code attribute
        bool has_code = false;
        for (const auto& attr : method.attributes) {
            if (dynamic_cast<const Code_attribute*>(attr.get())) {
                has_code = true;
                auto* code = dynamic_cast<const Code_attribute*>(attr.get());
                EXPECT_GT(code->code.size(), 0u)
                    << "Method " << name << " has empty code";
                EXPECT_GT(code->max_stack, 0u)
                    << "Method " << name << " max_stack is 0";
            }
        }
        EXPECT_TRUE(has_code) << "Method " << name << " missing Code attribute";
    }
}

// ============================================================================
// Test: Parse HelloWorld.class - SourceFile attribute
// ============================================================================
TEST(ClassFileTest, HelloWorldSourceFile) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    bool found_source_file = false;
    for (const auto& attr : cf.attributes) {
        auto* sf = dynamic_cast<const SourceFile_attribute*>(attr.get());
        if (sf) {
            found_source_file = true;
            const auto& source = cf.get_utf8(sf->sourcefile_index);
            EXPECT_EQ(source, "HelloWorld.java");
        }
    }
    EXPECT_TRUE(found_source_file) << "Expected SourceFile attribute";
}

// ============================================================================
// Test: Parse HelloWorld.class - Methodref for System.out.println
// ============================================================================
TEST(ClassFileTest, HelloWorldHasStringConstant) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // Should contain the string "Hello, World! The sum of " in the constant pool via CONSTANT_String
    bool found_hello = false;
    for (std::size_t i = 1; i < cf.constant_pool.size(); ++i) {
        if (!cf.constant_pool[i]) continue;
        if (cf.constant_pool[i]->tag == ConstantPoolTag::CONSTANT_String) {
            auto* str = dynamic_cast<const CONSTANT_String_info*>(
                cf.constant_pool[i].get());
            const auto& value = cf.get_utf8(str->string_index);
            if (value.find("Hello, World!") != std::string::npos) {
                found_hello = true;
            }
        }
    }
    EXPECT_TRUE(found_hello) << "Expected 'Hello, World!' string constant";
}

// ============================================================================
// Test: CONSTANT_Ref_info common ancestor - Fieldref/Methodref/InterfaceMethodref
// ============================================================================
TEST(ClassFileTest, RefInfoCommonAncestor) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    // Find any Methodref and verify it can be treated as CONSTANT_Ref_info
    for (std::size_t i = 1; i < cf.constant_pool.size(); ++i) {
        if (!cf.constant_pool[i]) continue;
        auto* ref = dynamic_cast<const CONSTANT_Ref_info*>(cf.constant_pool[i].get());
        if (ref) {
            // Common ancestor fields should be accessible
            EXPECT_GT(ref->class_index, 0u);
            EXPECT_GT(ref->name_and_type_index, 0u);
            EXPECT_LT(ref->class_index, cf.constant_pool.size());
            EXPECT_LT(ref->name_and_type_index, cf.constant_pool.size());
            return;  // found at least one, test passes
        }
    }
    FAIL() << "Expected at least one CONSTANT_Ref_info entry";
}

// ============================================================================
// Test: Numeric constant pool entries (Integer/Float share CONSTANT_Numeric4_info)
// ============================================================================
TEST(ClassFileTest, Numeric4CommonAncestor) {
    // Construct a minimal class file with an Integer constant
    // This is a hand-crafted minimal valid class file
    auto int_entry = std::make_unique<CONSTANT_Integer_info>();
    int_entry->bytes = 42;
    auto* as_numeric4 = dynamic_cast<CONSTANT_Numeric4_info*>(int_entry.get());
    ASSERT_NE(as_numeric4, nullptr);
    EXPECT_EQ(as_numeric4->bytes, 42u);

    auto float_entry = std::make_unique<CONSTANT_Float_info>();
    float_entry->bytes = 0x42280000; // 42.0f in IEEE 754
    auto* as_numeric4_f = dynamic_cast<CONSTANT_Numeric4_info*>(float_entry.get());
    ASSERT_NE(as_numeric4_f, nullptr);
    EXPECT_EQ(as_numeric4_f->bytes, 0x42280000u);
}

// ============================================================================
// Test: get_utf8 with invalid index throws
// ============================================================================
TEST(ClassFileTest, GetUtf8InvalidIndex) {
    auto path = get_test_class_path() / "HelloWorld.class";
    if (!std::filesystem::exists(path)) {
        GTEST_SKIP() << "HelloWorld.class not found at " << path;
    }

    auto data = load_class_file(path);
    ClassFile cf(std::move(data));

    EXPECT_THROW((void)cf.get_utf8(0), ClassFileParseError);
    EXPECT_THROW((void)cf.get_utf8(static_cast<std::uint16_t>(cf.constant_pool.size())),
                 ClassFileParseError);
}

// ============================================================================
// Test: Minimal hand-crafted class file
// ============================================================================
TEST(ClassFileTest, MinimalClassFile) {
    // Build a minimal valid class file:
    // magic (4) + minor (2) + major (2) + cp_count (2) +
    // cp entries + access_flags (2) + this_class (2) + super_class (2) +
    // interfaces_count (2) + fields_count (2) + methods_count (2) +
    // attributes_count (2)
    std::vector<std::uint8_t> data;
    auto put_u1 = [&](std::uint8_t v) { data.push_back(v); };
    auto put_u2 = [&](std::uint16_t v) {
        data.push_back(static_cast<std::uint8_t>(v >> 8));
        data.push_back(static_cast<std::uint8_t>(v & 0xFF));
    };
    auto put_u4 = [&](std::uint32_t v) {
        data.push_back(static_cast<std::uint8_t>((v >> 24) & 0xFF));
        data.push_back(static_cast<std::uint8_t>((v >> 16) & 0xFF));
        data.push_back(static_cast<std::uint8_t>((v >> 8)  & 0xFF));
        data.push_back(static_cast<std::uint8_t>(v & 0xFF));
    };

    put_u4(0xCAFEBABE);       // magic
    put_u2(0);                 // minor_version
    put_u2(52);                // major_version (Java 8)

    // Constant pool: count = 5 (entries 1-4)
    // #1: CONSTANT_Utf8 "TestClass"
    // #2: CONSTANT_Class -> #1
    // #3: CONSTANT_Utf8 "java/lang/Object"
    // #4: CONSTANT_Class -> #3
    put_u2(5);  // constant_pool_count

    // #1: CONSTANT_Utf8 "TestClass"
    put_u1(1);  // tag = CONSTANT_Utf8
    put_u2(9);  // length
    for (char c : std::string("TestClass")) put_u1(static_cast<std::uint8_t>(c));

    // #2: CONSTANT_Class -> #1
    put_u1(7);  // tag = CONSTANT_Class
    put_u2(1);  // name_index

    // #3: CONSTANT_Utf8 "java/lang/Object"
    put_u1(1);  // tag = CONSTANT_Utf8
    put_u2(16); // length
    for (char c : std::string("java/lang/Object")) put_u1(static_cast<std::uint8_t>(c));

    // #4: CONSTANT_Class -> #3
    put_u1(7);  // tag = CONSTANT_Class
    put_u2(3);  // name_index

    put_u2(ClassAccess::ACC_PUBLIC | ClassAccess::ACC_SUPER); // access_flags
    put_u2(2);  // this_class -> #2
    put_u2(4);  // super_class -> #4
    put_u2(0);  // interfaces_count
    put_u2(0);  // fields_count
    put_u2(0);  // methods_count
    put_u2(0);  // attributes_count

    ClassFile cf(std::move(data));

    EXPECT_EQ(cf.magic, 0xCAFEBABE);
    EXPECT_EQ(cf.major_version, 52u);
    EXPECT_EQ(cf.minor_version, 0u);
    EXPECT_EQ(cf.constant_pool.size(), 5u);
    EXPECT_EQ(cf.this_class, 2u);
    EXPECT_EQ(cf.super_class, 4u);
    EXPECT_EQ(cf.interfaces.size(), 0u);
    EXPECT_EQ(cf.fields.size(), 0u);
    EXPECT_EQ(cf.methods.size(), 0u);
    EXPECT_EQ(cf.attributes.size(), 0u);

    auto* this_class = dynamic_cast<const CONSTANT_Class_info*>(
        cf.constant_pool[cf.this_class].get());
    ASSERT_NE(this_class, nullptr);
    EXPECT_EQ(cf.get_utf8(this_class->name_index), "TestClass");
}

// ============================================================================
// Test: Long/Double take two constant pool slots
// ============================================================================
TEST(ClassFileTest, LongDoubleOccupyTwoSlots) {
    std::vector<std::uint8_t> data;
    auto put_u1 = [&](std::uint8_t v) { data.push_back(v); };
    auto put_u2 = [&](std::uint16_t v) {
        data.push_back(static_cast<std::uint8_t>(v >> 8));
        data.push_back(static_cast<std::uint8_t>(v & 0xFF));
    };
    auto put_u4 = [&](std::uint32_t v) {
        data.push_back(static_cast<std::uint8_t>((v >> 24) & 0xFF));
        data.push_back(static_cast<std::uint8_t>((v >> 16) & 0xFF));
        data.push_back(static_cast<std::uint8_t>((v >> 8)  & 0xFF));
        data.push_back(static_cast<std::uint8_t>(v & 0xFF));
    };

    put_u4(0xCAFEBABE);
    put_u2(0);
    put_u2(52);

    // cp_count = 8 (entries 1..7)
    // #1: Utf8 "TestClass"
    // #2: Class -> #1
    // #3: Utf8 "java/lang/Object"
    // #4: Class -> #3
    // #5: Long (occupies #5 and #6)
    // #7: Utf8 "after_long"
    put_u2(8);

    // #1
    put_u1(1); put_u2(9);
    for (char c : std::string("TestClass")) put_u1(static_cast<std::uint8_t>(c));
    // #2
    put_u1(7); put_u2(1);
    // #3
    put_u1(1); put_u2(16);
    for (char c : std::string("java/lang/Object")) put_u1(static_cast<std::uint8_t>(c));
    // #4
    put_u1(7); put_u2(3);
    // #5: CONSTANT_Long
    put_u1(5); put_u4(0); put_u4(12345);
    // #6 is skipped (occupied by Long)
    // #7: Utf8 "after_long"
    put_u1(1); put_u2(10);
    for (char c : std::string("after_long")) put_u1(static_cast<std::uint8_t>(c));

    put_u2(ClassAccess::ACC_PUBLIC | ClassAccess::ACC_SUPER);
    put_u2(2); put_u2(4);
    put_u2(0); put_u2(0); put_u2(0); put_u2(0);

    ClassFile cf(std::move(data));

    EXPECT_EQ(cf.constant_pool.size(), 8u);
    // #5 should be Long
    ASSERT_NE(cf.constant_pool[5], nullptr);
    EXPECT_EQ(cf.constant_pool[5]->tag, ConstantPoolTag::CONSTANT_Long);
    auto* long_entry = dynamic_cast<const CONSTANT_Long_info*>(cf.constant_pool[5].get());
    ASSERT_NE(long_entry, nullptr);
    EXPECT_EQ(long_entry->low_bytes, 12345u);
    // #6 should be nullptr (occupied slot)
    EXPECT_EQ(cf.constant_pool[6], nullptr);
    // #7 should be Utf8
    ASSERT_NE(cf.constant_pool[7], nullptr);
    EXPECT_EQ(cf.constant_pool[7]->tag, ConstantPoolTag::CONSTANT_Utf8);
    EXPECT_EQ(cf.get_utf8(7), "after_long");

    // Test CONSTANT_Numeric8_info common ancestor
    auto* as_numeric8 = dynamic_cast<const CONSTANT_Numeric8_info*>(cf.constant_pool[5].get());
    ASSERT_NE(as_numeric8, nullptr);
    EXPECT_EQ(as_numeric8->high_bytes, 0u);
    EXPECT_EQ(as_numeric8->low_bytes, 12345u);
}

} // anonymous namespace
} // namespace aijvm::classfile
