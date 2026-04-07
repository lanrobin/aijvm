# Project Context: AIJVM (C++20)

## 1. Project Overview
- **Goal:** Build a minimal Java Virtual Machine (JVM) from scratch.
- **Specification:** The Java® Virtual Machine Specification, Java SE 26 Edition. The is located in docs/jvms26
- **Environment:** Windows VSCode + WSL + CMake.
- **Target OS:** Cross-platform (Windows / Linux / MacOS).

## 2. Tech Stack & Coding Standards
- **Language:** Strictly C++20.
- **Cross-Platform Rule:** Always prioritize C++20 standard library features (e.g., `<filesystem>`, `<thread>`, `<chrono>`, `<mutex>`) over OS-specific APIs (like POSIX or WinAPI) to ensure cross-platform compilation via CMake.
- **Modern C++ Practices:** - Use `std::span` for safe memory/buffer access (especially for ClassFile parsing).
  - Use `std::variant` and `std::optional` where applicable.
  - Use `<format>` for string formatting instead of C-style `printf`.
  - Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) for ownership management; avoid raw pointers unless for non-owning observation.
  - Use `<bit>` and `std::endian::big` for handling Java class file byte-order conversions.

## 3. Core Architectural Modules
The JVM must implement the following core subsystems:
1.  **Class Loader:** Parse `.class` files (Magic Number, Constant Pool, Fields, Methods, Attributes).
2.  **Runtime Data Areas:** Implement PC, JVM Stack, Frames (Local Variables, Operand Stack), and Heap.
3.  **Execution Engine:** Interpreter-based bytecode dispatcher.
4.  **Memory Management:** A simple Semi-space Copying Garbage Collector (Swap GC).
5.  **Multithreading:** 1:1 threading model mapping Java threads to OS threads using `std::thread`.
6.  **Native Interface:** Minimal JNI simulation to support console execution (e.g., `System.out.println`).

## 4. AI Assistant Rules (How to interact with me)
As an AI assisting in this project, you must adhere to the following rules:
- **No Monolithic Code Dumps:** Do not write the entire JVM at once. Wait for my specific prompts for each sub-module.
- **Interface First (Contract Driven):** When I ask for a new feature, ALWAYS propose the C++ struct/class definitions (header design) first. Wait for my approval before implementing the `.cpp` logic.
- **Test-Driven Development (TDD):** When generating implementation code, ALWAYS generate corresponding GoogleTest (`gtest`) unit tests, particularly for memory operations and edge cases.
- **Cite the JVM Spec:** When implementing bytecode logic or class parsing, briefly reference the relevant section/concept from the JVM SE 26 Specification in your comments.
- **Contextual Awareness:** As an engineer working in AI infrastructure and machine learning systems (with experience in low-level programming like PyTorch/CUDA), I do not need basic C++ tutorials or elementary systems concepts explained. Skip generic greetings. Provide production-ready, highly optimized C++20 code with concise architectural explanations for your design choices.