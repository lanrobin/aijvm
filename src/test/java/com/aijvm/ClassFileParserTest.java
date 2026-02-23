package com.aijvm;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.*;
import java.net.URI;
import java.nio.file.*;
import java.util.*;
import javax.tools.*;

/**
 * Tests for {@link ClassFileParser}: verifies that the parser correctly reads
 * a compiled {@code .class} file and exposes its structure.
 */
class ClassFileParserTest {

    // ── Helpers ──────────────────────────────────────────────────────────────

    /** Compiles a Java source string and returns the {@code .class} bytes. */
    static byte[] compileToBytes(String className, String source) throws Exception {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        assertNotNull(compiler, "javac not available in this JRE");

        Path tmpDir = Files.createTempDirectory("aijvm-test-");
        try {
            Path srcFile = tmpDir.resolve(className + ".java");
            Files.writeString(srcFile, source);

            StandardJavaFileManager fm = compiler.getStandardFileManager(null, null, null);
            Iterable<? extends JavaFileObject> units =
                    fm.getJavaFileObjectsFromFiles(List.of(srcFile.toFile()));

            List<String> options = List.of("-d", tmpDir.toString(),
                    "--release", "11");  // target Java 11 bytecode
            JavaCompiler.CompilationTask task =
                    compiler.getTask(null, fm, null, options, null, units);
            assertTrue(task.call(), "Compilation failed for " + className);

            Path classFile = tmpDir.resolve(className + ".class");
            return Files.readAllBytes(classFile);
        } finally {
            deleteTree(tmpDir);
        }
    }

    private static void deleteTree(Path dir) throws IOException {
        if (!Files.exists(dir)) return;
        try (var walk = Files.walk(dir)) {
            walk.sorted(Comparator.reverseOrder())
                .map(Path::toFile)
                .forEach(File::delete);
        }
    }

    // ── Tests ─────────────────────────────────────────────────────────────────

    @Test
    void testMagicNumberRejected() {
        byte[] bad = new byte[]{0x00, 0x00, 0x00, 0x00};
        ClassFileParser parser = new ClassFileParser();
        assertThrows(IOException.class, () -> parser.parse(bad));
    }

    @Test
    void testSimpleClassParsed() throws Exception {
        String src = "public class SimpleClass { public static int answer() { return 42; } }";
        byte[] bytes = compileToBytes("SimpleClass", src);

        ClassFileParser parser = new ClassFileParser();
        ClassFile cf = parser.parse(bytes);

        assertEquals("SimpleClass", cf.thisClass);
        assertEquals("java/lang/Object", cf.superClass);
        assertFalse(cf.methods.isEmpty(), "Should have methods");
    }

    @Test
    void testConstantPoolHasUtf8() throws Exception {
        String src = "public class Utf8Test { }";
        byte[] bytes = compileToBytes("Utf8Test", src);

        ClassFile cf = new ClassFileParser().parse(bytes);
        assertNotNull(cf.constantPool);
        // Class name should be present somewhere in the constant pool
        boolean found = false;
        for (int i = 1; i < 500; i++) {
            Object entry = cf.constantPool.get(i);
            if (entry == null) break;
            if (entry instanceof ConstantPool.Utf8Entry u && "Utf8Test".equals(u.value())) {
                found = true;
                break;
            }
        }
        assertTrue(found, "Class name 'Utf8Test' not found in constant pool");
    }

    @Test
    void testMethodHasCodeAttribute() throws Exception {
        String src = "public class WithCode { public static void doNothing() { } }";
        byte[] bytes = compileToBytes("WithCode", src);

        ClassFile cf = new ClassFileParser().parse(bytes);
        ClassFile.MethodInfo m = cf.findMethodByName("doNothing");
        assertNotNull(m, "Method 'doNothing' not found");
        assertNotNull(m.getCode(), "Code attribute missing");
    }

    @Test
    void testFieldsAreParsed() throws Exception {
        String src = "public class FieldClass { public int x; public static String name; }";
        byte[] bytes = compileToBytes("FieldClass", src);

        ClassFile cf = new ClassFileParser().parse(bytes);
        assertEquals(2, cf.fields.size());
        assertTrue(cf.fields.stream().anyMatch(f -> "x".equals(f.name)));
        assertTrue(cf.fields.stream().anyMatch(f -> "name".equals(f.name)));
    }

    @Test
    void testVersionIsParsed() throws Exception {
        String src = "public class VersionTest { }";
        byte[] bytes = compileToBytes("VersionTest", src);

        ClassFile cf = new ClassFileParser().parse(bytes);
        // Java 11 = major version 55
        assertEquals(55, cf.majorVersion, "Expected Java 11 major version (55)");
    }
}
