Based on the previous implementation [11-Claude-Prompt-ExecuteEngine-class-init.md](./11-Claude-Prompt-ExecuteEngine-class-init.md), you put the class initialization processs the method Heap::init_system_classes().

I think it is better to put the intialization status in the class ClassFile itself, as customer provided class may also has static initializer, so we can call `<cinit>` when loading the class provided by customer.

Please help to change the implement to store the ClassInitState in the class ClassFile and invoke `<clinit>` when loading the class.

Aslo please create a java file with static block to test this function.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.