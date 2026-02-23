package com.aijvm;

import java.nio.file.Paths;

/**
 * Command-line entry point for the NanoJVM.
 *
 * <p>Usage: {@code java -jar aijvm.jar <ClassName> [args...]}
 *
 * <p>The class is loaded from the current directory (or directories on
 * the {@code -cp} flag if extended in the future).
 */
public class Main {

    public static void main(String[] argv) throws Exception {
        if (argv.length == 0) {
            System.err.println("Usage: aijvm <ClassName> [args...]");
            System.exit(1);
        }

        String className = argv[0].replace('.', '/'); // accept both forms
        String[] progArgs = new String[argv.length - 1];
        System.arraycopy(argv, 1, progArgs, 0, progArgs.length);

        NanoJVM jvm = new NanoJVM(Paths.get("."));
        jvm.runMain(className, progArgs);
    }
}
