#pragma once
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

// 基础无符号类型定义，严格对应 JVM 规范
using u1 = uint8_t;
using u2 = uint16_t;
using u4 = uint32_t;

// 常量池的 Tag 定义 [cite: 1382]
enum class ConstantTag : u1 {
    CONSTANT_Utf8 = 1,
    CONSTANT_Integer = 3,
    CONSTANT_Float = 4,
    CONSTANT_Long = 5,
    CONSTANT_Double = 6,
    CONSTANT_Class = 7,
    CONSTANT_String = 8,
    CONSTANT_Fieldref = 9,
    CONSTANT_Methodref = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_NameAndType = 12,
    CONSTANT_MethodHandle = 15,
    CONSTANT_MethodType = 16,
    CONSTANT_Dynamic = 17,
    CONSTANT_InvokeDynamic = 18,
    CONSTANT_Module = 19,
    CONSTANT_Package = 20
};

// 常量池项基类
struct cp_info {
    ConstantTag tag;
    virtual ~cp_info() = default;
};

// 属性表结构 [cite: 1432]
struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    std::vector<u1> info;
};

// 字段表结构 [cite: 1426]
struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};

// 方法表结构 [cite: 1428]
struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};

// 顶层 ClassFile 结构体 
struct ClassFile {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    std::vector<std::shared_ptr<cp_info>> constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    std::vector<u2> interfaces;
    u2 fields_count;
    std::vector<field_info> fields;
    u2 methods_count;
    std::vector<method_info> methods;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};

// Class 解析器接口
class ClassReader {
private:
    std::vector<u1> data;
    size_t pos = 0;

    // 底层流读取工具，处理大端序
    u1 read_u1();
    u2 read_u2();
    u4 read_u4();
    std::vector<u1> read_bytes(size_t length);

    // 各大区块解析逻辑
    void parse_constant_pool(ClassFile& cf);
    void parse_interfaces(ClassFile& cf);
    void parse_fields(ClassFile& cf);
    void parse_methods(ClassFile& cf);
    void parse_attributes(std::vector<attribute_info>& attributes, u2 count);

public:
    explicit ClassReader(const std::vector<u1>& bytecode);
    explicit ClassReader(const std::filesystem::path& path);
    std::shared_ptr<ClassFile> parse();
};