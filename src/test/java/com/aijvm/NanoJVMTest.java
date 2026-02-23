package com.aijvm;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import javax.tools.*;

/**
 * Integration tests for {@link NanoJVM}.
 *
 * <p>Each test compiles a tiny Java source snippet, loads the resulting
 * {@code .class} file into the NanoJVM, and verifies the return value or
 * printed output.
 */
class NanoJVMTest {

    private NanoJVM jvm;
    private Path tmpDir;

    @BeforeEach
    void setup() throws IOException {
        tmpDir = Files.createTempDirectory("aijvm-test-");
        jvm = new NanoJVM(tmpDir);
    }

    // ── Test helpers ─────────────────────────────────────────────────────────

    /** Compiles {@code source} into {@code tmpDir} and loads it into the JVM. */
    ClassFile compile(String className, String source) throws Exception {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        assertNotNull(compiler, "javac not available");

        Path srcFile = tmpDir.resolve(className + ".java");
        Files.writeString(srcFile, source);

        StandardJavaFileManager fm = compiler.getStandardFileManager(null, null, null);
        Iterable<? extends JavaFileObject> units =
                fm.getJavaFileObjectsFromFiles(List.of(srcFile.toFile()));
        List<String> opts = List.of("-d", tmpDir.toString(), "-cp", tmpDir.toString(), "--release", "11");
        JavaCompiler.CompilationTask task =
                compiler.getTask(null, fm, null, opts, null, units);
        assertTrue(task.call(), "Compilation failed for " + className);
        fm.close();

        return jvm.loadClass(tmpDir.resolve(className + ".class"));
    }

    /** Runs a static method and returns the result. */
    Object run(String cls, String method, String descriptor, Object... args) throws Exception {
        return jvm.invokeStatic(cls, method, descriptor, args);
    }

    /** Captures printed output while running main. */
    String captureMain(String cls, String... args) throws Exception {
        ByteArrayOutputStream buf = new ByteArrayOutputStream();
        jvm.setOutput(new PrintStream(buf));
        jvm.runMain(cls, args);
        return buf.toString().trim();
    }

    // ── Arithmetic ────────────────────────────────────────────────────────────

    @Test
    void testIntegerAdd() throws Exception {
        compile("IntOps", """
                public class IntOps {
                    public static int add(int a, int b) { return a + b; }
                }
                """);
        assertEquals(7, run("IntOps", "add", "(II)I", 3, 4));
    }

    @Test
    void testIntegerSubtract() throws Exception {
        compile("IntOps2", """
                public class IntOps2 {
                    public static int sub(int a, int b) { return a - b; }
                }
                """);
        assertEquals(5, run("IntOps2", "sub", "(II)I", 9, 4));
    }

    @Test
    void testIntegerMultiply() throws Exception {
        compile("IntOps3", """
                public class IntOps3 {
                    public static int mul(int a, int b) { return a * b; }
                }
                """);
        assertEquals(12, run("IntOps3", "mul", "(II)I", 3, 4));
    }

    @Test
    void testIntegerDivide() throws Exception {
        compile("IntOps4", """
                public class IntOps4 {
                    public static int div(int a, int b) { return a / b; }
                }
                """);
        assertEquals(3, run("IntOps4", "div", "(II)I", 9, 3));
    }

    @Test
    void testIntegerRemainder() throws Exception {
        compile("IntOps5", """
                public class IntOps5 {
                    public static int rem(int a, int b) { return a % b; }
                }
                """);
        assertEquals(1, run("IntOps5", "rem", "(II)I", 10, 3));
    }

    // ── Recursion ─────────────────────────────────────────────────────────────

    @Test
    void testFactorial() throws Exception {
        compile("Factorial", """
                public class Factorial {
                    public static int factorial(int n) {
                        if (n <= 1) return 1;
                        return n * factorial(n - 1);
                    }
                }
                """);
        assertEquals(120, run("Factorial", "factorial", "(I)I", 5));
        assertEquals(1,   run("Factorial", "factorial", "(I)I", 0));
        assertEquals(1,   run("Factorial", "factorial", "(I)I", 1));
    }

