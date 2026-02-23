package com.aijvm;

import java.io.*;
import java.nio.file.*;
import java.util.*;

/**
 * NanoJVM – a minimal Java Virtual Machine interpreter.
 *
 * <p>Supports a broad subset of JVM bytecodes and provides native-method
 * stubs for the most commonly used standard-library classes
 * (System.out, StringBuilder, String, Math, Integer, etc.).
 */
public class NanoJVM {

    // ── State ────────────────────────────────────────────────────────────────

    /** Loaded classes keyed by binary class name (e.g. {@code "com/example/Foo"}). */
    private final Map<String, ClassFile> classes = new HashMap<>();

    /** Static fields, keyed by {@code "className.fieldName"}. */
    private final Map<String, Object> staticFields = new HashMap<>();

    /** Directories / JAR paths to search for {@code .class} files. */
    private final List<Path> classPath = new ArrayList<>();

    private final ClassFileParser parser = new ClassFileParser();

    /** Destination for output (default {@link System#out}). */
    private PrintStream output = System.out;

    // ── Construction ─────────────────────────────────────────────────────────

    public NanoJVM() {
        classPath.add(Paths.get("."));
    }

    public NanoJVM(Path... paths) {
        classPath.addAll(Arrays.asList(paths));
    }

    public void setOutput(PrintStream out) { this.output = out; }
    public void addClassPath(Path path)    { classPath.add(path); }

    // ── Class loading ────────────────────────────────────────────────────────

    /** Loads a class from a raw byte array and registers it. */
    public ClassFile loadClass(byte[] bytes) throws IOException {
        ClassFile cf = parser.parse(bytes);
        classes.put(cf.thisClass, cf);
        return cf;
    }

    /** Loads a class from a {@code .class} file and registers it. */
    public ClassFile loadClass(Path path) throws IOException {
        ClassFile cf = parser.parse(path);
        classes.put(cf.thisClass, cf);
        return cf;
    }

    /**
     * Returns a loaded class by binary name, or {@code null} if not found
     * (also searches the class path).
     */
    public ClassFile getClass(String className) {
        if (classes.containsKey(className)) return classes.get(className);
        // Search class path
        String rel = className + ".class";
        for (Path cp : classPath) {
            Path file = cp.resolve(rel);
            if (Files.exists(file)) {
                try { return loadClass(file); } catch (IOException ignored) {}
            }
        }
        return null;
    }

    // ── Public execution API ─────────────────────────────────────────────────

    /** Runs the {@code main(String[])} method of the named class. */
    public void runMain(String className, String[] args) throws Exception {
        ClassFile cf = requireClass(className);
        ClassFile.MethodInfo main = cf.findMethod("main", "([Ljava/lang/String;)V");
        if (main == null) throw new RuntimeException("main method not found in " + className);
        Frame frame = new Frame(Math.max(main.getCode().maxLocals, 1));
        frame.setLocal(0, args);
        executeMethod(cf, main, frame);
    }

    /**
     * Invokes a static method and returns the result ({@code null} for void).
     *
     * @param className  binary class name
     * @param methodName method name
     * @param descriptor JVM descriptor, e.g. {@code "(II)I"}
     * @param args       arguments in order
     */
    public Object invokeStatic(String className, String methodName,
                                String descriptor, Object... args) throws Exception {
        ClassFile cf = requireClass(className);
        ClassFile.MethodInfo m = cf.findMethod(methodName, descriptor);
        if (m == null) throw new RuntimeException(
                "Method not found: " + className + "." + methodName + descriptor);
        return callMethod(cf, m, args);
    }

    // ── Internal execution ───────────────────────────────────────────────────

    private Object executeMethod(ClassFile cf, ClassFile.MethodInfo method, Frame frame)
            throws Exception {
        ClassFile.CodeAttribute code = method.getCode();
        if (code == null) return null;   // native / abstract stub
        return interpret(cf, code, frame);
    }

