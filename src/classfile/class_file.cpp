#include "classfile/class_file.h"

#include <bit>
#include <cstring>
#include <format>
#include <span>

namespace aijvm::classfile {

// ============================================================================
// ByteReader: safe sequential reader over a byte span (big-endian)
// ============================================================================
class ByteReader {
public:
    explicit ByteReader(std::span<const std::uint8_t> data)
        : data_(data), pos_(0) {}

    [[nodiscard]] std::size_t position() const { return pos_; }
    [[nodiscard]] std::size_t remaining() const { return data_.size() - pos_; }

    std::uint8_t read_u1() {
        check(1);
        return data_[pos_++];
    }

    std::uint16_t read_u2() {
        check(2);
        auto val = static_cast<std::uint16_t>(
            (static_cast<std::uint16_t>(data_[pos_]) << 8) |
             static_cast<std::uint16_t>(data_[pos_ + 1]));
        pos_ += 2;
        return val;
    }

    std::uint32_t read_u4() {
        check(4);
        auto val = (static_cast<std::uint32_t>(data_[pos_])     << 24) |
                   (static_cast<std::uint32_t>(data_[pos_ + 1]) << 16) |
                   (static_cast<std::uint32_t>(data_[pos_ + 2]) << 8)  |
                    static_cast<std::uint32_t>(data_[pos_ + 3]);
        pos_ += 4;
        return val;
    }

    std::vector<std::uint8_t> read_bytes(std::size_t count) {
        check(count);
        std::vector<std::uint8_t> result(data_.begin() + static_cast<std::ptrdiff_t>(pos_),
                                         data_.begin() + static_cast<std::ptrdiff_t>(pos_ + count));
        pos_ += count;
        return result;
    }

    void skip(std::size_t count) {
        check(count);
        pos_ += count;
    }

private:
    void check(std::size_t n) const {
        if (pos_ + n > data_.size()) {
            throw ClassFileParseError(std::format(
                "Unexpected end of class data at offset {}, need {} bytes but only {} remaining",
                pos_, n, data_.size() - pos_));
        }
    }

