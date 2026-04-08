# tests/CMakeLists.txt

# Find the GoogleTest package (assumes it is installed in your WSL environment)
find_package(GTest REQUIRED)

# Create the test executable
add_executable(run_tests
    dummy_test.cpp
    command_line_parser_test.cpp
    jmod_reader_test.cpp
    class_file_parser_test.cpp
    file_reader_test.cpp
    class_loader_test.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/command_line_parser.cpp
    ${CMAKE_SOURCE_DIR}/src/classfile/jmod_reader.cpp
    ${CMAKE_SOURCE_DIR}/src/classfile/class_file.cpp
    ${CMAKE_SOURCE_DIR}/src/classloader/class_loader.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/file_reader.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/logger.cpp
)

# Link GoogleTest, spdlog, libzip, and its main function
target_link_libraries(run_tests GTest::gtest GTest::gtest_main spdlog::spdlog PkgConfig::LIBZIP)

# Register the test with CTest so `make test` or `ctest` works
add_test(NAME AIJVM_Tests COMMAND run_tests)