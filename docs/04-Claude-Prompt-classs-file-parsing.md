As this document is quit large, I recommand a new session for this task to avoid context overflow.
Please refer to JVM Spec [Chapter 4. The class File Format](./jvms26/jvm_spec_chapter_4_the_class_file_format.pdf) to implement a class Parser to parse java binary stream data to a structural ClassFile. 
Here are requirements:
1. Skip 4.8 Format Checking;
2. Skip 4.9 Constraints on Java Virtual Machine Code and its sub sections.
3. Skip 4.10 Verification of class Files and its sub sections.
4. Use the document provided structure name as the c++ record name, such as CONSTANT_Class_info.
5. If the structure shared similar data structure make them a common ancestor making it easy to manuplate in other code.
6. In java world, every .class file will be parse to a c++ class instance of ClassFile, no exception.
7. The ClassFile take a std::vector<std::uint8_t> as input and then parse it.
8. If you have some thing unsure, please ask me and I will provide farther guidance.