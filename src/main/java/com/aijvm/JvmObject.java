package com.aijvm;

import java.util.HashMap;
import java.util.Map;

/** A runtime JVM object instance. */
public class JvmObject {

    /** Binary class name, e.g. {@code "java/lang/StringBuilder"}. */
    public final String className;

    /** Instance fields, keyed by field name. */
    private final Map<String, Object> fields = new HashMap<>();

    /**
     * Optional native backing object (e.g. a real {@link StringBuilder}
     * for {@code java/lang/StringBuilder} instances).
     */
    public Object nativeObject;

    public JvmObject(String className) {
        this.className = className;
    }

    public void setField(String name, Object value) {
        fields.put(name, value);
    }

    public Object getField(String name) {
        return fields.get(name);
    }

    @Override
    public String toString() {
        if (nativeObject != null) return nativeObject.toString();
        return className + "@" + Integer.toHexString(System.identityHashCode(this));
    }
}
