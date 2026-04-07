cmake_minimum_required(VERSION 3.20)
project(AIJVM VERSION 0.1.0 LANGUAGES CXX)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific extensions for cross-platform compatibility

# Set strict compilation warnings
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Generate the executable
add_executable(aijvm ${SOURCES})

# Enable testing (GoogleTest is highly recommended for validating AI-generated code)
enable_testing()
add_subdirectory(tests) # Note: Requires a separate CMakeLists.txt inside the 'tests' directory