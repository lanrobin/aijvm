We are now implementing the foundation for Multithreading in AIJVM. Currently, our execution runs directly on the OS main thread. I want to refactor the architecture so that the C++ main thread only bootstraps the VM, and spawns a child C++ thread to act as the "Java Main Thread". The OS main thread should then wait for this Java thread to finish.

This is the first step toward our 1:1 threading model.

Based on our `claude.md` rules, please provide the C++20 header definitions for this refactoring.

Key technical requirements and design points:

1. **The `JavaThread` Class:**
   - Define a `JavaThread` class that encapsulates a C++20 `std::thread`.
   - It must hold its own execution context: a PC (Program Counter) register and a `std::vector` (or similar container) for the JVM Stack (`Frame`s).
   - It needs a state enum (e.g., `NEW`, `RUNNABLE`, `TERMINATED`).
   - Provide a `start()` method that kicks off the underlying `std::thread`, and a `join()` method for the OS main thread to wait on it.

2. **The `JvmLauncher` / `VM` Singleton:**
   - Propose a high-level bootstrapper class.
   - It should have an `init()` method (to initialize the Heap and ClassLoader) and a `run_main_class(std::string_view class_name)` method.
   - The `run_main_class` method will be responsible for creating the `JavaThread`, pushing the initial `Frame` for `public static void main(String[] args)`, starting the thread, and blocking via `join()`.

3. **Interpreter Context Adjustment:**
   - Ensure the `Interpreter::execute()` method is designed to take a `JavaThread&` (or a pointer to it) as its context, so it knows which thread's stack and PC it is currently mutating.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.