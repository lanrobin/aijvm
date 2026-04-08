#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace aijvm::classfile {

// ============================================================================
// §4.4 Constant Pool Tags (Table 4.4-A)
// ============================================================================
enum class ConstantPoolTag : std::uint8_t {
    CONSTANT_Utf8               = 1,
    CONSTANT_Integer            = 3,
    CONSTANT_Float              = 4,
    CONSTANT_Long               = 5,
    CONSTANT_Double             = 6,
    CONSTANT_Class              = 7,
    CONSTANT_String             = 8,
    CONSTANT_Fieldref           = 9,
    CONSTANT_Methodref          = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_NameAndType        = 12,
    CONSTANT_MethodHandle       = 15,
    CONSTANT_MethodType         = 16,
    CONSTANT_Dynamic            = 17,
    CONSTANT_InvokeDynamic      = 18,
    CONSTANT_Module             = 19,
    CONSTANT_Package            = 20,
};

// ============================================================================
// §4.1 Class access and property modifiers (Table 4.1-B)
// ============================================================================
namespace ClassAccess {
    constexpr std::uint16_t ACC_PUBLIC     = 0x0001;
    constexpr std::uint16_t ACC_FINAL      = 0x0010;
    constexpr std::uint16_t ACC_SUPER      = 0x0020;
    constexpr std::uint16_t ACC_INTERFACE  = 0x0200;
    constexpr std::uint16_t ACC_ABSTRACT   = 0x0400;
    constexpr std::uint16_t ACC_SYNTHETIC  = 0x1000;
    constexpr std::uint16_t ACC_ANNOTATION = 0x2000;
    constexpr std::uint16_t ACC_ENUM       = 0x4000;
    constexpr std::uint16_t ACC_MODULE     = 0x8000;
}

// ============================================================================
// §4.5 Field access and property flags (Table 4.5-A)
// ============================================================================
namespace FieldAccess {
    constexpr std::uint16_t ACC_PUBLIC    = 0x0001;
    constexpr std::uint16_t ACC_PRIVATE   = 0x0002;
    constexpr std::uint16_t ACC_PROTECTED = 0x0004;
    constexpr std::uint16_t ACC_STATIC    = 0x0008;
    constexpr std::uint16_t ACC_FINAL     = 0x0010;
    constexpr std::uint16_t ACC_VOLATILE  = 0x0040;
    constexpr std::uint16_t ACC_TRANSIENT = 0x0080;
    constexpr std::uint16_t ACC_SYNTHETIC = 0x1000;
    constexpr std::uint16_t ACC_ENUM      = 0x4000;
}

// ============================================================================
// §4.6 Method access and property flags (Table 4.6-A)
// ============================================================================
namespace MethodAccess {
    constexpr std::uint16_t ACC_PUBLIC       = 0x0001;
    constexpr std::uint16_t ACC_PRIVATE      = 0x0002;
    constexpr std::uint16_t ACC_PROTECTED    = 0x0004;
    constexpr std::uint16_t ACC_STATIC       = 0x0008;
    constexpr std::uint16_t ACC_FINAL        = 0x0010;
    constexpr std::uint16_t ACC_SYNCHRONIZED = 0x0020;
    constexpr std::uint16_t ACC_BRIDGE       = 0x0040;
    constexpr std::uint16_t ACC_VARARGS      = 0x0080;
    constexpr std::uint16_t ACC_NATIVE       = 0x0100;
    constexpr std::uint16_t ACC_ABSTRACT     = 0x0400;
    constexpr std::uint16_t ACC_STRICT       = 0x0800;
    constexpr std::uint16_t ACC_SYNTHETIC    = 0x1000;
}

// ============================================================================
// §4.4 Constant Pool Structures
// ============================================================================

// Base class for all constant pool entries
struct cp_info {
    ConstantPoolTag tag;
    virtual ~cp_info() = default;

protected:
    explicit cp_info(ConstantPoolTag t) : tag(t) {}
};

// §4.4.7 CONSTANT_Utf8_info
struct CONSTANT_Utf8_info : cp_info {
    std::string bytes;  // decoded modified UTF-8
    CONSTANT_Utf8_info() : cp_info(ConstantPoolTag::CONSTANT_Utf8) {}
};

// §4.4.1 CONSTANT_Class_info
struct CONSTANT_Class_info : cp_info {
    std::uint16_t name_index{};
    CONSTANT_Class_info() : cp_info(ConstantPoolTag::CONSTANT_Class) {}
};

