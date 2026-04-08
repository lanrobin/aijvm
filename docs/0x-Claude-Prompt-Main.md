1. Please try to add a static method test_read_class_from_jmod in main.cpp and following code to this method and call it from main.cpp, read from java.base.jmod from the --bj parameter folder and then read the content of classes/java/util/ArrayList.class and then try to parse this java file and pring all its parent class name and implemented interfaces names.

2. Please try to add a static method test_load_class in the main.cpp and try to load the java Main class specified by the c++ main paramter:
    a. load all its super class and implemented interfaces, recursively on both super class and interfaces.
    b. logging all the loaded class names.