    @Test
    void testFibonacci() throws Exception {
        compile("Fibonacci", """
                public class Fibonacci {
                    public static int fib(int n) {
                        if (n <= 1) return n;
                        return fib(n - 1) + fib(n - 2);
                    }
                }
                """);
        assertEquals(0,  run("Fibonacci", "fib", "(I)I", 0));
        assertEquals(1,  run("Fibonacci", "fib", "(I)I", 1));
        assertEquals(8,  run("Fibonacci", "fib", "(I)I", 6));
        assertEquals(55, run("Fibonacci", "fib", "(I)I", 10));
    }

    // ── Loops ─────────────────────────────────────────────────────────────────

    @Test
    void testForLoop() throws Exception {
        compile("SumLoop", """
                public class SumLoop {
                    public static int sum(int n) {
                        int result = 0;
                        for (int i = 1; i <= n; i++) result += i;
                        return result;
                    }
                }
                """);
        assertEquals(55, run("SumLoop", "sum", "(I)I", 10));
        assertEquals(0,  run("SumLoop", "sum", "(I)I", 0));
    }

    @Test
    void testWhileLoop() throws Exception {
        compile("WhileLoop", """
                public class WhileLoop {
                    public static int countDown(int n) {
                        int count = 0;
                        while (n > 0) { count++; n--; }
                        return count;
                    }
                }
                """);
        assertEquals(5, run("WhileLoop", "countDown", "(I)I", 5));
    }

    // ── Long arithmetic ───────────────────────────────────────────────────────

    @Test
    void testLongArithmetic() throws Exception {
        compile("LongOps", """
                public class LongOps {
                    public static long mul(long a, long b) { return a * b; }
                    public static long add(long a, long b) { return a + b; }
                }
                """);
        assertEquals(6000000000L, run("LongOps", "mul", "(JJ)J", 2000000000L, 3L));
        assertEquals(10_000_000_000L, run("LongOps", "add", "(JJ)J",
                5_000_000_000L, 5_000_000_000L));
    }

    // ── Double arithmetic ─────────────────────────────────────────────────────

    @Test
    void testDoubleArithmetic() throws Exception {
        compile("DoubleOps", """
                public class DoubleOps {
                    public static double add(double a, double b) { return a + b; }
                    public static double pi() { return Math.PI; }
                }
                """);
        assertEquals(3.14 + 2.72, (Double) run("DoubleOps", "add", "(DD)D", 3.14, 2.72), 1e-9);
    }

    // ── Conditional logic ─────────────────────────────────────────────────────

    @Test
    void testMax() throws Exception {
        compile("MaxTest", """
                public class MaxTest {
                    public static int max(int a, int b) { return a > b ? a : b; }
                }
                """);
        assertEquals(9, run("MaxTest", "max", "(II)I", 9, 3));
        assertEquals(5, run("MaxTest", "max", "(II)I", 2, 5));
    }

    @Test
    void testAbsoluteValue() throws Exception {
        compile("AbsTest", """
                public class AbsTest {
                    public static int abs(int x) { return x < 0 ? -x : x; }
                }
                """);
        assertEquals(5, run("AbsTest", "abs", "(I)I", -5));
        assertEquals(5, run("AbsTest", "abs", "(I)I",  5));
    }

    // ── Arrays ────────────────────────────────────────────────────────────────

    @Test
    void testIntArray() throws Exception {
        compile("ArrayOps", """
                public class ArrayOps {
                    public static int sumArray(int n) {
                        int[] arr = new int[n];
                        for (int i = 0; i < n; i++) arr[i] = i + 1;
                        int sum = 0;
                        for (int i = 0; i < n; i++) sum += arr[i];
                        return sum;
                    }
                }
                """);
        assertEquals(15, run("ArrayOps", "sumArray", "(I)I", 5));
    }

    // ── Objects ───────────────────────────────────────────────────────────────