// §4.4.3 CONSTANT_String_info
struct CONSTANT_String_info : cp_info {
    std::uint16_t string_index{};
    CONSTANT_String_info() : cp_info(ConstantPoolTag::CONSTANT_String) {}
};

// §4.4.6 CONSTANT_NameAndType_info
struct CONSTANT_NameAndType_info : cp_info {
    std::uint16_t name_index{};
    std::uint16_t descriptor_index{};
    CONSTANT_NameAndType_info() : cp_info(ConstantPoolTag::CONSTANT_NameAndType) {}
};

// §4.4.9 CONSTANT_MethodType_info
struct CONSTANT_MethodType_info : cp_info {
    std::uint16_t descriptor_index{};
    CONSTANT_MethodType_info() : cp_info(ConstantPoolTag::CONSTANT_MethodType) {}
};

// §4.4.8 CONSTANT_MethodHandle_info
struct CONSTANT_MethodHandle_info : cp_info {
    std::uint8_t reference_kind{};
    std::uint16_t reference_index{};
    CONSTANT_MethodHandle_info() : cp_info(ConstantPoolTag::CONSTANT_MethodHandle) {}
};

// §4.4.11 CONSTANT_Module_info
struct CONSTANT_Module_info : cp_info {
    std::uint16_t name_index{};
    CONSTANT_Module_info() : cp_info(ConstantPoolTag::CONSTANT_Module) {}
};

// §4.4.12 CONSTANT_Package_info
struct CONSTANT_Package_info : cp_info {
    std::uint16_t name_index{};
    CONSTANT_Package_info() : cp_info(ConstantPoolTag::CONSTANT_Package) {}
};

// §4.4.2 Common base for CONSTANT_Fieldref_info, CONSTANT_Methodref_info,
//        CONSTANT_InterfaceMethodref_info (shared data structure)
struct CONSTANT_Ref_info : cp_info {
    std::uint16_t class_index{};
    std::uint16_t name_and_type_index{};

protected:
    explicit CONSTANT_Ref_info(ConstantPoolTag t) : cp_info(t) {}
};

// §4.4.2 CONSTANT_Fieldref_info
struct CONSTANT_Fieldref_info : CONSTANT_Ref_info {
    CONSTANT_Fieldref_info() : CONSTANT_Ref_info(ConstantPoolTag::CONSTANT_Fieldref) {}
};

// §4.4.2 CONSTANT_Methodref_info
struct CONSTANT_Methodref_info : CONSTANT_Ref_info {
    CONSTANT_Methodref_info() : CONSTANT_Ref_info(ConstantPoolTag::CONSTANT_Methodref) {}
};

// §4.4.2 CONSTANT_InterfaceMethodref_info
struct CONSTANT_InterfaceMethodref_info : CONSTANT_Ref_info {
    CONSTANT_InterfaceMethodref_info()
        : CONSTANT_Ref_info(ConstantPoolTag::CONSTANT_InterfaceMethodref) {}
};

// §4.4.4 Common base for CONSTANT_Integer_info and CONSTANT_Float_info
//        (shared 4-byte numeric data structure)
struct CONSTANT_Numeric4_info : cp_info {
    std::uint32_t bytes{};

protected:
    explicit CONSTANT_Numeric4_info(ConstantPoolTag t) : cp_info(t) {}
};

// §4.4.4 CONSTANT_Integer_info
struct CONSTANT_Integer_info : CONSTANT_Numeric4_info {
    CONSTANT_Integer_info() : CONSTANT_Numeric4_info(ConstantPoolTag::CONSTANT_Integer) {}
};

// §4.4.4 CONSTANT_Float_info
struct CONSTANT_Float_info : CONSTANT_Numeric4_info {
    CONSTANT_Float_info() : CONSTANT_Numeric4_info(ConstantPoolTag::CONSTANT_Float) {}
};

// §4.4.5 Common base for CONSTANT_Long_info and CONSTANT_Double_info
//        (shared 8-byte numeric data structure, occupies two constant pool entries)
struct CONSTANT_Numeric8_info : cp_info {
    std::uint32_t high_bytes{};
    std::uint32_t low_bytes{};

protected:
    explicit CONSTANT_Numeric8_info(ConstantPoolTag t) : cp_info(t) {}
};

// §4.4.5 CONSTANT_Long_info
struct CONSTANT_Long_info : CONSTANT_Numeric8_info {
    CONSTANT_Long_info() : CONSTANT_Numeric8_info(ConstantPoolTag::CONSTANT_Long) {}
};

