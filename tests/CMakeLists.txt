add_executable(aijvm_tests
    ClassFileTest.cpp
    ${CMAKE_SOURCE_DIR}/src/ClassFile.cpp
)

target_include_directories(aijvm_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
)

target_compile_definitions(aijvm_tests PRIVATE
    TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
)

target_link_libraries(aijvm_tests PRIVATE
    GTest::gtest_main
)

target_compile_options(aijvm_tests PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

include(GoogleTest)
gtest_discover_tests(aijvm_tests)
