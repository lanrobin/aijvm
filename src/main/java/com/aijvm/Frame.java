package com.aijvm;

import java.util.ArrayDeque;
import java.util.Deque;

/**
 * JVM execution frame: local variable table + operand stack.
 * Long and double values occupy one logical slot in this implementation.
 */
public class Frame {

    private final Object[] locals;
    private final Deque<Object> stack = new ArrayDeque<>();

    public Frame(int maxLocals) {
        this.locals = new Object[Math.max(maxLocals, 1)];
    }

    // ── Local variables ─────────────────────────────────────────────────────

    public void setLocal(int index, Object value) {
        locals[index] = value;
    }

    public Object getLocal(int index) {
        return locals[index];
    }

    public int getLocalInt(int index) {
        Object v = locals[index];
        if (v instanceof Integer i)   return i;
        if (v instanceof Boolean b)   return b ? 1 : 0;
        if (v instanceof Byte b)      return b;
        if (v instanceof Short s)     return s;
        if (v instanceof Character c) return c;
        throw new RuntimeException("local[" + index + "] is not int-compatible: "
                + (v == null ? "null" : v.getClass().getName()));
    }

    public long getLocalLong(int index) {
        Object v = locals[index];
        if (v instanceof Long l) return l;
        throw new RuntimeException("local[" + index + "] is not long: " + v);
    }

    public float getLocalFloat(int index) {
        Object v = locals[index];
        if (v instanceof Float f) return f;
        throw new RuntimeException("local[" + index + "] is not float: " + v);
    }

    public double getLocalDouble(int index) {
        Object v = locals[index];
        if (v instanceof Double d) return d;
        throw new RuntimeException("local[" + index + "] is not double: " + v);
    }

    // ── Operand stack ────────────────────────────────────────────────────────

    public void push(Object value)  { stack.push(value); }
    public void pushInt(int v)      { stack.push(v); }
    public void pushLong(long v)    { stack.push(v); }
    public void pushFloat(float v)  { stack.push(v); }
    public void pushDouble(double v){ stack.push(v); }

    public Object pop() {
        if (stack.isEmpty()) throw new RuntimeException("Operand stack underflow");
        return stack.pop();
    }

    public int popInt() {
        Object v = pop();
        if (v instanceof Integer i)   return i;
        if (v instanceof Boolean b)   return b ? 1 : 0;
        if (v instanceof Byte b)      return (int) b;
        if (v instanceof Short s)     return (int) s;
        if (v instanceof Character c) return (int) c;
        throw new RuntimeException("Stack top is not int-compatible: "
                + (v == null ? "null" : v.getClass().getName()));
    }

    public long popLong() {
        Object v = pop();
        if (v instanceof Long l) return l;
        throw new RuntimeException("Stack top is not long: " + v);
    }

    public float popFloat() {
        Object v = pop();
        if (v instanceof Float f) return f;
        throw new RuntimeException("Stack top is not float: " + v);
    }

    public double popDouble() {
        Object v = pop();
        if (v instanceof Double d) return d;
        throw new RuntimeException("Stack top is not double: " + v);
    }

    public Object peek() { return stack.peek(); }
    public int stackSize() { return stack.size(); }
    public boolean stackIsEmpty() { return stack.isEmpty(); }
}