    @Test
    void testObjectFields() throws Exception {
        compile("Point", """
                public class Point {
                    public int x;
                    public int y;
                    public Point(int x, int y) { this.x = x; this.y = y; }
                    public int distSquared() { return x * x + y * y; }
                }
                """);
        compile("PointTest", """
                public class PointTest {
                    public static int test() {
                        Point p = new Point(3, 4);
                        return p.distSquared();
                    }
                }
                """);
        assertEquals(25, run("PointTest", "test", "()I"));
    }

    // ── Static fields ─────────────────────────────────────────────────────────

    @Test
    void testStaticField() throws Exception {
        compile("Counter", """
                public class Counter {
                    public static int count = 0;
                    public static void increment() { count++; }
                    public static int getCount() { return count; }
                }
                """);
        run("Counter", "increment", "()V");
        run("Counter", "increment", "()V");
        run("Counter", "increment", "()V");
        assertEquals(3, run("Counter", "getCount", "()I"));
    }

    // ── String operations ─────────────────────────────────────────────────────

    @Test
    void testStringBuilderConcat() throws Exception {
        compile("SbTest", """
                public class SbTest {
                    public static String build() {
                        StringBuilder sb = new StringBuilder();
                        sb.append("Hello");
                        sb.append(", ");
                        sb.append("World");
                        sb.append("!");
                        return sb.toString();
                    }
                }
                """);
        assertEquals("Hello, World!", run("SbTest", "build", "()Ljava/lang/String;"));
    }

    // ── System.out.println ────────────────────────────────────────────────────

    @Test
    void testPrintln() throws Exception {
        compile("PrintTest", """
                public class PrintTest {
                    public static void main(String[] args) {
                        System.out.println("NanoJVM works!");
                        System.out.println(42);
                    }
                }
                """);
        String out = captureMain("PrintTest");
        assertTrue(out.contains("NanoJVM works!"));
        assertTrue(out.contains("42"));
    }

    // ── Bitwise operations ────────────────────────────────────────────────────

    @Test
    void testBitwiseOps() throws Exception {
        compile("BitwiseOps", """
                public class BitwiseOps {
                    public static int and(int a, int b) { return a & b; }
                    public static int or(int a, int b)  { return a | b; }
                    public static int xor(int a, int b) { return a ^ b; }
                    public static int shl(int a, int b) { return a << b; }
                    public static int shr(int a, int b) { return a >> b; }
                }
                """);
        assertEquals(0,  run("BitwiseOps", "and", "(II)I", 0b1010, 0b0101));
        assertEquals(15, run("BitwiseOps", "or",  "(II)I", 0b1010, 0b0101));
        assertEquals(15, run("BitwiseOps", "xor", "(II)I", 0b1010, 0b0101));
        assertEquals(8,  run("BitwiseOps", "shl", "(II)I", 1, 3));
        assertEquals(2,  run("BitwiseOps", "shr", "(II)I", 8, 2));
    }

    // ── Type conversions ──────────────────────────────────────────────────────

    @Test
    void testTypeConversions() throws Exception {
        compile("ConvTest", """
                public class ConvTest {
                    public static long intToLong(int x) { return (long) x; }
                    public static int  longToInt(long x) { return (int) x; }
                    public static double intToDouble(int x) { return (double) x; }
                }
                """);
        assertEquals(42L,  run("ConvTest", "intToLong",   "(I)J", 42));
        assertEquals(42,   run("ConvTest", "longToInt",   "(J)I", 42L));
        assertEquals(42.0, run("ConvTest", "intToDouble", "(I)D", 42));
    }

    // ── Descriptor parsing utility ────────────────────────────────────────────

    @Test
    void testParseArgTypes() {
        String[] t1 = NanoJVM.parseArgTypes("(II)I");
        assertArrayEquals(new String[]{"I", "I"}, t1);

        String[] t2 = NanoJVM.parseArgTypes("(Ljava/lang/String;I)V");
        assertArrayEquals(new String[]{"Ljava/lang/String;", "I"}, t2);

        String[] t3 = NanoJVM.parseArgTypes("()V");
        assertEquals(0, t3.length);

        String[] t4 = NanoJVM.parseArgTypes("([I)I");
        assertArrayEquals(new String[]{"[I"}, t4);
    }
}