// §4.4.5 CONSTANT_Double_info
struct CONSTANT_Double_info : CONSTANT_Numeric8_info {
    CONSTANT_Double_info() : CONSTANT_Numeric8_info(ConstantPoolTag::CONSTANT_Double) {}
};

// §4.4.10 Common base for CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info
//         (shared bootstrap method + name_and_type data structure)
struct CONSTANT_DynamicBase_info : cp_info {
    std::uint16_t bootstrap_method_attr_index{};
    std::uint16_t name_and_type_index{};

protected:
    explicit CONSTANT_DynamicBase_info(ConstantPoolTag t) : cp_info(t) {}
};

// §4.4.10 CONSTANT_Dynamic_info
struct CONSTANT_Dynamic_info : CONSTANT_DynamicBase_info {
    CONSTANT_Dynamic_info() : CONSTANT_DynamicBase_info(ConstantPoolTag::CONSTANT_Dynamic) {}
};

// §4.4.10 CONSTANT_InvokeDynamic_info
struct CONSTANT_InvokeDynamic_info : CONSTANT_DynamicBase_info {
    CONSTANT_InvokeDynamic_info()
        : CONSTANT_DynamicBase_info(ConstantPoolTag::CONSTANT_InvokeDynamic) {}
};

// ============================================================================
// §4.7 Attribute Structures
// ============================================================================

// Base class for all attributes
struct attribute_info {
    std::uint16_t attribute_name_index{};
    std::uint32_t attribute_length{};
    virtual ~attribute_info() = default;
};

// Unknown/unrecognized attribute - stores raw bytes (§4.7.1)
struct Unknown_attribute : attribute_info {
    std::vector<std::uint8_t> info;
};

// §4.7.2 ConstantValue_attribute
struct ConstantValue_attribute : attribute_info {
    std::uint16_t constantvalue_index{};
};

// §4.7.3 Code_attribute
struct Code_attribute : attribute_info {
    std::uint16_t max_stack{};
    std::uint16_t max_locals{};
    std::vector<std::uint8_t> code;

    struct ExceptionTableEntry {
        std::uint16_t start_pc{};
        std::uint16_t end_pc{};
        std::uint16_t handler_pc{};
        std::uint16_t catch_type{};
    };
    std::vector<ExceptionTableEntry> exception_table;
    std::vector<std::unique_ptr<attribute_info>> attributes;
};

// §4.7.4 StackMapTable_attribute verification_type_info
struct verification_type_info {
    std::uint8_t tag{};
    std::uint16_t data{};  // cpool_index for Object (tag=7), offset for Uninitialized (tag=8)
};

// §4.7.4 StackMapTable_attribute stack_map_frame
struct stack_map_frame {
    std::uint8_t frame_type{};
    std::uint16_t offset_delta{};
    std::vector<verification_type_info> locals;
    std::vector<verification_type_info> stack;
};

// §4.7.4 StackMapTable_attribute
struct StackMapTable_attribute : attribute_info {
    std::vector<stack_map_frame> entries;
};

// §4.7.5 Exceptions_attribute
struct Exceptions_attribute : attribute_info {
    std::vector<std::uint16_t> exception_index_table;
};

// §4.7.6 InnerClasses_attribute
struct InnerClasses_attribute : attribute_info {
    struct InnerClassEntry {
        std::uint16_t inner_class_info_index{};
        std::uint16_t outer_class_info_index{};
        std::uint16_t inner_name_index{};
        std::uint16_t inner_class_access_flags{};
    };
    std::vector<InnerClassEntry> classes;
};

// §4.7.7 EnclosingMethod_attribute
struct EnclosingMethod_attribute : attribute_info {
    std::uint16_t class_index{};
    std::uint16_t method_index{};
};

// §4.7.8 Synthetic_attribute (zero-length)
struct Synthetic_attribute : attribute_info {};

// §4.7.9 Signature_attribute
struct Signature_attribute : attribute_info {
    std::uint16_t signature_index{};
};

// §4.7.10 SourceFile_attribute
struct SourceFile_attribute : attribute_info {
    std::uint16_t sourcefile_index{};
};

// §4.7.11 SourceDebugExtension_attribute
struct SourceDebugExtension_attribute : attribute_info {
    std::vector<std::uint8_t> debug_extension;
};

// §4.7.12 LineNumberTable_attribute
struct LineNumberTable_attribute : attribute_info {
    struct LineNumberEntry {
        std::uint16_t start_pc{};
        std::uint16_t line_number{};
    };
    std::vector<LineNumberEntry> line_number_table;
};

