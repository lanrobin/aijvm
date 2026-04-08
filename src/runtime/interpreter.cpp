#include "runtime/interpreter.h"
#include "utils/logger.h"

#include <format>

namespace aijvm::runtime {

void Interpreter::execute(JavaThread& thread) {
    while (auto* frame = thread.current_frame()) {
        if (!execute_instruction(thread, *frame)) {
            // Method returned — if stack is empty, execution is complete
            if (thread.stack_empty()) {
                return;
            }
            // Otherwise continue executing the caller's frame
        }
    }
}

bool Interpreter::execute_instruction(JavaThread& thread, Frame& frame) {
    std::uint8_t opcode = frame.read_u1();

    switch (opcode) {

    // ===== §6.5 nop =====
    case Opcode::NOP:
        break;

    // ===== §6.5 iconst_<i>: Push int constant =====
    // "The <i> int constant (-1, 0, 1, 2, 3, 4, or 5) is pushed onto
    //  the operand stack."
    case Opcode::ICONST_M1:
        frame.push_int(-1);
        break;
    case Opcode::ICONST_0:
        frame.push_int(0);
        break;
    case Opcode::ICONST_1:
        frame.push_int(1);
        break;
    case Opcode::ICONST_2:
        frame.push_int(2);
        break;
    case Opcode::ICONST_3:
        frame.push_int(3);
        break;
    case Opcode::ICONST_4:
        frame.push_int(4);
        break;
    case Opcode::ICONST_5:
        frame.push_int(5);
        break;

    // ===== §6.5 bipush: Push byte as int =====
    // "The immediate byte is sign-extended to an int value. That value is
    //  pushed onto the operand stack."
    case Opcode::BIPUSH: {
        auto byte_val = static_cast<std::int8_t>(frame.read_u1());
        frame.push_int(static_cast<std::int32_t>(byte_val));
        break;
    }

    // ===== §6.5 iload: Load int from local variable =====
    // "The index is an unsigned byte. The local variable at index must
    //  contain an int."
    case Opcode::ILOAD: {
        auto index = frame.read_u1();
        frame.push_int(frame.get_local_int(index));
        break;
    }

    // ===== §6.5 iload_<n>: Load int from local variable =====
    // "The <n> must be an index into the local variable array of the
    //  current frame. The local variable at <n> must contain an int."
    case Opcode::ILOAD_0:
        frame.push_int(frame.get_local_int(0));
        break;
    case Opcode::ILOAD_1:
        frame.push_int(frame.get_local_int(1));
        break;
    case Opcode::ILOAD_2:
        frame.push_int(frame.get_local_int(2));
        break;
    case Opcode::ILOAD_3:
        frame.push_int(frame.get_local_int(3));
        break;

    // ===== §6.5 istore: Store int into local variable =====
    // "The index is an unsigned byte. The value on the top of the operand
    //  stack must be of type int."
    case Opcode::ISTORE: {
        auto index = frame.read_u1();
        frame.set_local_int(index, frame.pop_int());
        break;
    }

    // ===== §6.5 istore_<n>: Store int into local variable =====
    // "The <n> must be an index into the local variable array of the
    //  current frame."
    case Opcode::ISTORE_0:
        frame.set_local_int(0, frame.pop_int());
        break;
    case Opcode::ISTORE_1:
        frame.set_local_int(1, frame.pop_int());
        break;
    case Opcode::ISTORE_2:
        frame.set_local_int(2, frame.pop_int());
        break;
    case Opcode::ISTORE_3:
        frame.set_local_int(3, frame.pop_int());
        break;

    // ===== §6.5 iadd: Add int =====
    // "Both value1 and value2 must be of type int. The values are popped from
    //  the operand stack. The int result is value1 + value2. The result is
    //  pushed onto the operand stack."
    // Note: "The result is the 32 low-order bits of the true mathematical
    //  result in a sufficiently wide two's-complement format."
    case Opcode::IADD: {
        std::int32_t value2 = frame.pop_int();
        std::int32_t value1 = frame.pop_int();
        frame.push_int(value1 + value2);
        break;
    }

    // ===== §6.5 ireturn: Return int from method =====
    // "The value must be of type int. It is popped from the operand stack of
    //  the current frame and pushed onto the operand stack of the frame of
    //  the invoker."
    case Opcode::IRETURN: {
        std::int32_t return_value = frame.pop_int();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) {
            caller->push_int(return_value);
        }
        // If no caller (last frame), return value is discarded
        return false;
    }

    // ===== §6.5 return: Return void from method =====
    // "Any values on the operand stack of the current frame are discarded.
    //  The interpreter then returns control to the invoker of the method,
    //  reinstating the frame of the invoker."
    case Opcode::RETURN:
        thread.pop_frame();
        return false;

    default:
        throw InterpreterError(std::format(
            "Unimplemented opcode: 0x{:02X} at PC={}",
            opcode, frame.pc() - 1));
    }

    return true;
}

} // namespace aijvm::runtime
