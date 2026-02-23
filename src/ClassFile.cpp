#include "ClassFile.h"

ClassReader::ClassReader(const std::vector<u1>& bytecode) : data(bytecode), pos(0) {}

static std::vector<u1> readFileBytes(const std::filesystem::path& path)
{
    if (!std::filesystem::is_regular_file(path))
        throw std::runtime_error("Not a regular file: " + path.string());

    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Failed to open file: " + path.string());

    return { std::istreambuf_iterator<char>(file),
             std::istreambuf_iterator<char>() };
}

ClassReader::ClassReader(const std::filesystem::path& path)
    : ClassReader(readFileBytes(path)) {}

u1 ClassReader::read_u1() {
    if (pos >= data.size()) throw std::out_of_range("Unexpected EOF");
    return data[pos++];
}

u2 ClassReader::read_u2() {
    // 强制按大端序组合 16 位整数 
    u2 val = (read_u1() << 8) | read_u1(); 
    return val;
}

u4 ClassReader::read_u4() {
    // 强制按大端序组合 32 位整数 
    u4 val = (read_u1() << 24) | (read_u1() << 16) | (read_u1() << 8) | read_u1();
    return val;
}

std::vector<u1> ClassReader::read_bytes(size_t length) {
    if (pos + length > data.size()) throw std::out_of_range("Unexpected EOF");
    std::vector<u1> bytes(data.begin() + pos, data.begin() + pos + length);
    pos += length;
    return bytes;
}

void ClassReader::parse_constant_pool(ClassFile& cf) {
    cf.constant_pool.resize(cf.constant_pool_count); 
    // 常量池有效索引是从 1 到 constant_pool_count - 1 [cite: 1297]
    for (int i = 1; i < cf.constant_pool_count; ++i) {
        u1 tag_val = read_u1();
        ConstantTag tag = static_cast<ConstantTag>(tag_val);
        
        // 为了保持框架简洁，这里省略了为每个 tag 构建具体的子结构对象。
        // 主要逻辑是按规范跨越不同长度的字节流：
        switch (tag) {
            case ConstantTag::CONSTANT_Class:
            case ConstantTag::CONSTANT_String:
            case ConstantTag::CONSTANT_MethodType:
            case ConstantTag::CONSTANT_Module:
            case ConstantTag::CONSTANT_Package:
                read_u2();
                break;
            case ConstantTag::CONSTANT_Fieldref:
            case ConstantTag::CONSTANT_Methodref:
            case ConstantTag::CONSTANT_InterfaceMethodref:
            case ConstantTag::CONSTANT_NameAndType:
            case ConstantTag::CONSTANT_Dynamic:
            case ConstantTag::CONSTANT_InvokeDynamic:
                read_u2();
                read_u2();
                break;
            case ConstantTag::CONSTANT_Integer:
            case ConstantTag::CONSTANT_Float:
                read_u4();
                break;
            case ConstantTag::CONSTANT_Long:
            case ConstantTag::CONSTANT_Double:
                read_u4();
                read_u4();
                i++; // 8字节的 Long 和 Double 会占用常量池的两个条目位置 
                break;
            case ConstantTag::CONSTANT_Utf8: {
                u2 length = read_u2();
                read_bytes(length); // 修改版的 UTF-8 字符串
                break;
            }
            case ConstantTag::CONSTANT_MethodHandle:
                read_u1();
                read_u2();
                break;
            default:
                throw std::runtime_error("Unknown constant pool tag");
        }
    }
}

void ClassReader::parse_interfaces(ClassFile& cf) {
    cf.interfaces.resize(cf.interfaces_count);
    for (int i = 0; i < cf.interfaces_count; ++i) {
        cf.interfaces[i] = read_u2();
    }
}

void ClassReader::parse_attributes(std::vector<attribute_info>& attributes, u2 count) {
    attributes.resize(count);
    for (int i = 0; i < count; ++i) {
        attributes[i].attribute_name_index = read_u2();
        attributes[i].attribute_length = read_u4();
        attributes[i].info = read_bytes(attributes[i].attribute_length);
    }
}

void ClassReader::parse_fields(ClassFile& cf) {
    cf.fields.resize(cf.fields_count);
    for (int i = 0; i < cf.fields_count; ++i) {
        cf.fields[i].access_flags = read_u2();
        cf.fields[i].name_index = read_u2();
        cf.fields[i].descriptor_index = read_u2();
        cf.fields[i].attributes_count = read_u2();
        parse_attributes(cf.fields[i].attributes, cf.fields[i].attributes_count);
    }
}

void ClassReader::parse_methods(ClassFile& cf) {
    cf.methods.resize(cf.methods_count);
    for (int i = 0; i < cf.methods_count; ++i) {
        cf.methods[i].access_flags = read_u2();
        cf.methods[i].name_index = read_u2();
        cf.methods[i].descriptor_index = read_u2();
        cf.methods[i].attributes_count = read_u2();
        parse_attributes(cf.methods[i].attributes, cf.methods[i].attributes_count);
    }
}

std::shared_ptr<ClassFile> ClassReader::parse() {
    auto cf = std::make_shared<ClassFile>();
    
    cf->magic = read_u4();
    if (cf->magic != 0xCAFEBABE) { // 魔数标识类文件格式 [cite: 1288]
        throw std::runtime_error("Invalid magic number");
    }
    
    cf->minor_version = read_u2();
    cf->major_version = read_u2();
    
    cf->constant_pool_count = read_u2();
    parse_constant_pool(*cf);
    
    cf->access_flags = read_u2();
    cf->this_class = read_u2();
    cf->super_class = read_u2();
    
    cf->interfaces_count = read_u2();
    parse_interfaces(*cf);
    
    cf->fields_count = read_u2();
    parse_fields(*cf);
    
    cf->methods_count = read_u2();
    parse_methods(*cf);
    
    cf->attributes_count = read_u2();
    parse_attributes(cf->attributes, cf->attributes_count);
    
    return cf;
}