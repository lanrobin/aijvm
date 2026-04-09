We are now embarking on the Memory Management and Garbage Collection subsystem for AIJVM. Our goal is to implement a Semi-space Copying Garbage Collector (Cheney's Algorithm). 

To ensure stability, we will design the C++20 headers first. Please note that since Cheney's algorithm physically moves objects in memory, a "Stop-The-World" (STW) pause is strictly required.

Please provide the `.hpp` definitions for the following components, adhering to our `claude.md` contract:

1. **CLI Argument Update (`-Xmx`):**
   - We need to parse a `-Xmx` argument (e.g., `-Xmx64M`) during VM bootstrap to define the total heap size.

2. **The `Heap` and `ObjectHeader` Design:**
   - Define a basic `ObjectHeader` (or `KlassWord`). Crucially, for Cheney's algorithm, an object must be able to store a **"forwarding pointer"** when it is moved to the To-Space. Explain how you structure this header to minimize memory overhead (e.g., using pointer tagging or union).
   - Define the `Heap` class. It should allocate one large contiguous memory block based on `-Xmx`, and logically divide it into two equal halves (`FromSpace` and `ToSpace`). 
   - It needs an `ObjectReference allocate(size_t size)` method.

3. **The `GarbageCollector` (Cheney's Algorithm):**
   - Propose a `GarbageCollector` class.
   - It needs a method to trigger the collection: `void collect(std::vector<JavaThread*>& threads, ClassLoader& class_loader)`.
   - The parameters are our **GC Roots**: thread stacks (local variables) and class static fields. 
   - Define the helper methods for Cheney's algorithm: `copy_object` and the BFS scanning loops for pointers.

4. **Stop-The-World (STW) via Safe Points:**
   - Since we cannot force-suspend `std::thread`s safely in C++, we need a cooperative Safe Point mechanism.
   - Propose an update to our `ThreadManager` and `JavaThread` / `Interpreter` loop. Include a global `std::atomic<bool> gc_requested` flag and a synchronization primitive (like `std::barrier` or `std::condition_variable`) so all threads can park themselves when a GC is triggered, and resume when the GC finishes.

Following our rules, output ONLY the header definitions (`.hpp`) and brief architectural reasoning. Focus heavily on how the `ObjectHeader` accommodates the forwarding pointer, and how the cooperative STW handshake is synchronized. Do not write the full `.cpp` GC implementation yet.