We are now moving to fertize the Execution Engine subsystem of AIJVM. I need to design the core bytecode Interpreter. Based on the prerequirement [07-Claude-Prompt-ExecuteEngine-1.md](./07-Claude-Prompt-ExecuteEngine-1.md), you have implement partial of the opcode, this time please implement all the opcode.

Based on the JVM Specification (SE 26) Chapter 6 (The Java Virtual Machine Instruction Set), please provide the C++20 header definitions for this subsystem.

Key technical requirements and design points:
1. **Dispatch Mechanism:** The core of the interpreter will be the bytecode dispatch loop. I need an efficient way to decode and execute opcodes. Please propose the C++ class structure for the `Interpreter`. I am weighing a standard massive `switch-case` against a Computed Goto approach (e.g., GCC/Clang `&&label` array). Please briefly justify your architectural choice considering our requirement for cross-platform CMake builds vs. interpreter performance.
2. **Strict Scope Limitation:** Do implement all 200+ opcodes.
3. **Execution Context:** The `Interpreter` should likely have an `execute(JavaThread& thread)` or `execute(Frame& frame)` method. It needs to read the bytecode array safely (e.g., using `std::span`), increment the PC register, manipulate the previously defined Frame (Operand Stack / Local Variables), and execute the logic.
4. **HeapArea** Make an gc enable heap area with interface for different type of gc algorithms, currrently, please make a no-op gc firstly.
5. **Native method**. There is no native method provided yet, so raise NativeMethodNotFoundError when need to invoke a native method, we will provide them in future implements.
6. **Class loading**, intially, we load the classes with it super class and interfaces recursively. Now if there is class not being loaded, please on it on demand.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) first. I want to review the API contract, the opcodes enum mapping, and the dispatch architecture before we write any `.cpp` logic. Please include brief comments citing the JVM Spec.

There is a java class [HelloAdd.class](../tests/javaclasses/HelloAdd.class) for testing.