Please help to implement the class loader code according to [Chapter 5. Loading, Linking, and Initializing](./jvms26/jvm_spec_chapter_5_loading_linking_and_initializing.pdf), here are the guidances:
1. To simplify the impementation, we only support to categories class loader: System class loader is to read class from the java.base.jmod file form the folder specified with "--bj" parameter; Customer class loader is to read the class from folder speficied by "--cp" parameter;
2. To improve the performace, System class loader keep a handle to java.base.jmod as system may need to read multiple class from this jmod file.
3. The class name is canonicalized, such as "java/util/ArrayList", "HelloWorld", "javax/net/ssl/SSLContext".
4. When loading a class, first try the system class loader, if not found then try to load from customer class loader.
5. A succeeded loaded class will return an instance of c++ class ClassFile in [class_file.h](../include/classfile/class_file.h)