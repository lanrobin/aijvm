We are now moving to the Runtime Data Areas subsystem of AIJVM. I need to design the memory layout, specifically focusing on the PC Register, JVM Stack, and the Frame (which includes the Local Variable Array and the Operand Stack).

Based on the Java Virtual Machine Specification (SE 26), please provide the C++20 header definitions for this subsystem. 

Key technical requirements and design points:
1. **The Slot Design:** Define a `Slot` (or `JValue`) type to represent the entries in local variables and the operand stack. Since a slot must hold various types (int, float, reference, returnAddress) and types like long/double take two slots, please propose the best C++20 approach. You can use either `std::variant` (for modern C++ type safety) OR a 32-bit `union` / `uint32_t` wrapper (for strict JVM spec compliance and lower memory overhead). Choose the best one for an interpreter and briefly justify your architectural choice.
2. **The Frame:** Define a `Frame` class using C++ standard containers (e.g., `std::vector`) to simulate the Local Variable Array and Operand Stack. It must include type-safe `push/pop` methods for the stack and `get/set` methods for local variables.
3. **The Thread Context:** Define a `JavaThread` class that manages its own PC Register (program counter) and a JVM Stack (a stack of `Frame` pointers or objects).

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) first. I want to review the API contract, memory layout, and your justification for the `Slot` implementation before we write any `.cpp` logic. Please include brief comments citing the relevant sections of the JVM Spec (e.g., §2.5, §2.6).