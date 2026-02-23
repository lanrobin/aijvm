package com.aijvm;

/** Constant pool for a Java class file (JVMS §4.4). */
public class ConstantPool {

    // Tag constants
    public static final int CONSTANT_Utf8               = 1;
    public static final int CONSTANT_Integer            = 3;
    public static final int CONSTANT_Float              = 4;
    public static final int CONSTANT_Long               = 5;
    public static final int CONSTANT_Double             = 6;
    public static final int CONSTANT_Class              = 7;
    public static final int CONSTANT_String             = 8;
    public static final int CONSTANT_Fieldref           = 9;
    public static final int CONSTANT_Methodref          = 10;
    public static final int CONSTANT_InterfaceMethodref = 11;
    public static final int CONSTANT_NameAndType        = 12;
    public static final int CONSTANT_MethodHandle       = 15;
    public static final int CONSTANT_MethodType         = 16;
    public static final int CONSTANT_InvokeDynamic      = 18;

    private final Object[] entries;

    public ConstantPool(int count) {
        entries = new Object[count];
    }

    public void set(int index, Object entry) {
        entries[index] = entry;
    }

    public Object get(int index) {
        return entries[index];
    }

    /** Returns the UTF-8 string at the given index. */
    public String getUtf8(int index) {
        Object entry = entries[index];
        if (entry instanceof Utf8Entry e) return e.value;
        throw new RuntimeException("CP[" + index + "] is not Utf8: " + entry);
    }

    /** Returns the binary class name at a Class entry index (e.g. "java/lang/String"). */
    public String getClassName(int index) {
        Object entry = entries[index];
        if (entry instanceof ClassEntry e) return getUtf8(e.nameIndex);
        throw new RuntimeException("CP[" + index + "] is not Class: " + entry);
    }

    /**
     * Resolves a Fieldref / Methodref / InterfaceMethodref entry.
     * @return [className, memberName, descriptor]
     */
    public String[] resolveMemberRef(int index) {
        Object entry = entries[index];
        int classIndex, natIndex;
        if (entry instanceof FieldrefEntry e)          { classIndex = e.classIndex; natIndex = e.nameAndTypeIndex; }
        else if (entry instanceof MethodrefEntry e)    { classIndex = e.classIndex; natIndex = e.nameAndTypeIndex; }
        else if (entry instanceof InterfaceMethodrefEntry e) { classIndex = e.classIndex; natIndex = e.nameAndTypeIndex; }
        else throw new RuntimeException("CP[" + index + "] is not a member ref: " + entry);

        String className  = getClassName(classIndex);
        String memberName = getUtf8(((NameAndTypeEntry) entries[natIndex]).nameIndex);
        String descriptor = getUtf8(((NameAndTypeEntry) entries[natIndex]).descriptorIndex);
        return new String[]{className, memberName, descriptor};
    }

    /** Resolves a loadable constant (Integer, Long, Float, Double, String, Class). */
    public Object resolveLoadable(int index) {
        Object entry = entries[index];
        if (entry instanceof IntegerEntry e)  return e.value;
        if (entry instanceof FloatEntry e)    return e.value;
        if (entry instanceof LongEntry e)     return e.value;
        if (entry instanceof DoubleEntry e)   return e.value;
        if (entry instanceof StringEntry e)   return getUtf8(e.stringIndex);
        if (entry instanceof ClassEntry)      return getClassName(index);
        throw new RuntimeException("CP[" + index + "] is not loadable: " + entry);
    }

    // ── Entry types ─────────────────────────────────────────────────────────

    public record Utf8Entry(String value) {}
    public record IntegerEntry(int value) {}
    public record FloatEntry(float value) {}
    public record LongEntry(long value) {}
    public record DoubleEntry(double value) {}
    public record ClassEntry(int nameIndex) {}
    public record StringEntry(int stringIndex) {}
    public record FieldrefEntry(int classIndex, int nameAndTypeIndex) {}
    public record MethodrefEntry(int classIndex, int nameAndTypeIndex) {}
    public record InterfaceMethodrefEntry(int classIndex, int nameAndTypeIndex) {}
    public record NameAndTypeEntry(int nameIndex, int descriptorIndex) {}
    public record MethodHandleEntry(int referenceKind, int referenceIndex) {}
    public record MethodTypeEntry(int descriptorIndex) {}
    public record InvokeDynamicEntry(int bootstrapMethodAttrIndex, int nameAndTypeIndex) {}
}
