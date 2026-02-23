package com.aijvm;

import java.util.ArrayList;
import java.util.List;

/** Data model for a parsed Java class file (JVMS §4). */
public class ClassFile {

    public int minorVersion;
    public int majorVersion;
    public ConstantPool constantPool;
    public int accessFlags;
    public String thisClass;
    public String superClass;
    public List<String> interfaces = new ArrayList<>();
    public List<FieldInfo> fields = new ArrayList<>();
    public List<MethodInfo> methods = new ArrayList<>();
    public List<AttributeInfo> attributes = new ArrayList<>();

    /** Finds a method by exact name + descriptor match. */
    public MethodInfo findMethod(String name, String descriptor) {
        for (MethodInfo m : methods) {
            if (m.name.equals(name) && m.descriptor.equals(descriptor)) return m;
        }
        return null;
    }

    /** Finds the first method with the given name. */
    public MethodInfo findMethodByName(String name) {
        for (MethodInfo m : methods) {
            if (m.name.equals(name)) return m;
        }
        return null;
    }

    // ── Inner data types ────────────────────────────────────────────────────

    public static class FieldInfo {
        public int accessFlags;
        public String name;
        public String descriptor;
        public List<AttributeInfo> attributes = new ArrayList<>();
    }

    public static class MethodInfo {
        public int accessFlags;
        public String name;
        public String descriptor;
        public List<AttributeInfo> attributes = new ArrayList<>();

        /** Returns the Code attribute, or null if the method is native/abstract. */
        public CodeAttribute getCode() {
            for (AttributeInfo a : attributes) {
                if (a instanceof CodeAttribute ca) return ca;
            }
            return null;
        }
    }

    /** Generic attribute (raw bytes). */
    public static class AttributeInfo {
        public String name;
        public byte[] data;
    }

    /** Code attribute – contains the bytecode for a method (JVMS §4.7.3). */
    public static class CodeAttribute extends AttributeInfo {
        public int maxStack;
        public int maxLocals;
        public byte[] code;
        public List<ExceptionHandler> exceptionHandlers = new ArrayList<>();
        public List<AttributeInfo> attributes = new ArrayList<>();
    }

    /** One entry in the exception table of a Code attribute. */
    public static class ExceptionHandler {
        public int startPc;
        public int endPc;
        public int handlerPc;
        public int catchType;   // CP index of caught class; 0 = catch all (finally)
    }
}
