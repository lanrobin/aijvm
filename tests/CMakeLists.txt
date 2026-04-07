# tests/CMakeLists.txt

# Find the GoogleTest package (assumes it is installed in your WSL environment)
find_package(GTest REQUIRED)

# Create the test executable
add_executable(run_tests dummy_test.cpp)

# Link GoogleTest and its main function
target_link_libraries(run_tests GTest::gtest GTest::gtest_main)

# Register the test with CTest so `make test` or `ctest` works
add_test(NAME AIJVM_Tests COMMAND run_tests)