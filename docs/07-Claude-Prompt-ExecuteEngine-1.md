We are now moving to the Execution Engine subsystem of AIJVM. I need to design the core bytecode Interpreter.

Based on the JVM Specification (SE 26) Chapter 6 (The Java Virtual Machine Instruction Set), please provide the C++20 header definitions for this subsystem.

Key technical requirements and design points:
1. **Dispatch Mechanism:** The core of the interpreter will be the bytecode dispatch loop. I need an efficient way to decode and execute opcodes. Please propose the C++ class structure for the `Interpreter`. I am weighing a standard massive `switch-case` against a Computed Goto approach (e.g., GCC/Clang `&&label` array). Please briefly justify your architectural choice considering our requirement for cross-platform CMake builds vs. interpreter performance.
2. **Strict Scope Limitation:** Do NOT implement all 200+ opcodes. For this initial phase, the interpreter should only be aware of and support these fundamental instructions to evaluate a simple arithmetic sequence: `iconst_1`, `iload`, `istore`, `iadd`, and `return`.
3. **Execution Context:** The `Interpreter` should likely have an `execute(JavaThread& thread)` or `execute(Frame& frame)` method. It needs to read the bytecode array safely (e.g., using `std::span`), increment the PC register, manipulate the previously defined Frame (Operand Stack / Local Variables), and execute the logic.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) first. I want to review the API contract, the opcodes enum mapping, and the dispatch architecture before we write any `.cpp` logic. Please include brief comments citing the JVM Spec.

There is a java class [HelloAdd.class](../tests/javaclasses/HelloAdd.class) for testing.