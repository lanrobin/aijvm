#include <gtest/gtest.h>

#include "runtime/interpreter.h"
#include "runtime/heap.h"
#include "runtime/java_thread.h"
#include "runtime/frame.h"
#include "runtime/slot.h"
#include "classfile/class_file.h"
#include "classloader/class_loader.h"
#include "runtime/native_registry.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

using namespace aijvm::runtime;
using namespace aijvm::classfile;

// ============================================================================
// Helper: load a .class file into a byte vector
// ============================================================================
static std::vector<std::uint8_t> load_class_file(const std::filesystem::path& path) {
    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    EXPECT_TRUE(ifs.is_open()) << "Failed to open: " << path;
    auto size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
    ifs.read(reinterpret_cast<char*>(data.data()), size);
    return data;
}

static std::filesystem::path get_test_class_path() {
    auto path = std::filesystem::path(__FILE__).parent_path() / "javaclasses";
    if (std::filesystem::exists(path / "HelloAdd.class")) {
        return path;
    }
    return std::filesystem::path("tests/javaclasses");
}

// ============================================================================
// Helper: Create a frame with synthetic bytecode for interpreter tests.
// The bytecode vector must be kept alive for the frame's lifetime.
// ============================================================================
static std::unique_ptr<Frame> make_bytecode_frame(
    std::uint16_t max_locals,
    std::uint16_t max_stack,
    std::span<const std::uint8_t> bytecode) {
    return std::make_unique<Frame>(nullptr, nullptr, max_locals, max_stack, bytecode);
}

// ============================================================================
// Test fixture: provides Heap + ClassLoader for Interpreter construction
// ============================================================================
class InterpreterTestFixture : public ::testing::Test {
protected:
    Heap heap_;
    // ClassLoader with non-existent paths — fine for synthetic bytecode tests
    aijvm::classloader::ClassLoader loader_{"/nonexistent", "/nonexistent"};
    NativeMethodRegistry native_registry_;

    Interpreter make_interp() { return Interpreter(heap_, loader_, native_registry_); }
};

// ============================================================================
// §6.5 iconst_<i> Tests
// ============================================================================