    std::span<const std::uint8_t> data_;
    std::size_t pos_;
};

// ============================================================================
// Forward declarations for parse helpers
// ============================================================================
static std::unique_ptr<cp_info> parse_cp_entry(ByteReader& reader);
static std::unique_ptr<attribute_info> parse_attribute(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool);
static std::vector<std::unique_ptr<attribute_info>> parse_attributes(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool);
static annotation parse_annotation(ByteReader& reader);
static std::unique_ptr<element_value> parse_element_value(ByteReader& reader);
static type_annotation parse_type_annotation(ByteReader& reader);
static verification_type_info parse_verification_type(ByteReader& reader);
static stack_map_frame parse_stack_map_frame(ByteReader& reader);

// ============================================================================
// Helper: resolve UTF-8 from constant pool
// ============================================================================
static const std::string& resolve_utf8(
    const std::vector<std::unique_ptr<cp_info>>& pool,
    std::uint16_t index) {
    if (index == 0 || index >= pool.size() || !pool[index]) {
        throw ClassFileParseError(std::format(
            "Invalid constant pool UTF-8 index: {}", index));
    }
    auto* utf8 = dynamic_cast<const CONSTANT_Utf8_info*>(pool[index].get());
    if (!utf8) {
        throw ClassFileParseError(std::format(
            "Constant pool entry at index {} is not CONSTANT_Utf8_info", index));
    }
    return utf8->bytes;
}

// ============================================================================
// §4.4 Constant Pool Entry Parsing
// ============================================================================
static std::unique_ptr<cp_info> parse_cp_entry(ByteReader& reader) {
    auto tag_byte = reader.read_u1();
    auto tag = static_cast<ConstantPoolTag>(tag_byte);

    switch (tag) {
    case ConstantPoolTag::CONSTANT_Utf8: {
        auto entry = std::make_unique<CONSTANT_Utf8_info>();
        auto length = reader.read_u2();
        auto bytes = reader.read_bytes(length);
        entry->bytes = std::string(bytes.begin(), bytes.end());
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Integer: {
        auto entry = std::make_unique<CONSTANT_Integer_info>();
        entry->bytes = reader.read_u4();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Float: {
        auto entry = std::make_unique<CONSTANT_Float_info>();
        entry->bytes = reader.read_u4();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Long: {
        auto entry = std::make_unique<CONSTANT_Long_info>();
        entry->high_bytes = reader.read_u4();
        entry->low_bytes = reader.read_u4();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Double: {
        auto entry = std::make_unique<CONSTANT_Double_info>();
        entry->high_bytes = reader.read_u4();
        entry->low_bytes = reader.read_u4();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Class: {
        auto entry = std::make_unique<CONSTANT_Class_info>();
        entry->name_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_String: {
        auto entry = std::make_unique<CONSTANT_String_info>();
        entry->string_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Fieldref: {
        auto entry = std::make_unique<CONSTANT_Fieldref_info>();
        entry->class_index = reader.read_u2();
        entry->name_and_type_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Methodref: {
        auto entry = std::make_unique<CONSTANT_Methodref_info>();
        entry->class_index = reader.read_u2();
        entry->name_and_type_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_InterfaceMethodref: {
        auto entry = std::make_unique<CONSTANT_InterfaceMethodref_info>();
        entry->class_index = reader.read_u2();
        entry->name_and_type_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_NameAndType: {
        auto entry = std::make_unique<CONSTANT_NameAndType_info>();
        entry->name_index = reader.read_u2();
        entry->descriptor_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_MethodHandle: {
        auto entry = std::make_unique<CONSTANT_MethodHandle_info>();
        entry->reference_kind = reader.read_u1();
        entry->reference_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_MethodType: {
        auto entry = std::make_unique<CONSTANT_MethodType_info>();
        entry->descriptor_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Dynamic: {
        auto entry = std::make_unique<CONSTANT_Dynamic_info>();
        entry->bootstrap_method_attr_index = reader.read_u2();
        entry->name_and_type_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_InvokeDynamic: {
        auto entry = std::make_unique<CONSTANT_InvokeDynamic_info>();
        entry->bootstrap_method_attr_index = reader.read_u2();
        entry->name_and_type_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Module: {
        auto entry = std::make_unique<CONSTANT_Module_info>();
        entry->name_index = reader.read_u2();
        return entry;
    }
    case ConstantPoolTag::CONSTANT_Package: {
        auto entry = std::make_unique<CONSTANT_Package_info>();
        entry->name_index = reader.read_u2();
        return entry;
    }
    default:
        throw ClassFileParseError(std::format(
            "Unknown constant pool tag: {}", tag_byte));
    }
}

// ============================================================================
// §4.7.16.1 element_value parsing
// ============================================================================
static std::unique_ptr<element_value> parse_element_value(ByteReader& reader) {
    auto ev = std::make_unique<element_value>();
    ev->tag = reader.read_u1();
    char t = static_cast<char>(ev->tag);

    switch (t) {
    case 'B': case 'C': case 'D': case 'F':
    case 'I': case 'J': case 'S': case 'Z':
    case 's':
        ev->const_value_index = reader.read_u2();
        break;
    case 'e':
        ev->enum_const_value.type_name_index = reader.read_u2();
        ev->enum_const_value.const_name_index = reader.read_u2();
        break;
    case 'c':
        ev->class_info_index = reader.read_u2();
        break;
    case '@':
        ev->annotation_value = parse_annotation(reader);
        break;
    case '[': {
        auto num_values = reader.read_u2();
        ev->array_value.reserve(num_values);
        for (std::uint16_t i = 0; i < num_values; ++i) {
            ev->array_value.push_back(parse_element_value(reader));
        }
        break;
    }
    default:
        throw ClassFileParseError(std::format(
            "Unknown element_value tag: '{}'", t));
    }
    return ev;
}

// ============================================================================
// §4.7.16 annotation parsing
// ============================================================================
static annotation parse_annotation(ByteReader& reader) {
    annotation ann;
    ann.type_index = reader.read_u2();
    auto num_pairs = reader.read_u2();
    ann.element_value_pairs.reserve(num_pairs);
    for (std::uint16_t i = 0; i < num_pairs; ++i) {
        annotation::ElementValuePair pair;
        pair.element_name_index = reader.read_u2();
        pair.value = parse_element_value(reader);
        ann.element_value_pairs.push_back(std::move(pair));
    }
    return ann;
}

// ============================================================================
// §4.7.4 verification_type_info parsing
// ============================================================================
static verification_type_info parse_verification_type(ByteReader& reader) {
    verification_type_info vti;
    vti.tag = reader.read_u1();
    switch (vti.tag) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6:
        // Top, Integer, Float, Double, Long, Null, UninitializedThis
        break;
    case 7: // Object_variable_info
        vti.data = reader.read_u2();
        break;
    case 8: // Uninitialized_variable_info
        vti.data = reader.read_u2();
        break;
    default:
        throw ClassFileParseError(std::format(
            "Unknown verification_type_info tag: {}", vti.tag));
    }
    return vti;
}

// ============================================================================
// §4.7.4 stack_map_frame parsing
// ============================================================================
static stack_map_frame parse_stack_map_frame(ByteReader& reader) {
    stack_map_frame frame;
    frame.frame_type = reader.read_u1();

    if (frame.frame_type <= 63) {
        // same_frame: offset_delta = frame_type
        frame.offset_delta = frame.frame_type;
    } else if (frame.frame_type <= 127) {
        // same_locals_1_stack_item_frame: offset_delta = frame_type - 64
        frame.offset_delta = frame.frame_type - 64;
        frame.stack.push_back(parse_verification_type(reader));
    } else if (frame.frame_type <= 246) {
        throw ClassFileParseError(std::format(
            "Reserved stack_map_frame tag: {}", frame.frame_type));
    } else if (frame.frame_type == 247) {
        // same_locals_1_stack_item_frame_extended
        frame.offset_delta = reader.read_u2();
        frame.stack.push_back(parse_verification_type(reader));
    } else if (frame.frame_type <= 250) {
        // chop_frame
        frame.offset_delta = reader.read_u2();
    } else if (frame.frame_type == 251) {
        // same_frame_extended
        frame.offset_delta = reader.read_u2();
    } else if (frame.frame_type <= 254) {
        // append_frame
        frame.offset_delta = reader.read_u2();
        auto num_locals = frame.frame_type - 251;
        frame.locals.reserve(num_locals);
        for (int i = 0; i < num_locals; ++i) {
            frame.locals.push_back(parse_verification_type(reader));
        }
    } else {
        // full_frame (255)
        frame.offset_delta = reader.read_u2();
        auto num_locals = reader.read_u2();
        frame.locals.reserve(num_locals);
        for (std::uint16_t i = 0; i < num_locals; ++i) {
            frame.locals.push_back(parse_verification_type(reader));
        }
        auto num_stack = reader.read_u2();
        frame.stack.reserve(num_stack);
        for (std::uint16_t i = 0; i < num_stack; ++i) {
            frame.stack.push_back(parse_verification_type(reader));
        }
    }
    return frame;
}

// ============================================================================
// §4.7.20 type_annotation parsing
// ============================================================================
static type_annotation parse_type_annotation(ByteReader& reader) {
    type_annotation ta;
    ta.target_type = reader.read_u1();

    // Parse target_info based on target_type (§4.7.20.1)
    switch (ta.target_type) {
    case 0x00: case 0x01:
        // type_parameter_target
        ta.type_parameter_target.type_parameter_index = reader.read_u1();
        break;
    case 0x10:
        // supertype_target
        ta.supertype_target.supertype_index = reader.read_u2();
        break;
    case 0x11: case 0x12:
        // type_parameter_bound_target
        ta.type_parameter_bound_target.type_parameter_index = reader.read_u1();
        ta.type_parameter_bound_target.bound_index = reader.read_u1();
        break;
    case 0x13: case 0x14: case 0x15:
        // empty_target
        break;
    case 0x16:
        // formal_parameter_target
        ta.formal_parameter_target.formal_parameter_index = reader.read_u1();
        break;
    case 0x17:
        // throws_target
        ta.throws_target.throws_type_index = reader.read_u2();
        break;
    case 0x40: case 0x41: {
        // localvar_target
        auto table_length = reader.read_u2();
        ta.localvar_target.reserve(table_length);
        for (std::uint16_t i = 0; i < table_length; ++i) {
            type_annotation::LocalvarEntry entry;
            entry.start_pc = reader.read_u2();
            entry.length = reader.read_u2();
            entry.index = reader.read_u2();
            ta.localvar_target.push_back(entry);
        }
        break;
    }
    case 0x42:
        // catch_target
        ta.catch_target.exception_table_index = reader.read_u2();
        break;
    case 0x43: case 0x44: case 0x45: case 0x46:
        // offset_target
        ta.offset_target.offset = reader.read_u2();
        break;
    case 0x47: case 0x48: case 0x49: case 0x4A: case 0x4B:
        // type_argument_target
        ta.type_argument_target.offset = reader.read_u2();
        ta.type_argument_target.type_argument_index = reader.read_u1();
        break;
    default:
        throw ClassFileParseError(std::format(
            "Unknown type_annotation target_type: 0x{:02x}", ta.target_type));
    }

    // Parse type_path (§4.7.20.2)
    auto path_length = reader.read_u1();
    ta.target_path.reserve(path_length);
    for (std::uint8_t i = 0; i < path_length; ++i) {
        type_annotation::TypePathEntry entry;
        entry.type_path_kind = reader.read_u1();
        entry.type_argument_index = reader.read_u1();
        ta.target_path.push_back(entry);
    }

    // Parse annotation part
    ta.type_index = reader.read_u2();
    auto num_pairs = reader.read_u2();
    ta.element_value_pairs.reserve(num_pairs);
    for (std::uint16_t i = 0; i < num_pairs; ++i) {
        type_annotation::ElementValuePair pair;
        pair.element_name_index = reader.read_u2();
        pair.value = parse_element_value(reader);
        ta.element_value_pairs.push_back(std::move(pair));
    }

    return ta;
}

// ============================================================================
// §4.7 Attribute Parsing
// ============================================================================
static std::unique_ptr<attribute_info> parse_attribute(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool)
{
    auto name_index = reader.read_u2();
    auto length = reader.read_u4();
    auto attr_start = reader.position();

    // Resolve attribute name
    const std::string& name = resolve_utf8(constant_pool, name_index);

    auto set_base = [&](attribute_info& attr) {
        attr.attribute_name_index = name_index;
        attr.attribute_length = length;
    };

    if (name == "ConstantValue") {
        auto attr = std::make_unique<ConstantValue_attribute>();
        set_base(*attr);
        attr->constantvalue_index = reader.read_u2();
        return attr;
    }
    if (name == "Code") {
        auto attr = std::make_unique<Code_attribute>();
        set_base(*attr);
        attr->max_stack = reader.read_u2();
        attr->max_locals = reader.read_u2();
        auto code_length = reader.read_u4();
        attr->code = reader.read_bytes(code_length);
        auto exception_table_length = reader.read_u2();
        attr->exception_table.reserve(exception_table_length);
        for (std::uint16_t i = 0; i < exception_table_length; ++i) {
            Code_attribute::ExceptionTableEntry entry;
            entry.start_pc = reader.read_u2();
            entry.end_pc = reader.read_u2();
            entry.handler_pc = reader.read_u2();
            entry.catch_type = reader.read_u2();
            attr->exception_table.push_back(entry);
        }
        attr->attributes = parse_attributes(reader, constant_pool);
        return attr;
    }
    if (name == "StackMapTable") {
        auto attr = std::make_unique<StackMapTable_attribute>();
        set_base(*attr);
        auto num_entries = reader.read_u2();
        attr->entries.reserve(num_entries);
        for (std::uint16_t i = 0; i < num_entries; ++i) {
            attr->entries.push_back(parse_stack_map_frame(reader));
        }
        return attr;
    }
    if (name == "Exceptions") {
        auto attr = std::make_unique<Exceptions_attribute>();
        set_base(*attr);
        auto num_exceptions = reader.read_u2();
        attr->exception_index_table.reserve(num_exceptions);
        for (std::uint16_t i = 0; i < num_exceptions; ++i) {
            attr->exception_index_table.push_back(reader.read_u2());
        }
        return attr;
    }
    if (name == "InnerClasses") {
        auto attr = std::make_unique<InnerClasses_attribute>();
        set_base(*attr);
        auto num_classes = reader.read_u2();
        attr->classes.reserve(num_classes);
        for (std::uint16_t i = 0; i < num_classes; ++i) {
            InnerClasses_attribute::InnerClassEntry entry;
            entry.inner_class_info_index = reader.read_u2();
            entry.outer_class_info_index = reader.read_u2();
            entry.inner_name_index = reader.read_u2();
            entry.inner_class_access_flags = reader.read_u2();
            attr->classes.push_back(entry);
        }
        return attr;
    }
    if (name == "EnclosingMethod") {
        auto attr = std::make_unique<EnclosingMethod_attribute>();
        set_base(*attr);
        attr->class_index = reader.read_u2();
        attr->method_index = reader.read_u2();
        return attr;
    }
    if (name == "Synthetic") {
        auto attr = std::make_unique<Synthetic_attribute>();
        set_base(*attr);
        return attr;
    }
    if (name == "Signature") {
        auto attr = std::make_unique<Signature_attribute>();
        set_base(*attr);
        attr->signature_index = reader.read_u2();
        return attr;
    }
    if (name == "SourceFile") {
        auto attr = std::make_unique<SourceFile_attribute>();
        set_base(*attr);
        attr->sourcefile_index = reader.read_u2();
        return attr;
    }
    if (name == "SourceDebugExtension") {
        auto attr = std::make_unique<SourceDebugExtension_attribute>();
        set_base(*attr);
        attr->debug_extension = reader.read_bytes(length);
        return attr;
    }
    if (name == "LineNumberTable") {
        auto attr = std::make_unique<LineNumberTable_attribute>();
        set_base(*attr);
        auto table_length = reader.read_u2();
        attr->line_number_table.reserve(table_length);
        for (std::uint16_t i = 0; i < table_length; ++i) {
            LineNumberTable_attribute::LineNumberEntry entry;
            entry.start_pc = reader.read_u2();
            entry.line_number = reader.read_u2();
            attr->line_number_table.push_back(entry);
        }
        return attr;
    }
    if (name == "LocalVariableTable") {
        auto attr = std::make_unique<LocalVariableTable_attribute>();
        set_base(*attr);
        auto table_length = reader.read_u2();
        attr->local_variable_table.reserve(table_length);
        for (std::uint16_t i = 0; i < table_length; ++i) {
            LocalVariableTable_attribute::LocalVariableEntry entry;
            entry.start_pc = reader.read_u2();
            entry.length = reader.read_u2();
            entry.name_index = reader.read_u2();
            entry.descriptor_index = reader.read_u2();
            entry.index = reader.read_u2();
            attr->local_variable_table.push_back(entry);
        }
        return attr;
    }
    if (name == "LocalVariableTypeTable") {
        auto attr = std::make_unique<LocalVariableTypeTable_attribute>();
        set_base(*attr);
        auto table_length = reader.read_u2();
        attr->local_variable_type_table.reserve(table_length);
        for (std::uint16_t i = 0; i < table_length; ++i) {
            LocalVariableTypeTable_attribute::LocalVariableTypeEntry entry;
            entry.start_pc = reader.read_u2();
            entry.length = reader.read_u2();
            entry.name_index = reader.read_u2();
            entry.signature_index = reader.read_u2();
            entry.index = reader.read_u2();
            attr->local_variable_type_table.push_back(entry);
        }
        return attr;
    }
    if (name == "Deprecated") {
        auto attr = std::make_unique<Deprecated_attribute>();
        set_base(*attr);
        return attr;
    }
    if (name == "RuntimeVisibleAnnotations") {
        auto attr = std::make_unique<RuntimeVisibleAnnotations_attribute>();
        set_base(*attr);
        auto num_annotations = reader.read_u2();
        attr->annotations.reserve(num_annotations);
        for (std::uint16_t i = 0; i < num_annotations; ++i) {
            attr->annotations.push_back(parse_annotation(reader));
        }
        return attr;
    }
    if (name == "RuntimeInvisibleAnnotations") {
        auto attr = std::make_unique<RuntimeInvisibleAnnotations_attribute>();
        set_base(*attr);
        auto num_annotations = reader.read_u2();
        attr->annotations.reserve(num_annotations);
        for (std::uint16_t i = 0; i < num_annotations; ++i) {
            attr->annotations.push_back(parse_annotation(reader));
        }
        return attr;
    }
    if (name == "RuntimeVisibleParameterAnnotations") {
        auto attr = std::make_unique<RuntimeVisibleParameterAnnotations_attribute>();
        set_base(*attr);
        auto num_params = reader.read_u1();
        attr->parameter_annotations.reserve(num_params);
        for (std::uint8_t i = 0; i < num_params; ++i) {
            RuntimeVisibleParameterAnnotations_attribute::ParameterAnnotation pa;
            auto num_annotations = reader.read_u2();
            pa.annotations.reserve(num_annotations);
            for (std::uint16_t j = 0; j < num_annotations; ++j) {
                pa.annotations.push_back(parse_annotation(reader));
            }
            attr->parameter_annotations.push_back(std::move(pa));
        }
        return attr;
    }
    if (name == "RuntimeInvisibleParameterAnnotations") {
        auto attr = std::make_unique<RuntimeInvisibleParameterAnnotations_attribute>();
        set_base(*attr);
        auto num_params = reader.read_u1();
        attr->parameter_annotations.reserve(num_params);
        for (std::uint8_t i = 0; i < num_params; ++i) {
            RuntimeInvisibleParameterAnnotations_attribute::ParameterAnnotation pa;
            auto num_annotations = reader.read_u2();
            pa.annotations.reserve(num_annotations);
            for (std::uint16_t j = 0; j < num_annotations; ++j) {
                pa.annotations.push_back(parse_annotation(reader));
            }
            attr->parameter_annotations.push_back(std::move(pa));
        }
        return attr;
    }
    if (name == "RuntimeVisibleTypeAnnotations") {
        auto attr = std::make_unique<RuntimeVisibleTypeAnnotations_attribute>();
        set_base(*attr);
        auto num_annotations = reader.read_u2();
        attr->annotations.reserve(num_annotations);
        for (std::uint16_t i = 0; i < num_annotations; ++i) {
            attr->annotations.push_back(parse_type_annotation(reader));
        }
        return attr;
    }
    if (name == "RuntimeInvisibleTypeAnnotations") {
        auto attr = std::make_unique<RuntimeInvisibleTypeAnnotations_attribute>();
        set_base(*attr);
        auto num_annotations = reader.read_u2();
        attr->annotations.reserve(num_annotations);
        for (std::uint16_t i = 0; i < num_annotations; ++i) {
            attr->annotations.push_back(parse_type_annotation(reader));
        }
        return attr;
    }
    if (name == "AnnotationDefault") {
        auto attr = std::make_unique<AnnotationDefault_attribute>();
        set_base(*attr);
        attr->default_value = parse_element_value(reader);
        return attr;
    }
    if (name == "BootstrapMethods") {
        auto attr = std::make_unique<BootstrapMethods_attribute>();
        set_base(*attr);
        auto num_methods = reader.read_u2();
        attr->bootstrap_methods.reserve(num_methods);
        for (std::uint16_t i = 0; i < num_methods; ++i) {
            BootstrapMethods_attribute::BootstrapMethod bm;
            bm.bootstrap_method_ref = reader.read_u2();
            auto num_args = reader.read_u2();
            bm.bootstrap_arguments.reserve(num_args);
            for (std::uint16_t j = 0; j < num_args; ++j) {
                bm.bootstrap_arguments.push_back(reader.read_u2());
            }
            attr->bootstrap_methods.push_back(std::move(bm));
        }
        return attr;
    }
    if (name == "MethodParameters") {
        auto attr = std::make_unique<MethodParameters_attribute>();
        set_base(*attr);
        auto count = reader.read_u1();
        attr->parameters.reserve(count);
        for (std::uint8_t i = 0; i < count; ++i) {
            MethodParameters_attribute::Parameter param;
            param.name_index = reader.read_u2();
            param.access_flags = reader.read_u2();
            attr->parameters.push_back(param);
        }
        return attr;
    }
    if (name == "Module") {
        auto attr = std::make_unique<Module_attribute>();
        set_base(*attr);
        attr->module_name_index = reader.read_u2();
        attr->module_flags = reader.read_u2();
        attr->module_version_index = reader.read_u2();

        auto requires_count = reader.read_u2();
        attr->requires_entries.reserve(requires_count);
        for (std::uint16_t i = 0; i < requires_count; ++i) {
            Module_attribute::Requires req;
            req.requires_index = reader.read_u2();
            req.requires_flags = reader.read_u2();
            req.requires_version_index = reader.read_u2();
            attr->requires_entries.push_back(req);
        }

        auto exports_count = reader.read_u2();
        attr->exports_entries.reserve(exports_count);
        for (std::uint16_t i = 0; i < exports_count; ++i) {
            Module_attribute::Exports exp;
            exp.exports_index = reader.read_u2();
            exp.exports_flags = reader.read_u2();
            auto to_count = reader.read_u2();
            exp.exports_to_index.reserve(to_count);
            for (std::uint16_t j = 0; j < to_count; ++j) {
                exp.exports_to_index.push_back(reader.read_u2());
            }
            attr->exports_entries.push_back(std::move(exp));
        }

        auto opens_count = reader.read_u2();
        attr->opens_entries.reserve(opens_count);
        for (std::uint16_t i = 0; i < opens_count; ++i) {
            Module_attribute::Opens opn;
            opn.opens_index = reader.read_u2();
            opn.opens_flags = reader.read_u2();
            auto to_count = reader.read_u2();
            opn.opens_to_index.reserve(to_count);
            for (std::uint16_t j = 0; j < to_count; ++j) {
                opn.opens_to_index.push_back(reader.read_u2());
            }
            attr->opens_entries.push_back(std::move(opn));
        }

        auto uses_count = reader.read_u2();
        attr->uses_index.reserve(uses_count);
        for (std::uint16_t i = 0; i < uses_count; ++i) {
            attr->uses_index.push_back(reader.read_u2());
        }

        auto provides_count = reader.read_u2();
        attr->provides_entries.reserve(provides_count);
        for (std::uint16_t i = 0; i < provides_count; ++i) {
            Module_attribute::Provides prov;
            prov.provides_index = reader.read_u2();
            auto with_count = reader.read_u2();
            prov.provides_with_index.reserve(with_count);
            for (std::uint16_t j = 0; j < with_count; ++j) {
                prov.provides_with_index.push_back(reader.read_u2());
            }
            attr->provides_entries.push_back(std::move(prov));
        }
        return attr;
    }
    if (name == "ModulePackages") {
        auto attr = std::make_unique<ModulePackages_attribute>();
        set_base(*attr);
        auto count = reader.read_u2();
        attr->package_index.reserve(count);
        for (std::uint16_t i = 0; i < count; ++i) {
            attr->package_index.push_back(reader.read_u2());
        }
        return attr;
    }
    if (name == "ModuleMainClass") {
        auto attr = std::make_unique<ModuleMainClass_attribute>();
        set_base(*attr);
        attr->main_class_index = reader.read_u2();
        return attr;
    }
    if (name == "NestHost") {
        auto attr = std::make_unique<NestHost_attribute>();
        set_base(*attr);
        attr->host_class_index = reader.read_u2();
        return attr;
    }
    if (name == "NestMembers") {
        auto attr = std::make_unique<NestMembers_attribute>();
        set_base(*attr);
        auto count = reader.read_u2();
        attr->classes.reserve(count);
        for (std::uint16_t i = 0; i < count; ++i) {
            attr->classes.push_back(reader.read_u2());
        }
        return attr;
    }
    if (name == "Record") {
        auto attr = std::make_unique<Record_attribute>();
        set_base(*attr);
        auto count = reader.read_u2();
        attr->components.reserve(count);
        for (std::uint16_t i = 0; i < count; ++i) {
            Record_attribute::RecordComponentInfo comp;
            comp.name_index = reader.read_u2();
            comp.descriptor_index = reader.read_u2();
            comp.attributes = parse_attributes(reader, constant_pool);
            attr->components.push_back(std::move(comp));
        }
        return attr;
    }
    if (name == "PermittedSubclasses") {
        auto attr = std::make_unique<PermittedSubclasses_attribute>();
        set_base(*attr);
        auto count = reader.read_u2();
        attr->classes.reserve(count);
        for (std::uint16_t i = 0; i < count; ++i) {
            attr->classes.push_back(reader.read_u2());
        }
        return attr;
    }

    // Unknown attribute - skip raw bytes (§4.7.1)
    auto attr = std::make_unique<Unknown_attribute>();
    set_base(*attr);
    attr->info = reader.read_bytes(length);
    // Verify we consumed exactly the right number of bytes
    auto consumed = reader.position() - attr_start;
    if (consumed != length) {
        // This path should not be reached for Unknown_attribute as we read exactly 'length'
        throw ClassFileParseError(std::format(
            "Attribute '{}' consumed {} bytes but declared length {}",
            name, consumed, length));
    }
    return attr;
}

// ============================================================================
// Parse multiple attributes
// ============================================================================
static std::vector<std::unique_ptr<attribute_info>> parse_attributes(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool)
{
    auto count = reader.read_u2();
    std::vector<std::unique_ptr<attribute_info>> attrs;
    attrs.reserve(count);
    for (std::uint16_t i = 0; i < count; ++i) {
        attrs.push_back(parse_attribute(reader, constant_pool));
    }
    return attrs;
}

// ============================================================================
// Parse field_info
// ============================================================================
static field_info parse_field(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool)
{
    field_info fi;
    fi.access_flags = reader.read_u2();
    fi.name_index = reader.read_u2();
    fi.descriptor_index = reader.read_u2();
    fi.attributes = parse_attributes(reader, constant_pool);
    return fi;
}

// ============================================================================
// Parse method_info
// ============================================================================
static method_info parse_method(
    ByteReader& reader,
    const std::vector<std::unique_ptr<cp_info>>& constant_pool)
{
    method_info mi;
    mi.access_flags = reader.read_u2();
    mi.name_index = reader.read_u2();
    mi.descriptor_index = reader.read_u2();
    mi.attributes = parse_attributes(reader, constant_pool);
    return mi;
}

// ============================================================================
// §4.1 ClassFile Constructor - Main Parse Entry Point
// ============================================================================
ClassFile::ClassFile(std::vector<std::uint8_t> data) {
    std::span<const std::uint8_t> byte_span{data};
    ByteReader reader{byte_span};

    // Magic number
    magic = reader.read_u4();
    if (magic != 0xCAFEBABE) {
        throw ClassFileParseError(std::format(
            "Invalid magic number: 0x{:08X}, expected 0xCAFEBABE", magic));
    }

    // Version
    minor_version = reader.read_u2();
    major_version = reader.read_u2();

    // §4.4 Constant Pool
    auto constant_pool_count = reader.read_u2();
    constant_pool.resize(constant_pool_count);
    // constant_pool[0] is unused (nullptr), entries are 1-indexed
    for (std::uint16_t i = 1; i < constant_pool_count; ++i) {
        constant_pool[i] = parse_cp_entry(reader);
        // §4.4.5: Long and Double entries occupy two constant pool slots
        if (constant_pool[i]->tag == ConstantPoolTag::CONSTANT_Long ||
            constant_pool[i]->tag == ConstantPoolTag::CONSTANT_Double) {
            ++i; // skip next index (it remains nullptr)
        }
    }

    // §4.1 Access flags, this/super class, interfaces
    access_flags = reader.read_u2();
    this_class = reader.read_u2();
    super_class = reader.read_u2();

    auto interfaces_count = reader.read_u2();
    interfaces.reserve(interfaces_count);
    for (std::uint16_t i = 0; i < interfaces_count; ++i) {
        interfaces.push_back(reader.read_u2());
    }

    // §4.5 Fields
    auto fields_count = reader.read_u2();
    fields.reserve(fields_count);
    for (std::uint16_t i = 0; i < fields_count; ++i) {
        fields.push_back(parse_field(reader, constant_pool));
    }

    // §4.6 Methods
    auto methods_count = reader.read_u2();
    methods.reserve(methods_count);
    for (std::uint16_t i = 0; i < methods_count; ++i) {
        methods.push_back(parse_method(reader, constant_pool));
    }

    // §4.7 Attributes
    attributes = parse_attributes(reader, constant_pool);
}

// ============================================================================
// Helper: get UTF-8 string from constant pool
// ============================================================================
const std::string& ClassFile::get_utf8(std::uint16_t index) const {
    return resolve_utf8(constant_pool, index);
}

// ============================================================================
// §4.3.2 Static Reference Field Metadata
// ============================================================================
void ClassFile::compute_static_ref_fields() const {
    if (static_ref_fields_computed_) return;

    for (const auto& f : fields) {
        // Only static fields
        if (!(f.access_flags & FieldAccess::ACC_STATIC)) continue;

        // Resolve descriptor from constant pool
        const auto& desc = resolve_utf8(constant_pool, f.descriptor_index);
        if (desc.empty()) continue;

        // §4.3.2: Reference types start with 'L' (object) or '[' (array)
        char first = desc[0];
        if (first == 'L' || first == '[') {
            const auto& name = resolve_utf8(constant_pool, f.name_index);
            static_ref_field_names_.push_back(name);
        }
    }

    static_ref_fields_computed_ = true;
}

const std::vector<std::string>& ClassFile::get_static_ref_field_names() const {
    compute_static_ref_fields();
    return static_ref_field_names_;
}

} // namespace aijvm::classfile