// §4.7.13 LocalVariableTable_attribute
struct LocalVariableTable_attribute : attribute_info {
    struct LocalVariableEntry {
        std::uint16_t start_pc{};
        std::uint16_t length{};
        std::uint16_t name_index{};
        std::uint16_t descriptor_index{};
        std::uint16_t index{};
    };
    std::vector<LocalVariableEntry> local_variable_table;
};

// §4.7.14 LocalVariableTypeTable_attribute
struct LocalVariableTypeTable_attribute : attribute_info {
    struct LocalVariableTypeEntry {
        std::uint16_t start_pc{};
        std::uint16_t length{};
        std::uint16_t name_index{};
        std::uint16_t signature_index{};
        std::uint16_t index{};
    };
    std::vector<LocalVariableTypeEntry> local_variable_type_table;
};

// §4.7.15 Deprecated_attribute (zero-length)
struct Deprecated_attribute : attribute_info {};

// ============================================================================
// §4.7.16 Annotation structures (shared by multiple annotation attributes)
// ============================================================================

struct element_value;  // forward declaration

struct annotation {
    std::uint16_t type_index{};
    struct ElementValuePair {
        std::uint16_t element_name_index{};
        std::unique_ptr<element_value> value;
    };
    std::vector<ElementValuePair> element_value_pairs;
};

struct element_value {
    std::uint8_t tag{};
    // For tag in {B,C,D,F,I,J,S,Z,s}: const_value_index
    std::uint16_t const_value_index{};
    // For tag 'e': enum_const_value
    struct {
        std::uint16_t type_name_index{};
        std::uint16_t const_name_index{};
    } enum_const_value;
    // For tag 'c': class_info_index
    std::uint16_t class_info_index{};
    // For tag '@': annotation_value
    annotation annotation_value;
    // For tag '[': array_value
    std::vector<std::unique_ptr<element_value>> array_value;
};

// §4.7.16 RuntimeVisibleAnnotations_attribute
struct RuntimeVisibleAnnotations_attribute : attribute_info {
    std::vector<annotation> annotations;
};

// §4.7.17 RuntimeInvisibleAnnotations_attribute
struct RuntimeInvisibleAnnotations_attribute : attribute_info {
    std::vector<annotation> annotations;
};

// §4.7.18 RuntimeVisibleParameterAnnotations_attribute
struct RuntimeVisibleParameterAnnotations_attribute : attribute_info {
    struct ParameterAnnotation {
        std::vector<annotation> annotations;
    };
    std::vector<ParameterAnnotation> parameter_annotations;
};

// §4.7.19 RuntimeInvisibleParameterAnnotations_attribute
struct RuntimeInvisibleParameterAnnotations_attribute : attribute_info {
    struct ParameterAnnotation {
        std::vector<annotation> annotations;
    };
    std::vector<ParameterAnnotation> parameter_annotations;
};

// ============================================================================
// §4.7.20 Type annotation structures
// ============================================================================

struct type_annotation {
    std::uint8_t target_type{};

    // target_info union - which fields are valid depends on target_type
    struct {
        std::uint8_t type_parameter_index{};
    } type_parameter_target;

    struct {
        std::uint16_t supertype_index{};
    } supertype_target;

    struct {
        std::uint8_t type_parameter_index{};
        std::uint8_t bound_index{};
    } type_parameter_bound_target;

    // empty_target has no fields

    struct {
        std::uint8_t formal_parameter_index{};
    } formal_parameter_target;

    struct {
        std::uint16_t throws_type_index{};
    } throws_target;

    struct LocalvarEntry {
        std::uint16_t start_pc{};
        std::uint16_t length{};
        std::uint16_t index{};
    };
    std::vector<LocalvarEntry> localvar_target;

    struct {
        std::uint16_t exception_table_index{};
    } catch_target;

    struct {
        std::uint16_t offset{};
    } offset_target;

    struct {
        std::uint16_t offset{};
        std::uint8_t type_argument_index{};
    } type_argument_target;

    // type_path
    struct TypePathEntry {
        std::uint8_t type_path_kind{};
        std::uint8_t type_argument_index{};
    };
    std::vector<TypePathEntry> target_path;

    // annotation part
    std::uint16_t type_index{};
    struct ElementValuePair {
        std::uint16_t element_name_index{};
        std::unique_ptr<element_value> value;
    };
    std::vector<ElementValuePair> element_value_pairs;
};

// §4.7.20 RuntimeVisibleTypeAnnotations_attribute
struct RuntimeVisibleTypeAnnotations_attribute : attribute_info {
    std::vector<type_annotation> annotations;
};

