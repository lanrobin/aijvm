We need to complete the GC Root scanning phase in our `GarbageCollector`. Currently, the implementation only scans the `JavaThread` stacks. Since AIJVM does not support JNI, our second and final source of Strong GC Roots must be the static fields of all loaded classes.

Please provide the C++20 header updates and architectural design to properly trace static fields as GC Roots.

Key technical requirements and design points:

1. **ClassLoader Iteration:** The `GarbageCollector::collect` method needs access to the loaded classes. Propose an update to expose these (e.g., an iterator, a visitor pattern, or `std::vector<Klass*> get_all_loaded_classes()`) from the `ClassLoader` in a thread-safe manner during the STW pause.

2. **Klass and Static Field Type Mapping (Crucial):**
   A class stores its static variables (often as an array of `Slot`s or `JValue`s). The GC MUST NOT treat primitive types (like `int` or `double`) as pointers. 
   - How will the `Klass` structure identify which static fields are references? 
   - Propose a lightweight metadata mechanism (e.g., parsing field descriptors for `L` or `[` during class loading and caching their offsets/indices).
   - Define an interface for the GC to extract these, such as a `void iterate_static_reference_roots(std::function<void(ObjectReference**)> visitor)` method.

3. **GC Integration (Cheney's Algorithm):**
   Update the initial root scanning logic in the `GarbageCollector` header. Show how the extracted static `ObjectReference`s are added to the initial To-Space BFS queue alongside the thread stack roots.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. I want to review your mechanism for distinguishing references from primitives in static fields before we write any `.cpp` logic.