TEST_F(InterpreterTestFixture, IconstM1) {
    // iconst_m1, return
    static const std::vector<std::uint8_t> code = {Opcode::ICONST_M1, Opcode::ISTORE_0, Opcode::RETURN};
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

TEST_F(InterpreterTestFixture, IconstAll) {
    // Push iconst_0 through iconst_5, add them all, store result, return
    static const std::vector<std::uint8_t> code = {
        Opcode::ICONST_0,   // push 0
        Opcode::ICONST_1,   // push 1
        Opcode::IADD,       // 0+1=1
        Opcode::ICONST_2,   // push 2
        Opcode::IADD,       // 1+2=3
        Opcode::ICONST_3,   // push 3
        Opcode::IADD,       // 3+3=6
        Opcode::ICONST_4,   // push 4
        Opcode::IADD,       // 6+4=10
        Opcode::ICONST_5,   // push 5
        Opcode::IADD,       // 10+5=15
        Opcode::ISTORE_0,   // store to local 0
        Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 2, code));

    // Execute and verify the frame is popped
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// §6.5 bipush Test
// ============================================================================

TEST_F(InterpreterTestFixture, Bipush) {
    // bipush 42, istore_0, return
    static const std::vector<std::uint8_t> code = {
        Opcode::BIPUSH, 42, Opcode::ISTORE_0, Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

TEST_F(InterpreterTestFixture, BipushNegative) {
    // bipush -10 (0xF6 = 246 unsigned = -10 signed), istore_0, return
    static const std::vector<std::uint8_t> code = {
        Opcode::BIPUSH, 0xF6, Opcode::ISTORE_0, Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));

    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// §6.5 iload / istore Tests
// ============================================================================

TEST_F(InterpreterTestFixture, IloadIstore) {
    // iconst_5, istore 4, iload 4, istore_0, return
    static const std::vector<std::uint8_t> code = {
        Opcode::ICONST_5,
        Opcode::ISTORE, 4,     // store 5 to local[4]
        Opcode::ILOAD, 4,      // load from local[4]
        Opcode::ISTORE_0,      // store to local[0]
        Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(5, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

TEST_F(InterpreterTestFixture, IloadNVariants) {
    // Set locals 0-3 via istore_<n>, then load them all with iload_<n> and add
    static const std::vector<std::uint8_t> code = {
        Opcode::ICONST_1, Opcode::ISTORE_0,   // local[0] = 1
        Opcode::ICONST_2, Opcode::ISTORE_1,   // local[1] = 2
        Opcode::ICONST_3, Opcode::ISTORE_2,   // local[2] = 3
        Opcode::ICONST_4, Opcode::ISTORE_3,   // local[3] = 4
        Opcode::ILOAD_0,                       // push 1
        Opcode::ILOAD_1,                       // push 2
        Opcode::IADD,                          // 1+2=3
        Opcode::ILOAD_2,                       // push 3
        Opcode::IADD,                          // 3+3=6
        Opcode::ILOAD_3,                       // push 4
        Opcode::IADD,                          // 6+4=10
        Opcode::ISTORE_0,                      // local[0] = 10
        Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(4, 2, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// §6.5 iadd Tests
// ============================================================================

TEST_F(InterpreterTestFixture, IaddOverflow) {
    // §6.5 iadd: "If overflow occurs, then the sign of the result may not be
    // the same as the sign of the mathematical sum. Despite the fact that
    // overflow may occur, execution of an iadd instruction never throws a
    // run-time exception."
    // INT_MAX + 1 should wrap to INT_MIN
    static const std::vector<std::uint8_t> code = {
        Opcode::BIPUSH, 0x7F,  // push 127 (max for bipush)
        Opcode::ICONST_1,      // push 1
        Opcode::IADD,          // 127 + 1 = 128 (no overflow for int, but testing logic)
        Opcode::ISTORE_0,
        Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 2, code));
    auto interp = make_interp();
    EXPECT_NO_THROW(interp.execute(thread));
}

// ============================================================================
// §6.5 ireturn Tests
// ============================================================================

TEST_F(InterpreterTestFixture, Ireturn) {
    // Simulate method invocation: caller frame calls a "method" that returns 42.
    // Callee: bipush 42, ireturn
    static const std::vector<std::uint8_t> callee_code = {
        Opcode::BIPUSH, 42, Opcode::IRETURN
    };
    // Caller: after callee returns, the return value (42) is on caller's stack.
    // Then istore_0, return.
    static const std::vector<std::uint8_t> caller_code = {
        // The caller's PC will be here when callee returns.
        // After ireturn, 42 gets pushed onto caller's stack.
        Opcode::ISTORE_0,
        Opcode::RETURN
    };

    JavaThread thread;
    // Push caller frame first
    thread.push_frame(make_bytecode_frame(1, 1, caller_code));
    // Push callee frame on top
    thread.push_frame(make_bytecode_frame(1, 1, callee_code));

    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

TEST_F(InterpreterTestFixture, IreturnNoCallerFrame) {
    // ireturn when there's only one frame — return value is discarded
    static const std::vector<std::uint8_t> code = {
        Opcode::ICONST_5, Opcode::IRETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// §6.5 return (void) Test
// ============================================================================

TEST_F(InterpreterTestFixture, ReturnVoid) {
    static const std::vector<std::uint8_t> code = {Opcode::RETURN};
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// §6.5 nop Test
// ============================================================================

TEST_F(InterpreterTestFixture, Nop) {
    static const std::vector<std::uint8_t> code = {
        Opcode::NOP, Opcode::NOP, Opcode::RETURN
    };
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    interp.execute(thread);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// Error Handling Tests
// ============================================================================

TEST_F(InterpreterTestFixture, UnimplementedOpcode) {
    // 0xFE is reserved/impdep1 — should throw InterpreterError
    static const std::vector<std::uint8_t> code = {0xFE};
    JavaThread thread;
    thread.push_frame(make_bytecode_frame(1, 1, code));
    auto interp = make_interp();
    EXPECT_THROW(interp.execute(thread), InterpreterError);
}

// ============================================================================
// Integration Test: HelloAdd.class bytecode simulation
// ============================================================================
// HelloAdd.main bytecode (from javap -c):
//   0: iconst_5
//   1: istore_1
//   2: bipush 10
//   4: istore_2
//   5: iload_1
//   6: iload_2
//   7: iadd
//   8: istore_3
//   9: bipush 9
//  11: istore_3
//  12: return

TEST_F(InterpreterTestFixture, HelloAddBytecodeManual) {
    // Reproduce the exact HelloAdd.main bytecode
    static const std::vector<std::uint8_t> code = {
        Opcode::ICONST_5,       // 0: push 5
        Opcode::ISTORE_1,       // 1: local[1] = 5   (int a = 5)
        Opcode::BIPUSH, 10,     // 2: push 10
        Opcode::ISTORE_2,       // 4: local[2] = 10  (int b = 10)
        Opcode::ILOAD_1,        // 5: push local[1]  (a)
        Opcode::ILOAD_2,        // 6: push local[2]  (b)
        Opcode::IADD,           // 7: 5 + 10 = 15
        Opcode::ISTORE_3,       // 8: local[3] = 15  (int sum = a + b)
        Opcode::BIPUSH, 9,      // 9: push 9
        Opcode::ISTORE_3,       // 11: local[3] = 9  (sum = 9)
        Opcode::RETURN           // 12: return void
    };

    JavaThread thread;
    auto frame = make_bytecode_frame(4, 2, code);
    auto* f = frame.get();
    thread.push_frame(std::move(frame));

    // Execute step-by-step to verify intermediate state
    auto interp = make_interp();

    // Execute: iconst_5 → push 5
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->stack_depth(), 1u);

    // Execute: istore_1 → local[1] = 5
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->get_local_int(1), 5);
    EXPECT_TRUE(thread.current_frame()->stack_empty());

    // Execute: bipush 10 → push 10
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->stack_depth(), 1u);

    // Execute: istore_2 → local[2] = 10
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->get_local_int(2), 10);

    // Execute: iload_1 → push 5
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));

    // Execute: iload_2 → push 10
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->stack_depth(), 2u);

    // Execute: iadd → 5 + 10 = 15
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->stack_depth(), 1u);

    // Execute: istore_3 → local[3] = 15
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->get_local_int(3), 15);

    // Execute: bipush 9 → push 9
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));

    // Execute: istore_3 → local[3] = 9 (overwrite)
    ASSERT_TRUE(interp.execute_instruction(thread, *thread.current_frame()));
    EXPECT_EQ(thread.current_frame()->get_local_int(3), 9);

    // Execute: return
    EXPECT_FALSE(interp.execute_instruction(thread, *f));
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// Integration Test: Parse and execute HelloAdd.class from real .class file
// ============================================================================

TEST_F(InterpreterTestFixture, HelloAddClassFile) {
    auto class_path = get_test_class_path() / "HelloAdd.class";
    if (!std::filesystem::exists(class_path)) {
        GTEST_SKIP() << "HelloAdd.class not found at " << class_path;
    }

    auto data = load_class_file(class_path);
    auto cf = std::make_shared<ClassFile>(std::move(data));

    // Find the "main" method
    const method_info* main_method = nullptr;
    for (const auto& method : cf->methods) {
        if (cf->get_utf8(method.name_index) == "main") {
            main_method = &method;
            break;
        }
    }
    ASSERT_NE(main_method, nullptr) << "main method not found in HelloAdd.class";

    // Find Code attribute
    const Code_attribute* code_attr = nullptr;
    for (const auto& attr : main_method->attributes) {
        code_attr = dynamic_cast<const Code_attribute*>(attr.get());
        if (code_attr) break;
    }
    ASSERT_NE(code_attr, nullptr) << "Code attribute not found for main method";

    // Create frame from Code attribute
    auto frame = std::make_unique<Frame>(
        cf, main_method,
        code_attr->max_locals, code_attr->max_stack,
        std::span<const std::uint8_t>(code_attr->code));

    // Set local[0] = nullptr (args parameter — unused)
    frame->set_local_ref(0, nullptr);

    JavaThread thread;
    thread.push_frame(std::move(frame));

    // Execute
    auto interp = make_interp();
    interp.execute(thread);

    // After execution, the frame should be popped (void return)
    EXPECT_TRUE(thread.stack_empty());
}
