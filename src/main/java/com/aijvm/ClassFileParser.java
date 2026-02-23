package com.aijvm;

import java.io.*;
import java.nio.file.*;

/** Parses binary {@code .class} files into {@link ClassFile} objects (JVMS §4). */
public class ClassFileParser {

    private static final int MAGIC = 0xCAFEBABE;

    /** Parses from a file on disk. */
    public ClassFile parse(Path path) throws IOException {
        return parse(Files.readAllBytes(path));
    }

    /** Parses from a raw byte array. */
    public ClassFile parse(byte[] bytes) throws IOException {
        return parse(new DataInputStream(new ByteArrayInputStream(bytes)));
    }

    /** Parses from a DataInputStream. */
    public ClassFile parse(DataInputStream in) throws IOException {
        ClassFile cf = new ClassFile();

        int magic = in.readInt();
        if (magic != MAGIC) {
            throw new IOException(String.format("Bad magic: 0x%08X (expected 0xCAFEBABE)", magic));
        }

        cf.minorVersion = in.readUnsignedShort();
        cf.majorVersion = in.readUnsignedShort();
        cf.constantPool = parseConstantPool(in);
        cf.accessFlags  = in.readUnsignedShort();

        int thisIdx  = in.readUnsignedShort();
        int superIdx = in.readUnsignedShort();
        cf.thisClass  = cf.constantPool.getClassName(thisIdx);
        cf.superClass = superIdx == 0 ? null : cf.constantPool.getClassName(superIdx);

        int ifCount = in.readUnsignedShort();
        for (int i = 0; i < ifCount; i++) {
            cf.interfaces.add(cf.constantPool.getClassName(in.readUnsignedShort()));
        }

        int fieldCount = in.readUnsignedShort();
        for (int i = 0; i < fieldCount; i++) {
            cf.fields.add(parseField(in, cf.constantPool));
        }

        int methodCount = in.readUnsignedShort();
        for (int i = 0; i < methodCount; i++) {
            cf.methods.add(parseMethod(in, cf.constantPool));
        }

        int attrCount = in.readUnsignedShort();
        for (int i = 0; i < attrCount; i++) {
            cf.attributes.add(parseAttribute(in, cf.constantPool));
        }

        return cf;
    }

    // ── Constant pool ───────────────────────────────────────────────────────

    private ConstantPool parseConstantPool(DataInputStream in) throws IOException {
        int count = in.readUnsignedShort();
        ConstantPool cp = new ConstantPool(count);

        for (int i = 1; i < count; i++) {
            int tag = in.readUnsignedByte();
            switch (tag) {
                case ConstantPool.CONSTANT_Utf8 ->
                    cp.set(i, new ConstantPool.Utf8Entry(in.readUTF()));
                case ConstantPool.CONSTANT_Integer ->
                    cp.set(i, new ConstantPool.IntegerEntry(in.readInt()));
                case ConstantPool.CONSTANT_Float ->
                    cp.set(i, new ConstantPool.FloatEntry(in.readFloat()));
                case ConstantPool.CONSTANT_Long -> {
                    cp.set(i, new ConstantPool.LongEntry(in.readLong()));
                    i++; // long/double occupy two slots
                }
                case ConstantPool.CONSTANT_Double -> {
                    cp.set(i, new ConstantPool.DoubleEntry(in.readDouble()));
                    i++;
                }
                case ConstantPool.CONSTANT_Class ->
                    cp.set(i, new ConstantPool.ClassEntry(in.readUnsignedShort()));
                case ConstantPool.CONSTANT_String ->
                    cp.set(i, new ConstantPool.StringEntry(in.readUnsignedShort()));
                case ConstantPool.CONSTANT_Fieldref ->
                    cp.set(i, new ConstantPool.FieldrefEntry(
                            in.readUnsignedShort(), in.readUnsignedShort()));
                case ConstantPool.CONSTANT_Methodref ->
                    cp.set(i, new ConstantPool.MethodrefEntry(
                            in.readUnsignedShort(), in.readUnsignedShort()));
                case ConstantPool.CONSTANT_InterfaceMethodref ->
                    cp.set(i, new ConstantPool.InterfaceMethodrefEntry(
                            in.readUnsignedShort(), in.readUnsignedShort()));
                case ConstantPool.CONSTANT_NameAndType ->
                    cp.set(i, new ConstantPool.NameAndTypeEntry(
                            in.readUnsignedShort(), in.readUnsignedShort()));
                case ConstantPool.CONSTANT_MethodHandle ->
                    cp.set(i, new ConstantPool.MethodHandleEntry(
                            in.readUnsignedByte(), in.readUnsignedShort()));
                case ConstantPool.CONSTANT_MethodType ->
                    cp.set(i, new ConstantPool.MethodTypeEntry(in.readUnsignedShort()));
                case ConstantPool.CONSTANT_InvokeDynamic ->
                    cp.set(i, new ConstantPool.InvokeDynamicEntry(
                            in.readUnsignedShort(), in.readUnsignedShort()));
                default -> throw new IOException("Unknown CP tag " + tag + " at index " + i);
            }
        }
        return cp;
    }

