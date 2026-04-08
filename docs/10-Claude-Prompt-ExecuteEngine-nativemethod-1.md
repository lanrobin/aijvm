We are now moving to fertize the Execution Engine subsystem of AIJVM. I need to design the core bytecode Interpreter to support invoke native method.

Based on the JVM Specification (SE 26) Chapter 6 (The Java Virtual Machine Instruction Set), please provide the C++20 header definitions for this subsystem.

Key technical requirements and design points:
1. **Make a unified entry:** Make a unified entry to all the native method invoking and then dispatch to diffirent implement by java class. For example, method java/lang/Object.getClass:()Ljava/lang/Class; will be dispatched to natives/java_lang_Object.cpp.
2. **Next step:** When you run the application, please help to implement the missing native methods until HelloWorld runs well.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) first. I want to review the API contract, the opcodes enum mapping, and the dispatch architecture before we write any `.cpp` logic. Please include brief comments citing the JVM Spec.

There is a java class [HelloWorld.class](../tests/javaclasses/HelloWorld.class) for testing.