    /**
     * Main bytecode interpretation loop.
     *
     * <p>Branch offsets follow the JVM specification: they are signed 16-bit
     * values relative to the start of the branch instruction (the opcode byte).
     * At the top of each iteration {@code pc} points to the opcode; after the
     * {@code pc++} at the top of the loop body it points to the first operand.
     */
    private Object interpret(ClassFile cf, ClassFile.CodeAttribute codeAttr, Frame frame)
            throws Exception {
        final byte[] code = codeAttr.code;
        final ConstantPool cp = cf.constantPool;
        int pc = 0;

        while (pc < code.length) {
            final int opcodePC = pc;            // PC of this instruction (for branch arithmetic)
            int opcode = u8(code, pc++);

            switch (opcode) {

                // ── NOP ─────────────────────────────────────────────────────
                case Opcodes.NOP -> {}

                // ── Push constants ───────────────────────────────────────────
                case Opcodes.ACONST_NULL -> frame.push(null);
                case Opcodes.ICONST_M1   -> frame.pushInt(-1);
                case Opcodes.ICONST_0    -> frame.pushInt(0);
                case Opcodes.ICONST_1    -> frame.pushInt(1);
                case Opcodes.ICONST_2    -> frame.pushInt(2);
                case Opcodes.ICONST_3    -> frame.pushInt(3);
                case Opcodes.ICONST_4    -> frame.pushInt(4);
                case Opcodes.ICONST_5    -> frame.pushInt(5);
                case Opcodes.LCONST_0    -> frame.pushLong(0L);
                case Opcodes.LCONST_1    -> frame.pushLong(1L);
                case Opcodes.FCONST_0    -> frame.pushFloat(0.0f);
                case Opcodes.FCONST_1    -> frame.pushFloat(1.0f);
                case Opcodes.FCONST_2    -> frame.pushFloat(2.0f);
                case Opcodes.DCONST_0    -> frame.pushDouble(0.0);
                case Opcodes.DCONST_1    -> frame.pushDouble(1.0);

                case Opcodes.BIPUSH -> frame.pushInt(code[pc++]);           // signed byte
                case Opcodes.SIPUSH -> { frame.pushInt(s16(code, pc)); pc += 2; }
                case Opcodes.LDC    -> frame.push(cp.resolveLoadable(u8(code, pc++)));
                case Opcodes.LDC_W, Opcodes.LDC2_W -> {
                    frame.push(cp.resolveLoadable(u16(code, pc))); pc += 2;
                }

                // ── Loads ────────────────────────────────────────────────────
                case Opcodes.ILOAD -> frame.pushInt(frame.getLocalInt(u8(code, pc++)));
                case Opcodes.LLOAD -> frame.pushLong(frame.getLocalLong(u8(code, pc++)));
                case Opcodes.FLOAD -> frame.pushFloat(frame.getLocalFloat(u8(code, pc++)));
                case Opcodes.DLOAD -> frame.pushDouble(frame.getLocalDouble(u8(code, pc++)));
                case Opcodes.ALOAD -> frame.push(frame.getLocal(u8(code, pc++)));

                case Opcodes.ILOAD_0 -> frame.pushInt(frame.getLocalInt(0));
                case Opcodes.ILOAD_1 -> frame.pushInt(frame.getLocalInt(1));
                case Opcodes.ILOAD_2 -> frame.pushInt(frame.getLocalInt(2));
                case Opcodes.ILOAD_3 -> frame.pushInt(frame.getLocalInt(3));
                case Opcodes.LLOAD_0 -> frame.pushLong(frame.getLocalLong(0));
                case Opcodes.LLOAD_1 -> frame.pushLong(frame.getLocalLong(1));
                case Opcodes.LLOAD_2 -> frame.pushLong(frame.getLocalLong(2));
                case Opcodes.LLOAD_3 -> frame.pushLong(frame.getLocalLong(3));
                case Opcodes.FLOAD_0 -> frame.pushFloat(frame.getLocalFloat(0));
                case Opcodes.FLOAD_1 -> frame.pushFloat(frame.getLocalFloat(1));
                case Opcodes.FLOAD_2 -> frame.pushFloat(frame.getLocalFloat(2));
                case Opcodes.FLOAD_3 -> frame.pushFloat(frame.getLocalFloat(3));
                case Opcodes.DLOAD_0 -> frame.pushDouble(frame.getLocalDouble(0));
                case Opcodes.DLOAD_1 -> frame.pushDouble(frame.getLocalDouble(1));
                case Opcodes.DLOAD_2 -> frame.pushDouble(frame.getLocalDouble(2));
                case Opcodes.DLOAD_3 -> frame.pushDouble(frame.getLocalDouble(3));
                case Opcodes.ALOAD_0 -> frame.push(frame.getLocal(0));
                case Opcodes.ALOAD_1 -> frame.push(frame.getLocal(1));
                case Opcodes.ALOAD_2 -> frame.push(frame.getLocal(2));
                case Opcodes.ALOAD_3 -> frame.push(frame.getLocal(3));

                // ── Array loads ──────────────────────────────────────────────
                case Opcodes.IALOAD, Opcodes.BALOAD, Opcodes.CALOAD, Opcodes.SALOAD -> {
                    int idx = frame.popInt(); frame.pushInt(((int[]) frame.pop())[idx]);
                }
                case Opcodes.LALOAD -> {
                    int idx = frame.popInt(); frame.pushLong(((long[]) frame.pop())[idx]);
                }
                case Opcodes.FALOAD -> {
                    int idx = frame.popInt(); frame.pushFloat(((float[]) frame.pop())[idx]);
                }
                case Opcodes.DALOAD -> {
                    int idx = frame.popInt(); frame.pushDouble(((double[]) frame.pop())[idx]);
                }
                case Opcodes.AALOAD -> {
                    int idx = frame.popInt(); frame.push(((Object[]) frame.pop())[idx]);
                }

                // ── Stores ───────────────────────────────────────────────────
                case Opcodes.ISTORE -> { int i = u8(code,pc++); frame.setLocal(i, frame.popInt()); }
                case Opcodes.LSTORE -> {
                    int i = u8(code,pc++); frame.setLocal(i, frame.popLong());
                    if (i + 1 < codeAttr.maxLocals) frame.setLocal(i + 1, null);
                }
                case Opcodes.FSTORE -> { int i = u8(code,pc++); frame.setLocal(i, frame.popFloat()); }
                case Opcodes.DSTORE -> {
                    int i = u8(code,pc++); frame.setLocal(i, frame.popDouble());
                    if (i + 1 < codeAttr.maxLocals) frame.setLocal(i + 1, null);
                }
                case Opcodes.ASTORE -> { int i = u8(code,pc++); frame.setLocal(i, frame.pop()); }

                case Opcodes.ISTORE_0 -> frame.setLocal(0, frame.popInt());
                case Opcodes.ISTORE_1 -> frame.setLocal(1, frame.popInt());
                case Opcodes.ISTORE_2 -> frame.setLocal(2, frame.popInt());
                case Opcodes.ISTORE_3 -> frame.setLocal(3, frame.popInt());
                case Opcodes.LSTORE_0 -> { frame.setLocal(0, frame.popLong()); frame.setLocal(1, null); }
                case Opcodes.LSTORE_1 -> { frame.setLocal(1, frame.popLong()); frame.setLocal(2, null); }
                case Opcodes.LSTORE_2 -> { frame.setLocal(2, frame.popLong()); frame.setLocal(3, null); }
                case Opcodes.LSTORE_3 -> { frame.setLocal(3, frame.popLong()); frame.setLocal(4, null); }
                case Opcodes.FSTORE_0 -> frame.setLocal(0, frame.popFloat());
                case Opcodes.FSTORE_1 -> frame.setLocal(1, frame.popFloat());
                case Opcodes.FSTORE_2 -> frame.setLocal(2, frame.popFloat());
                case Opcodes.FSTORE_3 -> frame.setLocal(3, frame.popFloat());
                case Opcodes.DSTORE_0 -> { frame.setLocal(0, frame.popDouble()); frame.setLocal(1, null); }
                case Opcodes.DSTORE_1 -> { frame.setLocal(1, frame.popDouble()); frame.setLocal(2, null); }
                case Opcodes.DSTORE_2 -> { frame.setLocal(2, frame.popDouble()); frame.setLocal(3, null); }
                case Opcodes.DSTORE_3 -> { frame.setLocal(3, frame.popDouble()); frame.setLocal(4, null); }
                case Opcodes.ASTORE_0 -> frame.setLocal(0, frame.pop());
                case Opcodes.ASTORE_1 -> frame.setLocal(1, frame.pop());
                case Opcodes.ASTORE_2 -> frame.setLocal(2, frame.pop());
                case Opcodes.ASTORE_3 -> frame.setLocal(3, frame.pop());

                // ── Array stores ─────────────────────────────────────────────
                case Opcodes.IASTORE, Opcodes.BASTORE, Opcodes.CASTORE, Opcodes.SASTORE -> {
                    int v = frame.popInt(); int i = frame.popInt();
                    ((int[]) frame.pop())[i] = v;
                }
                case Opcodes.LASTORE -> {
                    long v = frame.popLong(); int i = frame.popInt();
                    ((long[]) frame.pop())[i] = v;
                }
                case Opcodes.FASTORE -> {
                    float v = frame.popFloat(); int i = frame.popInt();
                    ((float[]) frame.pop())[i] = v;
                }
                case Opcodes.DASTORE -> {
                    double v = frame.popDouble(); int i = frame.popInt();
                    ((double[]) frame.pop())[i] = v;
                }
                case Opcodes.AASTORE -> {
                    Object v = frame.pop(); int i = frame.popInt();
                    ((Object[]) frame.pop())[i] = v;
                }

                // ── Stack manipulation ───────────────────────────────────────
                case Opcodes.POP  -> frame.pop();
                case Opcodes.POP2 -> {
                    Object top = frame.pop();
                    if (!(top instanceof Long) && !(top instanceof Double)) frame.pop();
                }
                case Opcodes.DUP -> frame.push(frame.peek());
                case Opcodes.DUP_X1 -> {
                    Object v1 = frame.pop(), v2 = frame.pop();
                    frame.push(v1); frame.push(v2); frame.push(v1);
                }
                case Opcodes.DUP_X2 -> {
                    Object v1 = frame.pop(), v2 = frame.pop();
                    if (v2 instanceof Long || v2 instanceof Double) {
                        frame.push(v1); frame.push(v2); frame.push(v1);
                    } else {
                        Object v3 = frame.pop();
                        frame.push(v1); frame.push(v3); frame.push(v2); frame.push(v1);
                    }
                }
                case Opcodes.DUP2 -> {
                    Object v1 = frame.pop();
                    if (v1 instanceof Long || v1 instanceof Double) {
                        frame.push(v1); frame.push(v1);
                    } else {
                        Object v2 = frame.pop();
                        frame.push(v2); frame.push(v1); frame.push(v2); frame.push(v1);
                    }
                }
                case Opcodes.DUP2_X1 -> {
                    Object v1 = frame.pop(), v2 = frame.pop();
                    if (v1 instanceof Long || v1 instanceof Double) {
                        frame.push(v1); frame.push(v2); frame.push(v1);
                    } else {
                        Object v3 = frame.pop();
                        frame.push(v2); frame.push(v1);
                        frame.push(v3); frame.push(v2); frame.push(v1);
                    }
                }
                case Opcodes.DUP2_X2 -> {
                    // Simplified: assume all category 1
                    Object v1 = frame.pop(), v2 = frame.pop(),
                           v3 = frame.pop(), v4 = frame.pop();
                    frame.push(v2); frame.push(v1);
                    frame.push(v4); frame.push(v3); frame.push(v2); frame.push(v1);
                }
                case Opcodes.SWAP -> {
                    Object v1 = frame.pop(), v2 = frame.pop();
                    frame.push(v1); frame.push(v2);
                }

                // ── Arithmetic ───────────────────────────────────────────────
                case Opcodes.IADD -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a+b); }
                case Opcodes.LADD -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a+b); }
                case Opcodes.FADD -> { float b=frame.popFloat(),a=frame.popFloat(); frame.pushFloat(a+b); }
                case Opcodes.DADD -> { double b=frame.popDouble(),a=frame.popDouble(); frame.pushDouble(a+b); }
                case Opcodes.ISUB -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a-b); }
                case Opcodes.LSUB -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a-b); }
                case Opcodes.FSUB -> { float b=frame.popFloat(),a=frame.popFloat(); frame.pushFloat(a-b); }
                case Opcodes.DSUB -> { double b=frame.popDouble(),a=frame.popDouble(); frame.pushDouble(a-b); }
                case Opcodes.IMUL -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a*b); }
                case Opcodes.LMUL -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a*b); }
                case Opcodes.FMUL -> { float b=frame.popFloat(),a=frame.popFloat(); frame.pushFloat(a*b); }
                case Opcodes.DMUL -> { double b=frame.popDouble(),a=frame.popDouble(); frame.pushDouble(a*b); }
                case Opcodes.IDIV -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a/b); }
                case Opcodes.LDIV -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a/b); }
                case Opcodes.FDIV -> { float b=frame.popFloat(),a=frame.popFloat(); frame.pushFloat(a/b); }
                case Opcodes.DDIV -> { double b=frame.popDouble(),a=frame.popDouble(); frame.pushDouble(a/b); }
                case Opcodes.IREM -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a%b); }
                case Opcodes.LREM -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a%b); }
                case Opcodes.FREM -> { float b=frame.popFloat(),a=frame.popFloat(); frame.pushFloat(a%b); }
                case Opcodes.DREM -> { double b=frame.popDouble(),a=frame.popDouble(); frame.pushDouble(a%b); }
                case Opcodes.INEG -> frame.pushInt(-frame.popInt());
                case Opcodes.LNEG -> frame.pushLong(-frame.popLong());
                case Opcodes.FNEG -> frame.pushFloat(-frame.popFloat());
                case Opcodes.DNEG -> frame.pushDouble(-frame.popDouble());

                // ── Bitwise / shift ──────────────────────────────────────────
                case Opcodes.ISHL  -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a<<b); }
                case Opcodes.LSHL  -> { int b=frame.popInt(); long a=frame.popLong(); frame.pushLong(a<<b); }
                case Opcodes.ISHR  -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a>>b); }
                case Opcodes.LSHR  -> { int b=frame.popInt(); long a=frame.popLong(); frame.pushLong(a>>b); }
                case Opcodes.IUSHR -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a>>>b); }
                case Opcodes.LUSHR -> { int b=frame.popInt(); long a=frame.popLong(); frame.pushLong(a>>>b); }
                case Opcodes.IAND  -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a&b); }
                case Opcodes.LAND  -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a&b); }
                case Opcodes.IOR   -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a|b); }
                case Opcodes.LOR   -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a|b); }
                case Opcodes.IXOR  -> { int b=frame.popInt(),a=frame.popInt(); frame.pushInt(a^b); }
                case Opcodes.LXOR  -> { long b=frame.popLong(),a=frame.popLong(); frame.pushLong(a^b); }

                // ── IINC ─────────────────────────────────────────────────────
                case Opcodes.IINC -> {
                    int idx = u8(code, pc++);
                    int inc = code[pc++];   // signed byte
                    frame.setLocal(idx, frame.getLocalInt(idx) + inc);
                }

                // ── Type conversions ─────────────────────────────────────────
                case Opcodes.I2L  -> frame.pushLong((long)  frame.popInt());
                case Opcodes.I2F  -> frame.pushFloat((float) frame.popInt());
                case Opcodes.I2D  -> frame.pushDouble((double)frame.popInt());
                case Opcodes.L2I  -> frame.pushInt((int)   frame.popLong());
                case Opcodes.L2F  -> frame.pushFloat((float)frame.popLong());
                case Opcodes.L2D  -> frame.pushDouble((double)frame.popLong());
                case Opcodes.F2I  -> frame.pushInt((int)   frame.popFloat());
                case Opcodes.F2L  -> frame.pushLong((long) frame.popFloat());
                case Opcodes.F2D  -> frame.pushDouble((double)frame.popFloat());
                case Opcodes.D2I  -> frame.pushInt((int)   frame.popDouble());
                case Opcodes.D2L  -> frame.pushLong((long) frame.popDouble());
                case Opcodes.D2F  -> frame.pushFloat((float)frame.popDouble());
                case Opcodes.I2B  -> frame.pushInt((byte)  frame.popInt());
                case Opcodes.I2C  -> frame.pushInt((char)  frame.popInt());
                case Opcodes.I2S  -> frame.pushInt((short) frame.popInt());

                // ── Comparisons ──────────────────────────────────────────────
                case Opcodes.LCMP -> {
                    long b=frame.popLong(),a=frame.popLong();
                    frame.pushInt(Long.compare(a, b));
                }
                case Opcodes.FCMPL -> {
                    float b=frame.popFloat(),a=frame.popFloat();
                    frame.pushInt((Float.isNaN(a)||Float.isNaN(b)) ? -1 : Float.compare(a,b));
                }
                case Opcodes.FCMPG -> {
                    float b=frame.popFloat(),a=frame.popFloat();
                    frame.pushInt((Float.isNaN(a)||Float.isNaN(b)) ?  1 : Float.compare(a,b));
                }
                case Opcodes.DCMPL -> {
                    double b=frame.popDouble(),a=frame.popDouble();
                    frame.pushInt((Double.isNaN(a)||Double.isNaN(b)) ? -1 : Double.compare(a,b));
                }
                case Opcodes.DCMPG -> {
                    double b=frame.popDouble(),a=frame.popDouble();
                    frame.pushInt((Double.isNaN(a)||Double.isNaN(b)) ?  1 : Double.compare(a,b));
                }

                // ── Conditional branches ─────────────────────────────────────
                // offset is signed 16-bit, relative to the opcode's PC.
                case Opcodes.IFEQ -> { int off=s16(code,pc); pc+=2; if(frame.popInt()==0) pc=opcodePC+off; }
                case Opcodes.IFNE -> { int off=s16(code,pc); pc+=2; if(frame.popInt()!=0) pc=opcodePC+off; }
                case Opcodes.IFLT -> { int off=s16(code,pc); pc+=2; if(frame.popInt()< 0) pc=opcodePC+off; }
                case Opcodes.IFGE -> { int off=s16(code,pc); pc+=2; if(frame.popInt()>=0) pc=opcodePC+off; }
                case Opcodes.IFGT -> { int off=s16(code,pc); pc+=2; if(frame.popInt()> 0) pc=opcodePC+off; }
                case Opcodes.IFLE -> { int off=s16(code,pc); pc+=2; if(frame.popInt()<=0) pc=opcodePC+off; }

                case Opcodes.IF_ICMPEQ -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a==b) pc=opcodePC+off;
                }
                case Opcodes.IF_ICMPNE -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a!=b) pc=opcodePC+off;
                }
                case Opcodes.IF_ICMPLT -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a<b) pc=opcodePC+off;
                }
                case Opcodes.IF_ICMPGE -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a>=b) pc=opcodePC+off;
                }
                case Opcodes.IF_ICMPGT -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a>b) pc=opcodePC+off;
                }
                case Opcodes.IF_ICMPLE -> {
                    int off=s16(code,pc); pc+=2; int b=frame.popInt(),a=frame.popInt();
                    if(a<=b) pc=opcodePC+off;
                }
                case Opcodes.IF_ACMPEQ -> {
                    int off=s16(code,pc); pc+=2; Object b=frame.pop(),a=frame.pop();
                    if(a==b) pc=opcodePC+off;
                }
                case Opcodes.IF_ACMPNE -> {
                    int off=s16(code,pc); pc+=2; Object b=frame.pop(),a=frame.pop();
                    if(a!=b) pc=opcodePC+off;
                }
                case Opcodes.IFNULL    -> { int off=s16(code,pc); pc+=2; if(frame.pop()==null)  pc=opcodePC+off; }
                case Opcodes.IFNONNULL -> { int off=s16(code,pc); pc+=2; if(frame.pop()!=null)  pc=opcodePC+off; }

                // ── Unconditional jumps ──────────────────────────────────────
                case Opcodes.GOTO   -> { int off=s16(code,pc); pc=opcodePC+off; }
                case Opcodes.GOTO_W -> { int off=s32(code,pc); pc=opcodePC+off; }

                // ── Switch ───────────────────────────────────────────────────
                case Opcodes.TABLESWITCH -> {
                    while ((pc & 3) != 0) pc++;             // align to 4-byte boundary
                    int def  = s32(code, pc); pc += 4;
                    int low  = s32(code, pc); pc += 4;
                    int high = s32(code, pc); pc += 4;
                    int key  = frame.popInt();
                    int jump = (key < low || key > high)
                            ? def
                            : s32(code, pc + (key - low) * 4);
                    pc = opcodePC + jump;
                }
                case Opcodes.LOOKUPSWITCH -> {
                    while ((pc & 3) != 0) pc++;
                    int def    = s32(code, pc); pc += 4;
                    int npairs = s32(code, pc); pc += 4;
                    int key    = frame.popInt();
                    int jump   = def;
                    for (int i = 0; i < npairs; i++) {
                        int match = s32(code, pc); pc += 4;
                        int off   = s32(code, pc); pc += 4;
                        if (key == match) { jump = off; break; }
                    }
                    pc = opcodePC + jump;
                }

                // ── Returns ──────────────────────────────────────────────────
                case Opcodes.IRETURN -> { return frame.popInt(); }
                case Opcodes.LRETURN -> { return frame.popLong(); }
                case Opcodes.FRETURN -> { return frame.popFloat(); }
                case Opcodes.DRETURN -> { return frame.popDouble(); }
                case Opcodes.ARETURN -> { return frame.pop(); }
                case Opcodes.RETURN  -> { return null; }

                // ── Field access ─────────────────────────────────────────────
                case Opcodes.GETSTATIC -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    frame.push(getStaticField(r[0], r[1], r[2]));
                }
                case Opcodes.PUTSTATIC -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    setStaticField(r[0], r[1], frame.pop());
                }
                case Opcodes.GETFIELD -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    Object obj = frame.pop();
                    frame.push(getInstanceField(obj, r[1]));
                }
                case Opcodes.PUTFIELD -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    Object val = frame.pop(), obj = frame.pop();
                    setInstanceField(obj, r[1], val);
                }

                // ── Method invocations ───────────────────────────────────────
                case Opcodes.INVOKESTATIC -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    Object res = invokeStaticMethod(r[0], r[1], r[2], frame);
                    if (!returnsVoid(r[2])) frame.push(res);
                }
                case Opcodes.INVOKEVIRTUAL, Opcodes.INVOKEINTERFACE -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    if (opcode == Opcodes.INVOKEINTERFACE) pc += 2; // skip count + 0
                    Object res = invokeVirtualMethod(r[0], r[1], r[2], frame);
                    if (!returnsVoid(r[2])) frame.push(res);
                }
                case Opcodes.INVOKESPECIAL -> {
                    String[] r = cp.resolveMemberRef(u16(code, pc)); pc += 2;
                    Object res = invokeSpecialMethod(r[0], r[1], r[2], frame);
                    if (!returnsVoid(r[2])) frame.push(res);
                }
                case Opcodes.INVOKEDYNAMIC -> {
                    pc += 4; // skip cpIndex + 0 + 0
                    throw new UnsupportedOperationException("INVOKEDYNAMIC not supported");
                }

                // ── Object / array creation ──────────────────────────────────
                case Opcodes.NEW -> {
                    frame.push(createObject(cp.getClassName(u16(code, pc)))); pc += 2;
                }
                case Opcodes.NEWARRAY -> {
                    int atype = u8(code, pc++);
                    frame.push(newPrimitiveArray(atype, frame.popInt()));
                }
                case Opcodes.ANEWARRAY -> {
                    pc += 2; // skip CP index (component type)
                    frame.push(new Object[frame.popInt()]);
                }
                case Opcodes.MULTIANEWARRAY -> {
                    pc += 2; // skip CP index
                    int dims = u8(code, pc++);
                    int[] sizes = new int[dims];
                    for (int i = dims - 1; i >= 0; i--) sizes[i] = frame.popInt();
                    frame.push(multiNewArray(sizes, 0));
                }
                case Opcodes.ARRAYLENGTH ->
                    frame.pushInt(java.lang.reflect.Array.getLength(frame.pop()));

                // ── Type checks ──────────────────────────────────────────────
                case Opcodes.CHECKCAST -> {
                    pc += 2; // nano JVM: no-op (no runtime type enforcement)
                }
                case Opcodes.INSTANCEOF -> {
                    String target = cp.getClassName(u16(code, pc)); pc += 2;
                    frame.pushInt(isInstanceOf(frame.pop(), target) ? 1 : 0);
                }

                // ── Exceptions ───────────────────────────────────────────────
                case Opcodes.ATHROW -> throw new JvmException(frame.pop());

                // ── Monitors (no-op in nano JVM) ─────────────────────────────
                case Opcodes.MONITORENTER, Opcodes.MONITOREXIT -> frame.pop();

                // ── WIDE prefix ──────────────────────────────────────────────
                case Opcodes.WIDE -> pc = handleWide(code, pc, frame, codeAttr.maxLocals);

                // ── JSR / RET (legacy subroutines) ───────────────────────────
                case Opcodes.JSR -> {
                    int off = s16(code, pc); pc += 2;
                    frame.push(pc); // push return address
                    pc = opcodePC + off;
                }
                case Opcodes.JSR_W -> {
                    int off = s32(code, pc); pc += 4;
                    frame.push(pc);
                    pc = opcodePC + off;
                }
                case Opcodes.RET -> {
                    pc = (Integer) frame.getLocal(u8(code, pc++));
                }

                default -> throw new UnsupportedOperationException(
                        String.format("Unsupported opcode 0x%02X at pc=%d", opcode, opcodePC));
            }
        }
        return null;
    }

    // ── WIDE prefix handler ──────────────────────────────────────────────────

    private int handleWide(byte[] code, int pc, Frame frame, int maxLocals) {
        int wop = u8(code, pc++);
        int idx = u16(code, pc); pc += 2;
        switch (wop) {
            case Opcodes.ILOAD  -> frame.pushInt(frame.getLocalInt(idx));
            case Opcodes.LLOAD  -> frame.pushLong(frame.getLocalLong(idx));
            case Opcodes.FLOAD  -> frame.pushFloat(frame.getLocalFloat(idx));
            case Opcodes.DLOAD  -> frame.pushDouble(frame.getLocalDouble(idx));
            case Opcodes.ALOAD  -> frame.push(frame.getLocal(idx));
            case Opcodes.ISTORE -> frame.setLocal(idx, frame.popInt());
            case Opcodes.LSTORE -> {
                frame.setLocal(idx, frame.popLong());
                if (idx + 1 < maxLocals) frame.setLocal(idx + 1, null);
            }
            case Opcodes.FSTORE -> frame.setLocal(idx, frame.popFloat());
            case Opcodes.DSTORE -> {
                frame.setLocal(idx, frame.popDouble());
                if (idx + 1 < maxLocals) frame.setLocal(idx + 1, null);
            }
            case Opcodes.ASTORE -> frame.setLocal(idx, frame.pop());
            case Opcodes.IINC -> {
                int inc = (short) u16(code, pc); pc += 2;
                frame.setLocal(idx, frame.getLocalInt(idx) + inc);
            }
            default -> throw new UnsupportedOperationException(
                    "WIDE not supported for opcode 0x" + Integer.toHexString(wop));
        }
        return pc;
    }

    // ── Static field access ──────────────────────────────────────────────────

    private Object getStaticField(String className, String fieldName, String descriptor) {
        if ("java/lang/System".equals(className)) {
            if ("out".equals(fieldName)) return new NativePrintStream(output);
            if ("err".equals(fieldName)) return new NativePrintStream(System.err);
        }
        String key = className + "." + fieldName;
        return staticFields.getOrDefault(key, defaultValue(descriptor));
    }

    private void setStaticField(String className, String fieldName, Object value) {
        staticFields.put(className + "." + fieldName, value);
    }

    // ── Instance field access ────────────────────────────────────────────────

    private Object getInstanceField(Object obj, String fieldName) {
        if (obj instanceof JvmObject jo) return jo.getField(fieldName);
        throw new RuntimeException("getfield on non-JvmObject: " + obj);
    }

    private void setInstanceField(Object obj, String fieldName, Object value) {
        if (obj instanceof JvmObject jo) { jo.setField(fieldName, value); return; }
        throw new RuntimeException("putfield on non-JvmObject: " + obj);
    }

    // ── Object / array creation ───────────────────────────────────────────────

    private Object createObject(String className) {
        JvmObject obj = new JvmObject(className);
        if ("java/lang/StringBuilder".equals(className) ||
            "java/lang/StringBuffer".equals(className)) {
            obj.nativeObject = new StringBuilder();
        }
        return obj;
    }

    private Object newPrimitiveArray(int atype, int count) {
        return switch (atype) {
            case 4  -> new boolean[count];
            case 5  -> new char[count];
            case 6  -> new float[count];
            case 7  -> new double[count];
            case 8  -> new byte[count];
            case 9  -> new short[count];
            case 10 -> new int[count];
            case 11 -> new long[count];
            default -> throw new RuntimeException("Unknown array type: " + atype);
        };
    }

    private Object[] multiNewArray(int[] dims, int depth) {
        Object[] arr = new Object[dims[depth]];
        if (depth < dims.length - 1) {
            for (int i = 0; i < dims[depth]; i++) arr[i] = multiNewArray(dims, depth + 1);
        }
        return arr;
    }

    // ── Method invocations ───────────────────────────────────────────────────

    private Object invokeStaticMethod(String className, String methodName,
                                       String descriptor, Frame callerFrame) throws Exception {
        if (isNativeClass(className)) {
            Object[] args = popArgs(descriptor, false, callerFrame);
            return dispatchNativeStatic(className, methodName, descriptor, args);
        }
        Object[] args = popArgs(descriptor, false, callerFrame);
        ClassFile cf  = requireClass(className);
        ClassFile.MethodInfo m = findInHierarchy(cf, methodName, descriptor);
        if (m == null) throw new RuntimeException(
                "Static method not found: " + className + "." + methodName + descriptor);
        return callMethod(cf, m, args);
    }

    private Object invokeVirtualMethod(String className, String methodName,
                                        String descriptor, Frame callerFrame) throws Exception {
        // Pop args first, then receiver (they were pushed receiver-first onto stack)
        Object[] args         = popArgs(descriptor, false, callerFrame);
        Object   receiver     = callerFrame.pop();
        if (receiver == null) throw new NullPointerException(
                "Null pointer invoking " + methodName);

        String actualClass = classOf(receiver);
        if (isNativeClass(actualClass) || isNativeClass(className)) {
            return dispatchNativeVirtual(receiver, actualClass, methodName, descriptor, args);
        }

        ClassFile cf = getClass(actualClass);
        if (cf == null) cf = requireClass(className);
        ClassFile.MethodInfo m = findInHierarchy(cf, methodName, descriptor);
        if (m == null) throw new RuntimeException(
                "Virtual method not found: " + className + "." + methodName + descriptor);

        Object[] all = prepend(receiver, args);
        return callMethod(cf, m, all);
    }

    private Object invokeSpecialMethod(String className, String methodName,
                                        String descriptor, Frame callerFrame) throws Exception {
        Object[] args     = popArgs(descriptor, false, callerFrame);
        Object   receiver = callerFrame.pop();

        if ("<init>".equals(methodName)) {
            if (receiver instanceof JvmObject jo && isNativeClass(jo.className)) {
                return dispatchNativeInit(jo, descriptor, args);
            }
            // User-defined constructor
            ClassFile cf = getClass(className);
            if (cf != null) {
                ClassFile.MethodInfo m = findInHierarchy(cf, "<init>", descriptor);
                if (m != null) {
                    callMethod(cf, m, prepend(receiver, args));
                }
            }
            return null;
        }

        // Super calls and private calls
        ClassFile cf = getClass(className);
        if (cf == null) return null;
        ClassFile.MethodInfo m = findInHierarchy(cf, methodName, descriptor);
        if (m == null) return null;
        return callMethod(cf, m, prepend(receiver, args));
    }

    // ── Actual method execution ──────────────────────────────────────────────

    private Object callMethod(ClassFile cf, ClassFile.MethodInfo method,
                               Object[] args) throws Exception {
        ClassFile.CodeAttribute code = method.getCode();
        if (code == null) return null;

        Frame newFrame = new Frame(Math.max(code.maxLocals, args.length));
        int slot = 0;
        for (Object arg : args) {
            newFrame.setLocal(slot++, arg);
            if (arg instanceof Long || arg instanceof Double) slot++; // wide slot
        }
        return interpret(cf, code, newFrame);
    }

    private ClassFile.MethodInfo findInHierarchy(ClassFile cf, String name, String descriptor) {
        ClassFile cur = cf;
        while (cur != null) {
            ClassFile.MethodInfo m = cur.findMethod(name, descriptor);
            if (m != null) return m;
            if (cur.superClass == null) break;
            cur = getClass(cur.superClass);
        }
        return null;
    }

    // ── Native method dispatch ───────────────────────────────────────────────

    private boolean isNativeClass(String cn) {
        return cn != null && (cn.startsWith("java/") || cn.startsWith("javax/")
                || cn.startsWith("sun/") || cn.startsWith("com/sun/") || cn.startsWith("jdk/"));
    }

    private String classOf(Object obj) {
        if (obj instanceof JvmObject jo) return jo.className;
        if (obj instanceof String)        return "java/lang/String";
        if (obj instanceof Integer)       return "java/lang/Integer";
        if (obj instanceof Long)          return "java/lang/Long";
        if (obj instanceof Float)         return "java/lang/Float";
        if (obj instanceof Double)        return "java/lang/Double";
        if (obj instanceof Boolean)       return "java/lang/Boolean";
        if (obj instanceof NativePrintStream) return "java/io/PrintStream";
        return "java/lang/Object";
    }

    private Object dispatchNativeStatic(String className, String methodName,
                                         String descriptor, Object[] args) {
        return switch (className) {
            case "java/lang/Integer" -> switch (methodName) {
                case "parseInt"  -> Integer.parseInt((String) args[0]);
                case "valueOf"   -> args[0] instanceof Integer ? args[0]
                                 : Integer.parseInt(args[0].toString());
                case "toString"  -> Integer.toString(toInt(args[0]));
                case "toBinaryString" -> Integer.toBinaryString(toInt(args[0]));
                case "toHexString"    -> Integer.toHexString(toInt(args[0]));
                case "toOctalString"  -> Integer.toOctalString(toInt(args[0]));
                case "max"  -> Math.max(toInt(args[0]), toInt(args[1]));
                case "min"  -> Math.min(toInt(args[0]), toInt(args[1]));
                case "sum"  -> toInt(args[0]) + toInt(args[1]);
                case "compare" -> Integer.compare(toInt(args[0]), toInt(args[1]));
                default -> unsupportedNative(className, methodName, descriptor);
            };
            case "java/lang/Long" -> switch (methodName) {
                case "parseLong" -> Long.parseLong((String) args[0]);
                case "valueOf"   -> args[0] instanceof Long ? args[0]
                                 : Long.parseLong(args[0].toString());
                case "toString"  -> Long.toString((Long) args[0]);
                case "max"  -> Math.max((Long) args[0], (Long) args[1]);
                case "min"  -> Math.min((Long) args[0], (Long) args[1]);
                case "compare" -> Long.compare((Long) args[0], (Long) args[1]);
                default -> unsupportedNative(className, methodName, descriptor);
            };
            case "java/lang/Double" -> switch (methodName) {
                case "parseDouble" -> Double.parseDouble((String) args[0]);
                case "valueOf"     -> args[0] instanceof Double ? args[0]
                                   : Double.parseDouble(args[0].toString());
                case "toString"    -> Double.toString((Double) args[0]);
                case "isNaN"       -> Double.isNaN((Double) args[0]);
                case "isInfinite"  -> Double.isInfinite((Double) args[0]);
                default -> unsupportedNative(className, methodName, descriptor);
            };
            case "java/lang/Float" -> switch (methodName) {
                case "parseFloat" -> Float.parseFloat((String) args[0]);
                case "valueOf"    -> args[0] instanceof Float ? args[0]
                                  : Float.parseFloat(args[0].toString());
                default -> unsupportedNative(className, methodName, descriptor);
            };
            case "java/lang/String" -> switch (methodName) {
                case "valueOf" -> args[0] == null ? "null"
                               : (args[0] instanceof JvmObject jo ? jo.toString()
                               : args[0].toString());
                case "format"  -> String.format((String) args[0],
                               Arrays.copyOfRange(args, 1, args.length));
                default -> unsupportedNative(className, methodName, descriptor);
            };
            case "java/lang/Math" -> dispatchMath(methodName, args);
            case "java/lang/System" -> switch (methodName) {
                case "arraycopy" -> {
                    Object src = args[0]; int srcPos = toInt(args[1]);
                    Object dst = args[2]; int dstPos = toInt(args[3]);
                    int len = toInt(args[4]);
                    System.arraycopy(src, srcPos, dst, dstPos, len);
                    yield null;
                }
                case "currentTimeMillis" -> System.currentTimeMillis();
                case "nanoTime"          -> System.nanoTime();
                case "exit"              -> { System.exit(toInt(args[0])); yield null; }
                default -> unsupportedNative(className, methodName, descriptor);
            };
            default -> unsupportedNative(className, methodName, descriptor);
        };
    }

    private Object dispatchMath(String methodName, Object[] args) {
        return switch (methodName) {
            case "abs"    -> args[0] instanceof Long ? Math.abs((Long)   args[0])
                                                     : Math.abs(toDouble(args[0]));
            case "max"    -> args[0] instanceof Long ? Math.max((Long)args[0],(Long)args[1])
                                                     : Math.max(toDouble(args[0]),toDouble(args[1]));
            case "min"    -> args[0] instanceof Long ? Math.min((Long)args[0],(Long)args[1])
                                                     : Math.min(toDouble(args[0]),toDouble(args[1]));
            case "sqrt"   -> Math.sqrt(toDouble(args[0]));
            case "cbrt"   -> Math.cbrt(toDouble(args[0]));
            case "pow"    -> Math.pow(toDouble(args[0]), toDouble(args[1]));
            case "floor"  -> Math.floor(toDouble(args[0]));
            case "ceil"   -> Math.ceil(toDouble(args[0]));
            case "round"  -> Math.round(toDouble(args[0]));
            case "log"    -> Math.log(toDouble(args[0]));
            case "log10"  -> Math.log10(toDouble(args[0]));
            case "exp"    -> Math.exp(toDouble(args[0]));
            case "sin"    -> Math.sin(toDouble(args[0]));
            case "cos"    -> Math.cos(toDouble(args[0]));
            case "tan"    -> Math.tan(toDouble(args[0]));
            case "asin"   -> Math.asin(toDouble(args[0]));
            case "acos"   -> Math.acos(toDouble(args[0]));
            case "atan"   -> Math.atan(toDouble(args[0]));
            case "atan2"  -> Math.atan2(toDouble(args[0]),toDouble(args[1]));
            case "signum" -> Math.signum(toDouble(args[0]));
            case "PI"     -> Math.PI;
            case "E"      -> Math.E;
            default -> unsupportedNative("java/lang/Math", methodName, "");
        };
    }

    private Object dispatchNativeVirtual(Object receiver, String actualClass,
                                          String methodName, String descriptor, Object[] args) {
        // PrintStream
        if (receiver instanceof NativePrintStream ps) {
            return dispatchPrintStream(ps.stream, methodName, args);
        }

        // StringBuilder / StringBuffer
        if (receiver instanceof JvmObject jo &&
                ("java/lang/StringBuilder".equals(jo.className) ||
                 "java/lang/StringBuffer".equals(jo.className))) {
            return dispatchStringBuilder(jo, methodName, args);
        }

        // String
        if (receiver instanceof String s) return dispatchString(s, methodName, args);

        // Integer (boxed)
        if (receiver instanceof Integer i) {
            if ("intValue".equals(methodName))    return i;
            if ("longValue".equals(methodName))   return (long)(int) i;
            if ("doubleValue".equals(methodName)) return (double)(int) i;
            if ("toString".equals(methodName))    return Integer.toString(i);
            if ("compareTo".equals(methodName))   return i.compareTo((Integer) args[0]);
            if ("equals".equals(methodName))      return i.equals(args[0]);
            if ("hashCode".equals(methodName))    return i.hashCode();
        }
        if (receiver instanceof Long l) {
            if ("longValue".equals(methodName))   return l;
            if ("intValue".equals(methodName))    return (int)(long) l;
            if ("toString".equals(methodName))    return Long.toString(l);
        }
        if (receiver instanceof Double d) {
            if ("doubleValue".equals(methodName)) return d;
            if ("intValue".equals(methodName))    return (int)(double) d;
            if ("toString".equals(methodName))    return Double.toString(d);
            if ("isNaN".equals(methodName))       return d.isNaN();
        }

        // Object.toString / equals / hashCode fallback
        if ("toString".equals(methodName))   return receiver.toString();
        if ("hashCode".equals(methodName))   return receiver.hashCode();
        if ("equals".equals(methodName))     return receiver.equals(args[0]);
        if ("getClass".equals(methodName))   return new JvmObject("java/lang/Class");

        throw new UnsupportedOperationException(
                "Native virtual not supported: " + actualClass + "." + methodName + descriptor);
    }

    private Object dispatchPrintStream(PrintStream ps, String methodName, Object[] args) {
        boolean nl = "println".equals(methodName);
        if (!nl && !"print".equals(methodName)) {
            throw new UnsupportedOperationException("PrintStream." + methodName);
        }
        if (args.length == 0) {
            if (nl) ps.println();
            return null;
        }
        Object val = args[0];
        if (val instanceof JvmObject jo) val = jo.toString();
        if (nl) ps.println(val); else ps.print(val);
        return null;
    }

    private Object dispatchStringBuilder(JvmObject jo, String methodName, Object[] args) {
        StringBuilder sb = (StringBuilder) jo.nativeObject;
        return switch (methodName) {
            case "append" -> {
                Object v = args[0];
                if (v instanceof JvmObject jo2) v = jo2.toString();
                if (v == null) sb.append("null");
                else if (v instanceof Integer i)  sb.append((int)(int) i);
                else if (v instanceof Long l)      sb.append((long) l);
                else if (v instanceof Float f)     sb.append((float) f);
                else if (v instanceof Double d)    sb.append((double) d);
                else if (v instanceof Boolean b)   sb.append((boolean) b);
                else if (v instanceof Character c) sb.append((char) c);
                else                               sb.append(v.toString());
                yield jo; // returns 'this'
            }
            case "insert" -> {
                int idx = toInt(args[0]);
                Object v = args[1];
                sb.insert(idx, v == null ? "null" : v.toString());
                yield jo;
            }
            case "delete"  -> { sb.delete(toInt(args[0]), toInt(args[1])); yield jo; }
            case "replace" -> { sb.replace(toInt(args[0]), toInt(args[1]), (String)args[2]); yield jo; }
            case "reverse" -> { sb.reverse(); yield jo; }
            case "toString"  -> sb.toString();
            case "length"    -> sb.length();
            case "capacity"  -> sb.capacity();
            case "charAt"    -> (int) sb.charAt(toInt(args[0]));
            case "setLength" -> { sb.setLength(toInt(args[0])); yield null; }
            case "indexOf"   -> sb.indexOf((String) args[0]);
            case "substring" -> args.length == 1 ? sb.substring(toInt(args[0]))
                                                  : sb.substring(toInt(args[0]), toInt(args[1]));
            default -> throw new UnsupportedOperationException("StringBuilder." + methodName);
        };
    }

    private Object dispatchString(String s, String methodName, Object[] args) {
        return switch (methodName) {
            case "length"          -> s.length();
            case "isEmpty"         -> s.isEmpty();
            case "charAt"          -> (int) s.charAt(toInt(args[0]));
            case "indexOf"         -> args[0] instanceof String str
                                    ? s.indexOf(str) : s.indexOf(toInt(args[0]));
            case "lastIndexOf"     -> args[0] instanceof String str
                                    ? s.lastIndexOf(str) : s.lastIndexOf(toInt(args[0]));
            case "substring"       -> args.length == 1
                                    ? s.substring(toInt(args[0]))
                                    : s.substring(toInt(args[0]), toInt(args[1]));
            case "equals"          -> s.equals(args[0]);
            case "equalsIgnoreCase"-> s.equalsIgnoreCase((String) args[0]);
            case "startsWith"      -> s.startsWith((String) args[0]);
            case "endsWith"        -> s.endsWith((String) args[0]);
            case "contains"        -> s.contains((String) args[0]);
            case "trim"            -> s.trim();
            case "strip"           -> s.strip();
            case "toUpperCase"     -> s.toUpperCase();
            case "toLowerCase"     -> s.toLowerCase();
            case "replace"         -> args[0] instanceof String a
                                    ? s.replace(a, (String) args[1])
                                    : s.replace((char) toInt(args[0]), (char) toInt(args[1]));
            case "split"           -> s.split((String) args[0]);
            case "toCharArray"     -> { char[] ca = s.toCharArray(); int[] ia = new int[ca.length]; for (int i=0;i<ca.length;i++) ia[i]=ca[i]; yield ia; }
            case "intern"          -> s.intern();
            case "concat"          -> s.concat((String) args[0]);
            case "compareTo"       -> s.compareTo((String) args[0]);
            case "compareToIgnoreCase" -> s.compareToIgnoreCase((String) args[0]);
            case "toString"        -> s;
            case "hashCode"        -> s.hashCode();
            case "getBytes"        -> s.getBytes();
            case "valueOf"         -> s;
            default -> throw new UnsupportedOperationException("String." + methodName);
        };
    }

    private Object dispatchNativeInit(JvmObject jo, String descriptor, Object[] args) {
        if ("java/lang/StringBuilder".equals(jo.className) ||
            "java/lang/StringBuffer".equals(jo.className)) {
            if (args.length == 1 && args[0] instanceof String s) {
                ((StringBuilder) jo.nativeObject).append(s);
            } else if (args.length == 1) {
                ((StringBuilder) jo.nativeObject).ensureCapacity(toInt(args[0]));
            }
        }
        return null;
    }

    // ── Argument popping helpers ─────────────────────────────────────────────

    /**
     * Pops method arguments from the operand stack in the correct order.
     * If {@code includeReceiver=true}, also pops the receiver afterwards.
     */
    private Object[] popArgs(String descriptor, boolean includeReceiver, Frame frame) {
        String[] types   = parseArgTypes(descriptor);
        Object[] args    = new Object[types.length];
        // Stack is LIFO, so pop in reverse
        for (int i = types.length - 1; i >= 0; i--) {
            args[i] = frame.pop();
        }
        return args;
    }

    // ── Misc helpers ─────────────────────────────────────────────────────────

    private ClassFile requireClass(String className) {
        ClassFile cf = getClass(className);
        if (cf == null) throw new RuntimeException("Class not found: " + className);
        return cf;
    }

    private boolean returnsVoid(String descriptor) {
        return descriptor.endsWith(")V");
    }

    private boolean isInstanceOf(Object obj, String target) {
        if (obj == null) return false;
        String actual = classOf(obj);
        return actual.equals(target) || "java/lang/Object".equals(target);
    }

    private Object defaultValue(String descriptor) {
        if (descriptor.isEmpty()) return null;
        return switch (descriptor.charAt(0)) {
            case 'I', 'B', 'C', 'S', 'Z' -> 0;
            case 'J' -> 0L;
            case 'F' -> 0.0f;
            case 'D' -> 0.0;
            default  -> null;
        };
    }

    private int toInt(Object v) {
        if (v instanceof Integer i) return i;
        if (v instanceof Long l)    return (int)(long) l;
        if (v instanceof Byte b)    return b;
        if (v instanceof Short s)   return s;
        if (v instanceof Character c) return c;
        throw new RuntimeException("Cannot convert to int: " + v);
    }

    private double toDouble(Object v) {
        if (v instanceof Double d)  return d;
        if (v instanceof Float f)   return f;
        if (v instanceof Integer i) return i;
        if (v instanceof Long l)    return l;
        throw new RuntimeException("Cannot convert to double: " + v);
    }

    private Object[] prepend(Object head, Object[] tail) {
        Object[] result = new Object[tail.length + 1];
        result[0] = head;
        System.arraycopy(tail, 0, result, 1, tail.length);
        return result;
    }

    private Object unsupportedNative(String cls, String method, String desc) {
        throw new UnsupportedOperationException(
                "Native not supported: " + cls + "." + method + desc);
    }

    // ── Bytecode read helpers (unsigned / signed) ────────────────────────────

    private static int u8(byte[] code, int pc) {
        return Byte.toUnsignedInt(code[pc]);
    }

    private static int u16(byte[] code, int pc) {
        return (Byte.toUnsignedInt(code[pc]) << 8) | Byte.toUnsignedInt(code[pc + 1]);
    }

    private static int s16(byte[] code, int pc) {
        return (short) ((Byte.toUnsignedInt(code[pc]) << 8) | Byte.toUnsignedInt(code[pc + 1]));
    }

    private static int s32(byte[] code, int pc) {
        return (Byte.toUnsignedInt(code[pc])     << 24)
             | (Byte.toUnsignedInt(code[pc + 1]) << 16)
             | (Byte.toUnsignedInt(code[pc + 2]) <<  8)
             |  Byte.toUnsignedInt(code[pc + 3]);
    }

    // ── Descriptor parsing helpers ───────────────────────────────────────────

    /** Counts the number of parameters described by a method descriptor. */
    public static int countArgs(String descriptor) {
        return parseArgTypes(descriptor).length;
    }

    /** Returns the parameter type descriptors from a method descriptor. */
    public static String[] parseArgTypes(String descriptor) {
        List<String> types = new ArrayList<>();
        int i = 1; // skip '('
        while (i < descriptor.length() && descriptor.charAt(i) != ')') {
            int start = i;
            char c = descriptor.charAt(i);
            if (c == '[') {
                while (descriptor.charAt(i) == '[') i++;
                if (descriptor.charAt(i) == 'L') {
                    while (descriptor.charAt(i) != ';') i++;
                }
            } else if (c == 'L') {
                while (descriptor.charAt(i) != ';') i++;
            }
            i++;
            types.add(descriptor.substring(start, i));
        }
        return types.toArray(String[]::new);
    }

    // ── Inner types ──────────────────────────────────────────────────────────

    /** Wraps a PrintStream so it can be used as a JVM stack value. */
    static final class NativePrintStream {
        final PrintStream stream;
        NativePrintStream(PrintStream s) { this.stream = s; }
    }

    /** Wraps a JVM-thrown object so it can propagate as a Java exception. */
    public static final class JvmException extends RuntimeException {
        public final Object thrownObject;
        public JvmException(Object obj) {
            super(obj == null ? "null" : obj.toString());
            this.thrownObject = obj;
        }
    }
}