    // ── Fields / methods / attributes ───────────────────────────────────────

    private ClassFile.FieldInfo parseField(DataInputStream in, ConstantPool cp) throws IOException {
        ClassFile.FieldInfo f = new ClassFile.FieldInfo();
        f.accessFlags = in.readUnsignedShort();
        f.name        = cp.getUtf8(in.readUnsignedShort());
        f.descriptor  = cp.getUtf8(in.readUnsignedShort());
        int n = in.readUnsignedShort();
        for (int i = 0; i < n; i++) f.attributes.add(parseAttribute(in, cp));
        return f;
    }

    private ClassFile.MethodInfo parseMethod(DataInputStream in, ConstantPool cp) throws IOException {
        ClassFile.MethodInfo m = new ClassFile.MethodInfo();
        m.accessFlags = in.readUnsignedShort();
        m.name        = cp.getUtf8(in.readUnsignedShort());
        m.descriptor  = cp.getUtf8(in.readUnsignedShort());
        int n = in.readUnsignedShort();
        for (int i = 0; i < n; i++) m.attributes.add(parseAttribute(in, cp));
        return m;
    }

    private ClassFile.AttributeInfo parseAttribute(DataInputStream in, ConstantPool cp) throws IOException {
        String name   = cp.getUtf8(in.readUnsignedShort());
        int    length = in.readInt();

        if ("Code".equals(name)) {
            return parseCodeAttribute(in, cp);
        }

        ClassFile.AttributeInfo attr = new ClassFile.AttributeInfo();
        attr.name = name;
        attr.data = in.readNBytes(length);
        return attr;
    }

    private ClassFile.CodeAttribute parseCodeAttribute(DataInputStream in, ConstantPool cp) throws IOException {
        ClassFile.CodeAttribute ca = new ClassFile.CodeAttribute();
        ca.name      = "Code";
        ca.maxStack  = in.readUnsignedShort();
        ca.maxLocals = in.readUnsignedShort();

        int codeLen = in.readInt();
        ca.code = in.readNBytes(codeLen);

        int exLen = in.readUnsignedShort();
        for (int i = 0; i < exLen; i++) {
            ClassFile.ExceptionHandler eh = new ClassFile.ExceptionHandler();
            eh.startPc   = in.readUnsignedShort();
            eh.endPc     = in.readUnsignedShort();
            eh.handlerPc = in.readUnsignedShort();
            eh.catchType = in.readUnsignedShort();
            ca.exceptionHandlers.add(eh);
        }

        int attrCount = in.readUnsignedShort();
        for (int i = 0; i < attrCount; i++) {
            ca.attributes.add(parseAttribute(in, cp));
        }
        return ca;
    }
}