// §4.7.21 RuntimeInvisibleTypeAnnotations_attribute
struct RuntimeInvisibleTypeAnnotations_attribute : attribute_info {
    std::vector<type_annotation> annotations;
};

// §4.7.22 AnnotationDefault_attribute
struct AnnotationDefault_attribute : attribute_info {
    std::unique_ptr<element_value> default_value;
};

// §4.7.23 BootstrapMethods_attribute
struct BootstrapMethods_attribute : attribute_info {
    struct BootstrapMethod {
        std::uint16_t bootstrap_method_ref{};
        std::vector<std::uint16_t> bootstrap_arguments;
    };
    std::vector<BootstrapMethod> bootstrap_methods;
};

// §4.7.24 MethodParameters_attribute
struct MethodParameters_attribute : attribute_info {
    struct Parameter {
        std::uint16_t name_index{};
        std::uint16_t access_flags{};
    };
    std::vector<Parameter> parameters;
};

// §4.7.25 Module_attribute
struct Module_attribute : attribute_info {
    std::uint16_t module_name_index{};
    std::uint16_t module_flags{};
    std::uint16_t module_version_index{};

    struct Requires {
        std::uint16_t requires_index{};
        std::uint16_t requires_flags{};
        std::uint16_t requires_version_index{};
    };
    std::vector<Requires> requires_entries;

    struct Exports {
        std::uint16_t exports_index{};
        std::uint16_t exports_flags{};
        std::vector<std::uint16_t> exports_to_index;
    };
    std::vector<Exports> exports_entries;

    struct Opens {
        std::uint16_t opens_index{};
        std::uint16_t opens_flags{};
        std::vector<std::uint16_t> opens_to_index;
    };
    std::vector<Opens> opens_entries;

    std::vector<std::uint16_t> uses_index;

    struct Provides {
        std::uint16_t provides_index{};
        std::vector<std::uint16_t> provides_with_index;
    };
    std::vector<Provides> provides_entries;
};

// §4.7.26 ModulePackages_attribute
struct ModulePackages_attribute : attribute_info {
    std::vector<std::uint16_t> package_index;
};

// §4.7.27 ModuleMainClass_attribute
struct ModuleMainClass_attribute : attribute_info {
    std::uint16_t main_class_index{};
};

// §4.7.28 NestHost_attribute
struct NestHost_attribute : attribute_info {
    std::uint16_t host_class_index{};
};

// §4.7.29 NestMembers_attribute
struct NestMembers_attribute : attribute_info {
    std::vector<std::uint16_t> classes;
};

// §4.7.30 Record_attribute
struct Record_attribute : attribute_info {
    struct RecordComponentInfo {
        std::uint16_t name_index{};
        std::uint16_t descriptor_index{};
        std::vector<std::unique_ptr<attribute_info>> attributes;
    };
    std::vector<RecordComponentInfo> components;
};

// §4.7.31 PermittedSubclasses_attribute
struct PermittedSubclasses_attribute : attribute_info {
    std::vector<std::uint16_t> classes;
};

// ============================================================================
// §4.5 field_info and §4.6 method_info
// ============================================================================

struct field_info {
    std::uint16_t access_flags{};
    std::uint16_t name_index{};
    std::uint16_t descriptor_index{};
    std::vector<std::unique_ptr<attribute_info>> attributes;
};

struct method_info {
    std::uint16_t access_flags{};
    std::uint16_t name_index{};
    std::uint16_t descriptor_index{};
    std::vector<std::unique_ptr<attribute_info>> attributes;
};

// ============================================================================
// §4.1 The ClassFile Structure
// ============================================================================

class ClassFileParseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class ClassFile {
public:
    // §4.1: Parse a class file from raw bytes
    explicit ClassFile(std::vector<std::uint8_t> data);

    std::uint32_t magic{};
    std::uint16_t minor_version{};
    std::uint16_t major_version{};
    // constant_pool[0] is nullptr (1-indexed per spec)
    std::vector<std::unique_ptr<cp_info>> constant_pool;
    std::uint16_t access_flags{};
    std::uint16_t this_class{};
    std::uint16_t super_class{};
    std::vector<std::uint16_t> interfaces;
    std::vector<field_info> fields;
    std::vector<method_info> methods;
    std::vector<std::unique_ptr<attribute_info>> attributes;

    // Helper: get UTF-8 string from constant pool by index
    [[nodiscard]] const std::string& get_utf8(std::uint16_t index) const;
};

} // namespace aijvm::classfile
