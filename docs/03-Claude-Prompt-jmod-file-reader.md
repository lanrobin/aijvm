To implement a light weight JVM, we have to leverage the existing openjdk jmod files as part of our runtime system, so we need to read the files inside a jmod file.
Please implement a component to read/list/search from a jmod file with following functions:
1. Open a jmod file as a standard zip file.
2. Provide a method to read a specific file and return its content.
3. Provide a method to list all the files in a folder, it should provide a parameter to control if list all the subfolders.
4. Provide a method to search if a file is in this jmod file. And optional folder related to root can be provided, if no, search from root.
5. Provide a method to extract all the files to a specific folder, the folder name MUST provided.

Here are simple spec for the jmod file:
A .jmod file is just a standard ZIP archive, and Header: JMOD files start with a 4-byte header: the letters 'J' 'M' (0x4A, 0x4D), followed by a major version byte (0x01) and a minor version byte (0x00). It has a standardized internal directory layout. This layout serves as your "specification":
bin/: Executable command-line tools.
classes/: Contains the .class files (this is what your ClassLoader will care about).
conf/: Configuration files exported by the module.
lib/: Native libraries (e.g., .so, .dylib, .dll) required by the module.
include/: C/C++ header files for native development (JNI).
legal/: License files.
man/: manual files.

Testing:
You can assume there is a jmod file /usr/lib/jvm/java-25-openjdk-amd64/jmods/java.base.jmod for testing.