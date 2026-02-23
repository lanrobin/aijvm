# aijvm
I ask Claude and Gemini to write an JVM for me.

## Requirements

- CMake 3.20+
- A C++20-capable compiler (GCC 10+, Clang 10+, MSVC 19.29+)

## Build

```bash
cmake -S . -B build
cmake --build build
```

For a specific build type (e.g. Release):

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Run

```bash
# Linux / macOS
./build/bin/aijvm

# Windows
.\build\bin\Release\aijvm.exe
```
