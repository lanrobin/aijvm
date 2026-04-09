#include "runtime/interpreter.h"
#include "classfile/class_file.h"
#include "classloader/class_loader.h"
#include "utils/logger.h"

#include <bit>
#include <cmath>
#include <cstring>
#include <format>
#include <limits>

namespace aijvm::runtime {

using namespace classfile;

Interpreter::Interpreter(Heap& heap, classloader::ClassLoader& class_loader,
                         NativeMethodRegistry& native_registry,
                         SafepointManager& safepoint_mgr)
    : heap_(heap), class_loader_(class_loader), native_registry_(native_registry),
      safepoint_mgr_(safepoint_mgr) {}

void Interpreter::execute(JavaThread& thread) {
    safepoint_mgr_.register_thread();
    while (auto* frame = thread.current_frame()) {
        // Safepoint poll at each instruction boundary
        safepoint_mgr_.safepoint_poll();
        if (!execute_instruction(thread, *frame)) {
            if (thread.stack_empty()) {
                safepoint_mgr_.unregister_thread();
                return;
            }
        }
    }
}

bool Interpreter::execute_instruction(JavaThread& thread, Frame& frame) {
    std::uint32_t insn_pc = frame.pc();  // PC before reading opcode
    std::uint8_t opcode = frame.read_u1();

    switch (opcode) {

    // ========================================================================
    // §6.5 — Constants
    // ========================================================================

    case Opcode::NOP: break;

    case Opcode::ACONST_NULL:
        frame.push_ref(nullptr);
        break;

    case Opcode::ICONST_M1: frame.push_int(-1); break;
    case Opcode::ICONST_0:  frame.push_int(0);  break;
    case Opcode::ICONST_1:  frame.push_int(1);  break;
    case Opcode::ICONST_2:  frame.push_int(2);  break;
    case Opcode::ICONST_3:  frame.push_int(3);  break;
    case Opcode::ICONST_4:  frame.push_int(4);  break;
    case Opcode::ICONST_5:  frame.push_int(5);  break;

    case Opcode::LCONST_0:  frame.push_long(0LL); break;
    case Opcode::LCONST_1:  frame.push_long(1LL); break;

    case Opcode::FCONST_0:  frame.push_float(0.0f); break;
    case Opcode::FCONST_1:  frame.push_float(1.0f); break;
    case Opcode::FCONST_2:  frame.push_float(2.0f); break;

    case Opcode::DCONST_0:  frame.push_double(0.0); break;
    case Opcode::DCONST_1:  frame.push_double(1.0); break;

    case Opcode::BIPUSH: {
        auto val = static_cast<std::int8_t>(frame.read_u1());
        frame.push_int(static_cast<std::int32_t>(val));
        break;
    }

    case Opcode::SIPUSH: {
        auto val = frame.read_s2();
        frame.push_int(static_cast<std::int32_t>(val));
        break;
    }

    case Opcode::LDC: {
        auto index = frame.read_u1();
        do_ldc(frame, index);
        break;
    }

    case Opcode::LDC_W: {
        auto index = frame.read_u2();
        do_ldc(frame, index);
        break;
    }

    case Opcode::LDC2_W: {
        auto index = frame.read_u2();
        const auto& cf = frame.get_class_file();
        auto* entry = cf.constant_pool[index].get();
        if (auto* li = dynamic_cast<const CONSTANT_Long_info*>(entry)) {
            auto val = (static_cast<std::int64_t>(li->high_bytes) << 32) |
                       static_cast<std::int64_t>(li->low_bytes);
            frame.push_long(val);
        } else if (auto* di = dynamic_cast<const CONSTANT_Double_info*>(entry)) {
            auto bits = (static_cast<std::uint64_t>(di->high_bytes) << 32) |
                        static_cast<std::uint64_t>(di->low_bytes);
            double val;
            std::memcpy(&val, &bits, sizeof(double));
            frame.push_double(val);
        } else {
            throw InterpreterError(std::format(
                "ldc2_w: invalid constant pool entry at index {}", index));
        }
        break;
    }

    // ========================================================================
    // §6.5 — Loads
    // ========================================================================

    case Opcode::ILOAD:   frame.push_int(frame.get_local_int(frame.read_u1())); break;
    case Opcode::LLOAD:   frame.push_long(frame.get_local_long(frame.read_u1())); break;
    case Opcode::FLOAD:   frame.push_float(frame.get_local_float(frame.read_u1())); break;
    case Opcode::DLOAD:   frame.push_double(frame.get_local_double(frame.read_u1())); break;
    case Opcode::ALOAD:   frame.push_ref(frame.get_local_ref(frame.read_u1())); break;

    case Opcode::ILOAD_0: frame.push_int(frame.get_local_int(0)); break;
    case Opcode::ILOAD_1: frame.push_int(frame.get_local_int(1)); break;
    case Opcode::ILOAD_2: frame.push_int(frame.get_local_int(2)); break;
    case Opcode::ILOAD_3: frame.push_int(frame.get_local_int(3)); break;

    case Opcode::LLOAD_0: frame.push_long(frame.get_local_long(0)); break;
    case Opcode::LLOAD_1: frame.push_long(frame.get_local_long(1)); break;
    case Opcode::LLOAD_2: frame.push_long(frame.get_local_long(2)); break;
    case Opcode::LLOAD_3: frame.push_long(frame.get_local_long(3)); break;

    case Opcode::FLOAD_0: frame.push_float(frame.get_local_float(0)); break;
    case Opcode::FLOAD_1: frame.push_float(frame.get_local_float(1)); break;
    case Opcode::FLOAD_2: frame.push_float(frame.get_local_float(2)); break;
    case Opcode::FLOAD_3: frame.push_float(frame.get_local_float(3)); break;

    case Opcode::DLOAD_0: frame.push_double(frame.get_local_double(0)); break;
    case Opcode::DLOAD_1: frame.push_double(frame.get_local_double(1)); break;
    case Opcode::DLOAD_2: frame.push_double(frame.get_local_double(2)); break;
    case Opcode::DLOAD_3: frame.push_double(frame.get_local_double(3)); break;

    case Opcode::ALOAD_0: frame.push_ref(frame.get_local_ref(0)); break;
    case Opcode::ALOAD_1: frame.push_ref(frame.get_local_ref(1)); break;
    case Opcode::ALOAD_2: frame.push_ref(frame.get_local_ref(2)); break;
    case Opcode::ALOAD_3: frame.push_ref(frame.get_local_ref(3)); break;

    // §6.5 — Array loads
    case Opcode::IALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: iaload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_int(arr->array_int[static_cast<std::size_t>(idx)]);
        break;
    }
    case Opcode::LALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: laload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_long(arr->array_long[static_cast<std::size_t>(idx)]);
        break;
    }
    case Opcode::FALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: faload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_float(arr->array_float[static_cast<std::size_t>(idx)]);
        break;
    }
    case Opcode::DALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: daload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_double(arr->array_double[static_cast<std::size_t>(idx)]);
        break;
    }
    case Opcode::AALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: aaload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_ref(arr->array_ref[static_cast<std::size_t>(idx)]);
        break;
    }
    case Opcode::BALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: baload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_int(static_cast<std::int32_t>(arr->array_byte[static_cast<std::size_t>(idx)]));
        break;
    }
    case Opcode::CALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: caload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_int(static_cast<std::int32_t>(arr->array_char[static_cast<std::size_t>(idx)]));
        break;
    }
    case Opcode::SALOAD: {
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: saload");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        frame.push_int(static_cast<std::int32_t>(arr->array_short[static_cast<std::size_t>(idx)]));
        break;
    }

    // ========================================================================
    // §6.5 — Stores
    // ========================================================================

    case Opcode::ISTORE:   frame.set_local_int(frame.read_u1(), frame.pop_int()); break;
    case Opcode::LSTORE:   frame.set_local_long(frame.read_u1(), frame.pop_long()); break;
    case Opcode::FSTORE:   frame.set_local_float(frame.read_u1(), frame.pop_float()); break;
    case Opcode::DSTORE:   frame.set_local_double(frame.read_u1(), frame.pop_double()); break;
    case Opcode::ASTORE:   frame.set_local_ref(frame.read_u1(), frame.pop_ref()); break;

    case Opcode::ISTORE_0: frame.set_local_int(0, frame.pop_int()); break;
    case Opcode::ISTORE_1: frame.set_local_int(1, frame.pop_int()); break;
    case Opcode::ISTORE_2: frame.set_local_int(2, frame.pop_int()); break;
    case Opcode::ISTORE_3: frame.set_local_int(3, frame.pop_int()); break;

    case Opcode::LSTORE_0: frame.set_local_long(0, frame.pop_long()); break;
    case Opcode::LSTORE_1: frame.set_local_long(1, frame.pop_long()); break;
    case Opcode::LSTORE_2: frame.set_local_long(2, frame.pop_long()); break;
    case Opcode::LSTORE_3: frame.set_local_long(3, frame.pop_long()); break;

    case Opcode::FSTORE_0: frame.set_local_float(0, frame.pop_float()); break;
    case Opcode::FSTORE_1: frame.set_local_float(1, frame.pop_float()); break;
    case Opcode::FSTORE_2: frame.set_local_float(2, frame.pop_float()); break;
    case Opcode::FSTORE_3: frame.set_local_float(3, frame.pop_float()); break;

    case Opcode::DSTORE_0: frame.set_local_double(0, frame.pop_double()); break;
    case Opcode::DSTORE_1: frame.set_local_double(1, frame.pop_double()); break;
    case Opcode::DSTORE_2: frame.set_local_double(2, frame.pop_double()); break;
    case Opcode::DSTORE_3: frame.set_local_double(3, frame.pop_double()); break;

    case Opcode::ASTORE_0: frame.set_local_ref(0, frame.pop_ref()); break;
    case Opcode::ASTORE_1: frame.set_local_ref(1, frame.pop_ref()); break;
    case Opcode::ASTORE_2: frame.set_local_ref(2, frame.pop_ref()); break;
    case Opcode::ASTORE_3: frame.set_local_ref(3, frame.pop_ref()); break;

    // §6.5 — Array stores
    case Opcode::IASTORE: {
        auto val = frame.pop_int();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: iastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_int[static_cast<std::size_t>(idx)] = val;
        break;
    }
    case Opcode::LASTORE: {
        auto val = frame.pop_long();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: lastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_long[static_cast<std::size_t>(idx)] = val;
        break;
    }
    case Opcode::FASTORE: {
        auto val = frame.pop_float();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: fastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_float[static_cast<std::size_t>(idx)] = val;
        break;
    }
    case Opcode::DASTORE: {
        auto val = frame.pop_double();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: dastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_double[static_cast<std::size_t>(idx)] = val;
        break;
    }
    case Opcode::AASTORE: {
        auto* val = frame.pop_ref();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: aastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_ref[static_cast<std::size_t>(idx)] = val;
        break;
    }
    case Opcode::BASTORE: {
        auto val = frame.pop_int();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: bastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_byte[static_cast<std::size_t>(idx)] = static_cast<std::int8_t>(val);
        break;
    }
    case Opcode::CASTORE: {
        auto val = frame.pop_int();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: castore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_char[static_cast<std::size_t>(idx)] = static_cast<std::uint16_t>(val);
        break;
    }
    case Opcode::SASTORE: {
        auto val = frame.pop_int();
        auto idx = frame.pop_int();
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: sastore");
        if (idx < 0 || idx >= arr->array_length())
            throw InterpreterError(std::format("ArrayIndexOutOfBoundsException: {}", idx));
        arr->array_short[static_cast<std::size_t>(idx)] = static_cast<std::int16_t>(val);
        break;
    }

    // ========================================================================
    // §6.5 — Stack manipulation
    // ========================================================================

    case Opcode::POP:
        frame.pop_slot();
        break;

    case Opcode::POP2:
        frame.pop_slot();
        frame.pop_slot();
        break;

    case Opcode::DUP: {
        auto val = frame.peek_slot(0);
        frame.push_slot(val);
        break;
    }

    case Opcode::DUP_X1: {
        auto v1 = frame.pop_slot();
        auto v2 = frame.pop_slot();
        frame.push_slot(v1);
        frame.push_slot(v2);
        frame.push_slot(v1);
        break;
    }

    case Opcode::DUP_X2: {
        auto v1 = frame.pop_slot();
        auto v2 = frame.pop_slot();
        auto v3 = frame.pop_slot();
        frame.push_slot(v1);
        frame.push_slot(v3);
        frame.push_slot(v2);
        frame.push_slot(v1);
        break;
    }

    case Opcode::DUP2: {
        auto v1 = frame.peek_slot(0);
        auto v2 = frame.peek_slot(1);
        frame.push_slot(v2);
        frame.push_slot(v1);
        break;
    }

    case Opcode::DUP2_X1: {
        auto v1 = frame.pop_slot();
        auto v2 = frame.pop_slot();
        auto v3 = frame.pop_slot();
        frame.push_slot(v2);
        frame.push_slot(v1);
        frame.push_slot(v3);
        frame.push_slot(v2);
        frame.push_slot(v1);
        break;
    }

    case Opcode::DUP2_X2: {
        auto v1 = frame.pop_slot();
        auto v2 = frame.pop_slot();
        auto v3 = frame.pop_slot();
        auto v4 = frame.pop_slot();
        frame.push_slot(v2);
        frame.push_slot(v1);
        frame.push_slot(v4);
        frame.push_slot(v3);
        frame.push_slot(v2);
        frame.push_slot(v1);
        break;
    }

    case Opcode::SWAP: {
        auto v1 = frame.pop_slot();
        auto v2 = frame.pop_slot();
        frame.push_slot(v1);
        frame.push_slot(v2);
        break;
    }

    // ========================================================================
    // §6.5 — Math
    // ========================================================================

    // --- int arithmetic ---
    case Opcode::IADD: { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 + v2); break; }
    case Opcode::ISUB: { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 - v2); break; }
    case Opcode::IMUL: { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 * v2); break; }
    case Opcode::IDIV: {
        auto v2 = frame.pop_int();
        auto v1 = frame.pop_int();
        if (v2 == 0) throw InterpreterError("ArithmeticException: / by zero");
        frame.push_int(v1 / v2);
        break;
    }
    case Opcode::IREM: {
        auto v2 = frame.pop_int();
        auto v1 = frame.pop_int();
        if (v2 == 0) throw InterpreterError("ArithmeticException: / by zero");
        frame.push_int(v1 % v2);
        break;
    }
    case Opcode::INEG: { frame.push_int(-frame.pop_int()); break; }

    // --- long arithmetic ---
    case Opcode::LADD: { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 + v2); break; }
    case Opcode::LSUB: { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 - v2); break; }
    case Opcode::LMUL: { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 * v2); break; }
    case Opcode::LDIV: {
        auto v2 = frame.pop_long();
        auto v1 = frame.pop_long();
        if (v2 == 0) throw InterpreterError("ArithmeticException: / by zero");
        frame.push_long(v1 / v2);
        break;
    }
    case Opcode::LREM: {
        auto v2 = frame.pop_long();
        auto v1 = frame.pop_long();
        if (v2 == 0) throw InterpreterError("ArithmeticException: / by zero");
        frame.push_long(v1 % v2);
        break;
    }
    case Opcode::LNEG: { frame.push_long(-frame.pop_long()); break; }

    // --- float arithmetic ---
    case Opcode::FADD: { auto v2 = frame.pop_float(); auto v1 = frame.pop_float(); frame.push_float(v1 + v2); break; }
    case Opcode::FSUB: { auto v2 = frame.pop_float(); auto v1 = frame.pop_float(); frame.push_float(v1 - v2); break; }
    case Opcode::FMUL: { auto v2 = frame.pop_float(); auto v1 = frame.pop_float(); frame.push_float(v1 * v2); break; }
    case Opcode::FDIV: { auto v2 = frame.pop_float(); auto v1 = frame.pop_float(); frame.push_float(v1 / v2); break; }
    case Opcode::FREM: { auto v2 = frame.pop_float(); auto v1 = frame.pop_float(); frame.push_float(std::fmod(v1, v2)); break; }
    case Opcode::FNEG: { frame.push_float(-frame.pop_float()); break; }

    // --- double arithmetic ---
    case Opcode::DADD: { auto v2 = frame.pop_double(); auto v1 = frame.pop_double(); frame.push_double(v1 + v2); break; }
    case Opcode::DSUB: { auto v2 = frame.pop_double(); auto v1 = frame.pop_double(); frame.push_double(v1 - v2); break; }
    case Opcode::DMUL: { auto v2 = frame.pop_double(); auto v1 = frame.pop_double(); frame.push_double(v1 * v2); break; }
    case Opcode::DDIV: { auto v2 = frame.pop_double(); auto v1 = frame.pop_double(); frame.push_double(v1 / v2); break; }
    case Opcode::DREM: { auto v2 = frame.pop_double(); auto v1 = frame.pop_double(); frame.push_double(std::fmod(v1, v2)); break; }
    case Opcode::DNEG: { frame.push_double(-frame.pop_double()); break; }

    // --- shifts & bitwise (int) ---
    case Opcode::ISHL:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 << (v2 & 0x1F)); break; }
    case Opcode::ISHR:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 >> (v2 & 0x1F)); break; }
    case Opcode::IUSHR: {
        auto v2 = frame.pop_int();
        auto v1 = frame.pop_int();
        frame.push_int(static_cast<std::int32_t>(
            static_cast<std::uint32_t>(v1) >> (v2 & 0x1F)));
        break;
    }
    case Opcode::IAND:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 & v2); break; }
    case Opcode::IOR:   { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 | v2); break; }
    case Opcode::IXOR:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); frame.push_int(v1 ^ v2); break; }

    // --- shifts & bitwise (long) ---
    case Opcode::LSHL:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_long(); frame.push_long(v1 << (v2 & 0x3F)); break; }
    case Opcode::LSHR:  { auto v2 = frame.pop_int(); auto v1 = frame.pop_long(); frame.push_long(v1 >> (v2 & 0x3F)); break; }
    case Opcode::LUSHR: {
        auto v2 = frame.pop_int();
        auto v1 = frame.pop_long();
        frame.push_long(static_cast<std::int64_t>(
            static_cast<std::uint64_t>(v1) >> (v2 & 0x3F)));
        break;
    }
    case Opcode::LAND:  { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 & v2); break; }
    case Opcode::LOR:   { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 | v2); break; }
    case Opcode::LXOR:  { auto v2 = frame.pop_long(); auto v1 = frame.pop_long(); frame.push_long(v1 ^ v2); break; }

    // §6.5 iinc — increment local variable by constant
    case Opcode::IINC: {
        auto index = frame.read_u1();
        auto delta = static_cast<std::int8_t>(frame.read_u1());
        frame.set_local_int(index, frame.get_local_int(index) + delta);
        break;
    }

    // ========================================================================
    // §6.5 — Conversions
    // ========================================================================

    case Opcode::I2L: frame.push_long(static_cast<std::int64_t>(frame.pop_int())); break;
    case Opcode::I2F: frame.push_float(static_cast<float>(frame.pop_int())); break;
    case Opcode::I2D: frame.push_double(static_cast<double>(frame.pop_int())); break;
    case Opcode::L2I: frame.push_int(static_cast<std::int32_t>(frame.pop_long())); break;
    case Opcode::L2F: frame.push_float(static_cast<float>(frame.pop_long())); break;
    case Opcode::L2D: frame.push_double(static_cast<double>(frame.pop_long())); break;
    case Opcode::F2I: {
        float v = frame.pop_float();
        std::int32_t r;
        if (std::isnan(v)) r = 0;
        else if (v >= static_cast<float>(std::numeric_limits<std::int32_t>::max())) r = std::numeric_limits<std::int32_t>::max();
        else if (v <= static_cast<float>(std::numeric_limits<std::int32_t>::min())) r = std::numeric_limits<std::int32_t>::min();
        else r = static_cast<std::int32_t>(v);
        frame.push_int(r);
        break;
    }
    case Opcode::F2L: {
        float v = frame.pop_float();
        std::int64_t r;
        if (std::isnan(v)) r = 0;
        else if (v >= static_cast<float>(std::numeric_limits<std::int64_t>::max())) r = std::numeric_limits<std::int64_t>::max();
        else if (v <= static_cast<float>(std::numeric_limits<std::int64_t>::min())) r = std::numeric_limits<std::int64_t>::min();
        else r = static_cast<std::int64_t>(v);
        frame.push_long(r);
        break;
    }
    case Opcode::F2D: frame.push_double(static_cast<double>(frame.pop_float())); break;
    case Opcode::D2I: {
        double v = frame.pop_double();
        std::int32_t r;
        if (std::isnan(v)) r = 0;
        else if (v >= static_cast<double>(std::numeric_limits<std::int32_t>::max())) r = std::numeric_limits<std::int32_t>::max();
        else if (v <= static_cast<double>(std::numeric_limits<std::int32_t>::min())) r = std::numeric_limits<std::int32_t>::min();
        else r = static_cast<std::int32_t>(v);
        frame.push_int(r);
        break;
    }
    case Opcode::D2L: {
        double v = frame.pop_double();
        std::int64_t r;
        if (std::isnan(v)) r = 0;
        else if (v >= static_cast<double>(std::numeric_limits<std::int64_t>::max())) r = std::numeric_limits<std::int64_t>::max();
        else if (v <= static_cast<double>(std::numeric_limits<std::int64_t>::min())) r = std::numeric_limits<std::int64_t>::min();
        else r = static_cast<std::int64_t>(v);
        frame.push_long(r);
        break;
    }
    case Opcode::D2F: frame.push_float(static_cast<float>(frame.pop_double())); break;
    case Opcode::I2B: frame.push_int(static_cast<std::int32_t>(static_cast<std::int8_t>(frame.pop_int()))); break;
    case Opcode::I2C: frame.push_int(static_cast<std::int32_t>(static_cast<std::uint16_t>(frame.pop_int()))); break;
    case Opcode::I2S: frame.push_int(static_cast<std::int32_t>(static_cast<std::int16_t>(frame.pop_int()))); break;

    // ========================================================================
    // §6.5 — Comparisons
    // ========================================================================

    case Opcode::LCMP: {
        auto v2 = frame.pop_long();
        auto v1 = frame.pop_long();
        frame.push_int(v1 > v2 ? 1 : (v1 < v2 ? -1 : 0));
        break;
    }
    case Opcode::FCMPL: {
        auto v2 = frame.pop_float();
        auto v1 = frame.pop_float();
        if (std::isnan(v1) || std::isnan(v2)) frame.push_int(-1);
        else frame.push_int(v1 > v2 ? 1 : (v1 < v2 ? -1 : 0));
        break;
    }
    case Opcode::FCMPG: {
        auto v2 = frame.pop_float();
        auto v1 = frame.pop_float();
        if (std::isnan(v1) || std::isnan(v2)) frame.push_int(1);
        else frame.push_int(v1 > v2 ? 1 : (v1 < v2 ? -1 : 0));
        break;
    }
    case Opcode::DCMPL: {
        auto v2 = frame.pop_double();
        auto v1 = frame.pop_double();
        if (std::isnan(v1) || std::isnan(v2)) frame.push_int(-1);
        else frame.push_int(v1 > v2 ? 1 : (v1 < v2 ? -1 : 0));
        break;
    }
    case Opcode::DCMPG: {
        auto v2 = frame.pop_double();
        auto v1 = frame.pop_double();
        if (std::isnan(v1) || std::isnan(v2)) frame.push_int(1);
        else frame.push_int(v1 > v2 ? 1 : (v1 < v2 ? -1 : 0));
        break;
    }

    // --- if<cond> — branch if int compared with zero ---
    case Opcode::IFEQ: { auto off = frame.read_s2(); if (frame.pop_int() == 0) frame.set_pc(insn_pc + off); break; }
    case Opcode::IFNE: { auto off = frame.read_s2(); if (frame.pop_int() != 0) frame.set_pc(insn_pc + off); break; }
    case Opcode::IFLT: { auto off = frame.read_s2(); if (frame.pop_int() <  0) frame.set_pc(insn_pc + off); break; }
    case Opcode::IFGE: { auto off = frame.read_s2(); if (frame.pop_int() >= 0) frame.set_pc(insn_pc + off); break; }
    case Opcode::IFGT: { auto off = frame.read_s2(); if (frame.pop_int() >  0) frame.set_pc(insn_pc + off); break; }
    case Opcode::IFLE: { auto off = frame.read_s2(); if (frame.pop_int() <= 0) frame.set_pc(insn_pc + off); break; }

    // --- if_icmp<cond> — branch if two ints compared ---
    case Opcode::IF_ICMPEQ: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 == v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ICMPNE: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 != v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ICMPLT: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 <  v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ICMPGE: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 >= v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ICMPGT: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 >  v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ICMPLE: { auto off = frame.read_s2(); auto v2 = frame.pop_int(); auto v1 = frame.pop_int(); if (v1 <= v2) frame.set_pc(insn_pc + off); break; }

    // --- if_acmp<cond> — branch if two references compared ---
    case Opcode::IF_ACMPEQ: { auto off = frame.read_s2(); auto v2 = frame.pop_ref(); auto v1 = frame.pop_ref(); if (v1 == v2) frame.set_pc(insn_pc + off); break; }
    case Opcode::IF_ACMPNE: { auto off = frame.read_s2(); auto v2 = frame.pop_ref(); auto v1 = frame.pop_ref(); if (v1 != v2) frame.set_pc(insn_pc + off); break; }

    // ========================================================================
    // §6.5 — Control
    // ========================================================================

    case Opcode::GOTO: {
        auto off = frame.read_s2();
        frame.set_pc(insn_pc + off);
        break;
    }

    case Opcode::GOTO_W: {
        auto off = frame.read_s4();
        frame.set_pc(insn_pc + off);
        break;
    }

    case Opcode::JSR: {
        auto off = frame.read_s2();
        frame.push_int(static_cast<std::int32_t>(frame.pc()));  // push return address
        frame.set_pc(insn_pc + off);
        break;
    }

    case Opcode::JSR_W: {
        auto off = frame.read_s4();
        frame.push_int(static_cast<std::int32_t>(frame.pc()));
        frame.set_pc(insn_pc + off);
        break;
    }

    case Opcode::RET: {
        auto index = frame.read_u1();
        frame.set_pc(static_cast<std::uint32_t>(frame.get_local_int(index)));
        break;
    }

    case Opcode::TABLESWITCH: {
        // Align PC to 4-byte boundary (relative to method start)
        while (frame.pc() % 4 != 0) (void)frame.read_u1();
        auto default_off = frame.read_s4();
        auto low = frame.read_s4();
        auto high = frame.read_s4();
        auto index = frame.pop_int();
        if (index >= low && index <= high) {
            // Skip to the correct offset
            std::int32_t num_skip = index - low;
            for (std::int32_t i = 0; i < num_skip; ++i) (void)frame.read_s4();
            auto off = frame.read_s4();
            frame.set_pc(insn_pc + off);
        } else {
            frame.set_pc(insn_pc + default_off);
        }
        break;
    }

    case Opcode::LOOKUPSWITCH: {
        while (frame.pc() % 4 != 0) (void)frame.read_u1();
        auto default_off = frame.read_s4();
        auto npairs = frame.read_s4();
        auto key = frame.pop_int();
        bool found = false;
        for (std::int32_t i = 0; i < npairs; ++i) {
            auto match = frame.read_s4();
            auto off = frame.read_s4();
            if (key == match) {
                frame.set_pc(insn_pc + off);
                found = true;
                break;
            }
        }
        if (!found) {
            frame.set_pc(insn_pc + default_off);
        }
        break;
    }

    // --- Returns ---
    // Helper: release synchronized monitor if set
    #define RELEASE_MONITOR_IF_SYNC() \
        do { if (frame.sync_object_) { \
            static_cast<JObject*>(frame.sync_object_)->monitor.unlock(); \
        } } while(0)

    case Opcode::IRETURN: {
        auto val = frame.pop_int();
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) caller->push_int(val);
        return false;
    }
    case Opcode::LRETURN: {
        auto val = frame.pop_long();
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) caller->push_long(val);
        return false;
    }
    case Opcode::FRETURN: {
        auto val = frame.pop_float();
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) caller->push_float(val);
        return false;
    }
    case Opcode::DRETURN: {
        auto val = frame.pop_double();
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) caller->push_double(val);
        return false;
    }
    case Opcode::ARETURN: {
        auto* val = frame.pop_ref();
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        if (auto* caller = thread.current_frame()) caller->push_ref(val);
        return false;
    }
    case Opcode::RETURN:
        RELEASE_MONITOR_IF_SYNC();
        thread.pop_frame();
        return false;

    #undef RELEASE_MONITOR_IF_SYNC

    // ========================================================================
    // §6.5 — References (field access, method invocation, object creation)
    // ========================================================================

    case Opcode::GETSTATIC:
    case Opcode::PUTSTATIC:
    case Opcode::GETFIELD:
    case Opcode::PUTFIELD: {
        auto cp_index = frame.read_u2();
        do_field_access(thread, frame, opcode, cp_index);
        break;
    }

    case Opcode::INVOKEVIRTUAL:
    case Opcode::INVOKESPECIAL:
    case Opcode::INVOKESTATIC: {
        auto cp_index = frame.read_u2();
        do_invoke(thread, frame, opcode, cp_index);
        return thread.current_frame() != nullptr;
    }

    case Opcode::INVOKEINTERFACE: {
        auto cp_index = frame.read_u2();
        (void)frame.read_u1();  // count (unused in our impl)
        (void)frame.read_u1();  // must be zero
        do_invoke(thread, frame, opcode, cp_index);
        return thread.current_frame() != nullptr;
    }

    case Opcode::INVOKEDYNAMIC: {
        auto cp_index = frame.read_u2();
        (void)frame.read_u1();  // must be zero
        (void)frame.read_u1();  // must be zero
        throw InterpreterError(std::format(
            "invokedynamic not yet supported (cp_index={})", cp_index));
    }

    case Opcode::NEW: {
        auto cp_index = frame.read_u2();
        do_new(thread, frame, cp_index);
        break;
    }

    case Opcode::NEWARRAY: {
        auto atype = frame.read_u1();
        do_newarray(frame, atype);
        break;
    }

    case Opcode::ANEWARRAY: {
        auto cp_index = frame.read_u2();
        do_anewarray(frame, cp_index);
        break;
    }

    case Opcode::ARRAYLENGTH: {
        auto* arr = static_cast<JObject*>(frame.pop_ref());
        if (!arr) throw InterpreterError("NullPointerException: arraylength");
        frame.push_int(arr->array_length());
        break;
    }

    case Opcode::ATHROW:
        throw InterpreterError("athrow not yet supported");

    case Opcode::CHECKCAST: {
        auto cp_index = frame.read_u2();
        do_checkcast(frame, cp_index);
        break;
    }

    case Opcode::INSTANCEOF: {
        auto cp_index = frame.read_u2();
        do_instanceof(frame, cp_index);
        break;
    }

    case Opcode::MONITORENTER: {
        auto* obj = static_cast<JObject*>(frame.pop_ref());
        if (obj) obj->monitor.lock();
        break;
    }

    case Opcode::MONITOREXIT: {
        auto* obj = static_cast<JObject*>(frame.pop_ref());
        if (obj) obj->monitor.unlock();
        break;
    }

    // ========================================================================
    // §6.5 — Extended
    // ========================================================================

    case Opcode::WIDE: {
        auto wide_op = frame.read_u1();
        auto wide_index = frame.read_u2();
        switch (wide_op) {
        case Opcode::ILOAD:  frame.push_int(frame.get_local_int(wide_index)); break;
        case Opcode::LLOAD:  frame.push_long(frame.get_local_long(wide_index)); break;
        case Opcode::FLOAD:  frame.push_float(frame.get_local_float(wide_index)); break;
        case Opcode::DLOAD:  frame.push_double(frame.get_local_double(wide_index)); break;
        case Opcode::ALOAD:  frame.push_ref(frame.get_local_ref(wide_index)); break;
        case Opcode::ISTORE: frame.set_local_int(wide_index, frame.pop_int()); break;
        case Opcode::LSTORE: frame.set_local_long(wide_index, frame.pop_long()); break;
        case Opcode::FSTORE: frame.set_local_float(wide_index, frame.pop_float()); break;
        case Opcode::DSTORE: frame.set_local_double(wide_index, frame.pop_double()); break;
        case Opcode::ASTORE: frame.set_local_ref(wide_index, frame.pop_ref()); break;
        case Opcode::IINC: {
            auto delta = frame.read_s2();
            frame.set_local_int(wide_index, frame.get_local_int(wide_index) + delta);
            break;
        }
        case Opcode::RET:
            frame.set_pc(static_cast<std::uint32_t>(frame.get_local_int(wide_index)));
            break;
        default:
            throw InterpreterError(std::format("Invalid wide opcode: 0x{:02X}", wide_op));
        }
        break;
    }

    case Opcode::MULTIANEWARRAY: {
        auto cp_index = frame.read_u2();
        auto dimensions = frame.read_u1();
        do_multianewarray(frame, cp_index, dimensions);
        break;
    }

    case Opcode::IFNULL: {
        auto off = frame.read_s2();
        if (frame.pop_ref() == nullptr) frame.set_pc(insn_pc + off);
        break;
    }

    case Opcode::IFNONNULL: {
        auto off = frame.read_s2();
        if (frame.pop_ref() != nullptr) frame.set_pc(insn_pc + off);
        break;
    }

    default:
        throw InterpreterError(std::format(
            "Unimplemented opcode: 0x{:02X} at PC={}", opcode, insn_pc));
    }

    return true;
}

// ============================================================================
// Helper implementations
// ============================================================================

void Interpreter::do_ldc(Frame& frame, std::uint16_t cp_index) {
    const auto& cf = frame.get_class_file();
    auto* entry = cf.constant_pool[cp_index].get();

    if (auto* ii = dynamic_cast<const CONSTANT_Integer_info*>(entry)) {
        std::int32_t val;
        std::memcpy(&val, &ii->bytes, sizeof(std::int32_t));
        frame.push_int(val);
    } else if (auto* fi = dynamic_cast<const CONSTANT_Float_info*>(entry)) {
        float val;
        std::memcpy(&val, &fi->bytes, sizeof(float));
        frame.push_float(val);
    } else if (auto* si = dynamic_cast<const CONSTANT_String_info*>(entry)) {
        // Create a JObject representing the String on the heap
        auto* str_obj = heap_.allocate_object("java/lang/String");
        const auto& str = cf.get_utf8(si->string_index);
        // Store the backing char array
        auto* char_arr = heap_.allocate_primitive_array(
            ArrayType::T_CHAR, static_cast<std::int32_t>(str.size()));
        for (std::size_t i = 0; i < str.size(); ++i) {
            char_arr->array_char[i] = static_cast<std::uint16_t>(str[i]);
        }
        str_obj->fields["java/lang/String.value"] = static_cast<void*>(char_arr);
        frame.push_ref(str_obj);
    } else if (dynamic_cast<const CONSTANT_Class_info*>(entry)) {
        // Push a reference representing the Class object (simplified)
        auto* cls_obj = heap_.allocate_object("java/lang/Class");
        cls_obj->fields["java/lang/Class.name"] =
            static_cast<void*>(nullptr);  // simplified
        frame.push_ref(cls_obj);
    } else {
        throw InterpreterError(std::format(
            "ldc: unsupported constant pool entry type at index {}", cp_index));
    }
}

void Interpreter::do_invoke(JavaThread& thread, Frame& frame,
                            std::uint8_t opcode, std::uint16_t cp_index) {
    const auto& cf = frame.get_class_file();
    auto* ref = dynamic_cast<const CONSTANT_Ref_info*>(cf.constant_pool[cp_index].get());
    if (!ref) {
        throw InterpreterError(std::format(
            "invoke: constant pool index {} is not a method/interface ref", cp_index));
    }

    auto* class_info = dynamic_cast<const CONSTANT_Class_info*>(
        cf.constant_pool[ref->class_index].get());
    auto* nat = dynamic_cast<const CONSTANT_NameAndType_info*>(
        cf.constant_pool[ref->name_and_type_index].get());
    const auto& class_name = cf.get_utf8(class_info->name_index);
    const auto& method_name = cf.get_utf8(nat->name_index);
    const auto& method_desc = cf.get_utf8(nat->descriptor_index);

    // Check native registry FIRST — if a native binding exists, use it directly
    // without attempting class loading or method resolution. This handles:
    //   - System classes we can't fully execute (PrintStream, Object, etc.)
    //   - Methods with ACC_NATIVE flag in their .class files
    auto native_key = NativeMethodRegistry::make_key(class_name, method_name, method_desc);
    auto* native_fn = native_registry_.find(native_key);
    if (native_fn) {
        VMContext ctx{thread, frame, heap_, *this, class_loader_};
        (*native_fn)(ctx);
        return;
    }

    // §5.5: Ensure class is initialized for invokestatic
    if (opcode == Opcode::INVOKESTATIC) {
        ensure_initialized(thread, class_name);
    }

    // §5.3: On-demand class loading
    auto target_cf = class_loader_.load_class(class_name);
    if (!target_cf) {
        throw InterpreterError(std::format(
            "ClassNotFoundException: {}", class_name));
    }

    // Find the method in the target class
    const method_info* target_method = nullptr;
    for (const auto& m : target_cf->methods) {
        if (target_cf->get_utf8(m.name_index) == method_name &&
            target_cf->get_utf8(m.descriptor_index) == method_desc) {
            target_method = &m;
            break;
        }
    }

    if (!target_method) {
        throw InterpreterError(std::format(
            "NoSuchMethodError: {}.{}:{}", class_name, method_name, method_desc));
    }

    // Check for native method (ACC_NATIVE flag set in .class)
    // We already checked the native registry at the top, so if we reach here
    // with ACC_NATIVE, the method is truly unregistered.
    if (target_method->access_flags & MethodAccess::ACC_NATIVE) {
        throw NativeMethodNotFoundError(std::format(
            "NativeMethodNotFoundError: {}.{}:{}", class_name, method_name, method_desc));
    }

    // Find Code attribute
    const Code_attribute* code_attr = nullptr;
    for (const auto& attr : target_method->attributes) {
        code_attr = dynamic_cast<const Code_attribute*>(attr.get());
        if (code_attr) break;
    }
    if (!code_attr) {
        throw InterpreterError(std::format(
            "No Code attribute for {}.{}:{}", class_name, method_name, method_desc));
    }

    // Count parameters from descriptor to set up locals
    // Descriptor format: (param_types)return_type
    // Each param occupies 1 local (or 2 for long/double)
    std::size_t num_args = 0;
    bool is_static = (opcode == Opcode::INVOKESTATIC);
    {
        std::size_t i = 1;  // skip '('
        while (i < method_desc.size() && method_desc[i] != ')') {
            char c = method_desc[i];
            if (c == 'J' || c == 'D') {
                num_args += 2;
                ++i;
            } else if (c == 'L') {
                num_args += 1;
                while (i < method_desc.size() && method_desc[i] != ';') ++i;
                ++i;  // skip ';'
            } else if (c == '[') {
                ++i;  // skip array dimensions
                // continue to parse element type
            } else {
                num_args += 1;
                ++i;
            }
        }
        if (!is_static) ++num_args;  // 'this' reference
    }

    // Create the new frame
    auto new_frame = std::make_unique<Frame>(
        target_cf, target_method,
        code_attr->max_locals, code_attr->max_stack,
        std::span<const std::uint8_t>(code_attr->code));

    // Pop arguments from caller's stack and set as locals in new frame
    // Arguments are on the stack in order: [objectref (if non-static)], arg1, arg2, ...
    // We pop in reverse order and store them
    std::vector<Slot> args(num_args);
    for (std::size_t i = num_args; i > 0; --i) {
        args[i - 1] = frame.pop_slot();
    }

    // Set locals from args
    std::uint16_t local_idx = 0;
    for (std::size_t i = 0; i < num_args && local_idx < code_attr->max_locals; ++i) {
        switch (args[i].type) {
        case SlotType::Int:
            new_frame->set_local_int(local_idx, args[i].value.i);
            break;
        case SlotType::Float:
            new_frame->set_local_float(local_idx, args[i].value.f);
            break;
        case SlotType::Long:
            new_frame->set_local_long(local_idx, args[i].value.l);
            ++local_idx;  // long takes 2 slots
            break;
        case SlotType::Double:
            new_frame->set_local_double(local_idx, args[i].value.d);
            ++local_idx;  // double takes 2 slots
            break;
        case SlotType::Reference:
            new_frame->set_local_ref(local_idx, args[i].value.ref);
            break;
        default:
            break;
        }
        ++local_idx;
    }

    thread.push_frame(std::move(new_frame));

    // §8.4.3.6: ACC_SYNCHRONIZED — acquire monitor on method entry
    if (target_method->access_flags & MethodAccess::ACC_SYNCHRONIZED) {
        void* monitor_obj = nullptr;
        if (target_method->access_flags & MethodAccess::ACC_STATIC) {
            // Static synchronized: lock the class object (simplified: use nullptr)
        } else {
            // Instance synchronized: lock 'this' (args[0])
            if (!args.empty() && args[0].type == SlotType::Reference) {
                monitor_obj = args[0].value.ref;
            }
        }
        if (monitor_obj) {
            static_cast<JObject*>(monitor_obj)->monitor.lock();
            thread.current_frame()->sync_object_ = monitor_obj;
        }
    }
}

void Interpreter::do_field_access(JavaThread& thread, Frame& frame,
                                  std::uint8_t opcode, std::uint16_t cp_index) {
    const auto& cf = frame.get_class_file();
    auto* ref = dynamic_cast<const CONSTANT_Fieldref_info*>(cf.constant_pool[cp_index].get());
    if (!ref) {
        throw InterpreterError(std::format(
            "field access: cp index {} is not a Fieldref", cp_index));
    }

    auto* class_info = dynamic_cast<const CONSTANT_Class_info*>(
        cf.constant_pool[ref->class_index].get());
    auto* nat = dynamic_cast<const CONSTANT_NameAndType_info*>(
        cf.constant_pool[ref->name_and_type_index].get());
    const auto& class_name = cf.get_utf8(class_info->name_index);
    const auto& field_name = cf.get_utf8(nat->name_index);
    const auto& field_desc = cf.get_utf8(nat->descriptor_index);
    std::string full_name = std::string(class_name) + "." + std::string(field_name);

    // §5.5: Ensure class is initialized for static field access
    if (opcode == Opcode::GETSTATIC || opcode == Opcode::PUTSTATIC) {
        ensure_initialized(thread, class_name);
    }

    // On-demand class loading
    auto target_cf = class_loader_.load_class(class_name);

    switch (opcode) {
    case Opcode::GETSTATIC: {
        // §2.5.4: Check static field storage in the heap
        auto* stored = heap_.get_static_field(full_name);
        if (stored) {
            if (auto* vi = std::get_if<std::int32_t>(stored)) frame.push_int(*vi);
            else if (auto* vl = std::get_if<std::int64_t>(stored)) frame.push_long(*vl);
            else if (auto* vf = std::get_if<float>(stored)) frame.push_float(*vf);
            else if (auto* vd = std::get_if<double>(stored)) frame.push_double(*vd);
            else if (auto* vr = std::get_if<void*>(stored)) frame.push_ref(*vr);
        } else {
            // No stored value — push type-appropriate default
            if (field_desc[0] == 'I' || field_desc[0] == 'Z' || field_desc[0] == 'B' ||
                field_desc[0] == 'C' || field_desc[0] == 'S') frame.push_int(0);
            else if (field_desc[0] == 'J') frame.push_long(0LL);
            else if (field_desc[0] == 'F') frame.push_float(0.0f);
            else if (field_desc[0] == 'D') frame.push_double(0.0);
            else frame.push_ref(nullptr);
        }
        break;
    }
    case Opcode::PUTSTATIC: {
        // Store static field value
        FieldValue fv;
        if (field_desc[0] == 'I' || field_desc[0] == 'Z' || field_desc[0] == 'B' ||
            field_desc[0] == 'C' || field_desc[0] == 'S') fv = frame.pop_int();
        else if (field_desc[0] == 'J') fv = frame.pop_long();
        else if (field_desc[0] == 'F') fv = frame.pop_float();
        else if (field_desc[0] == 'D') fv = frame.pop_double();
        else fv = frame.pop_ref();
        heap_.set_static_field(full_name, fv);
        break;
    }
    case Opcode::GETFIELD: {
        auto* obj = static_cast<JObject*>(frame.pop_ref());
        if (!obj) throw InterpreterError("NullPointerException: getfield");
        auto it = obj->fields.find(full_name);
        if (it == obj->fields.end()) {
            // Push default
            if (field_desc[0] == 'I' || field_desc[0] == 'Z' || field_desc[0] == 'B' ||
                field_desc[0] == 'C' || field_desc[0] == 'S') frame.push_int(0);
            else if (field_desc[0] == 'J') frame.push_long(0LL);
            else if (field_desc[0] == 'F') frame.push_float(0.0f);
            else if (field_desc[0] == 'D') frame.push_double(0.0);
            else frame.push_ref(nullptr);
        } else {
            auto& fv = it->second;
            if (auto* vi = std::get_if<std::int32_t>(&fv)) frame.push_int(*vi);
            else if (auto* vl = std::get_if<std::int64_t>(&fv)) frame.push_long(*vl);
            else if (auto* vf = std::get_if<float>(&fv)) frame.push_float(*vf);
            else if (auto* vd = std::get_if<double>(&fv)) frame.push_double(*vd);
            else if (auto* vr = std::get_if<void*>(&fv)) frame.push_ref(*vr);
        }
        break;
    }
    case Opcode::PUTFIELD: {
        FieldValue fv;
        if (field_desc[0] == 'I' || field_desc[0] == 'Z' || field_desc[0] == 'B' ||
            field_desc[0] == 'C' || field_desc[0] == 'S') fv = frame.pop_int();
        else if (field_desc[0] == 'J') fv = frame.pop_long();
        else if (field_desc[0] == 'F') fv = frame.pop_float();
        else if (field_desc[0] == 'D') fv = frame.pop_double();
        else fv = frame.pop_ref();
        auto* obj = static_cast<JObject*>(frame.pop_ref());
        if (!obj) throw InterpreterError("NullPointerException: putfield");
        obj->fields[full_name] = fv;
        break;
    }
    default: break;
    }
}

void Interpreter::do_new(JavaThread& thread, Frame& frame, std::uint16_t cp_index) {
    const auto& cf = frame.get_class_file();
    auto* ci = dynamic_cast<const CONSTANT_Class_info*>(cf.constant_pool[cp_index].get());
    if (!ci) throw InterpreterError(std::format("new: cp index {} not a Class", cp_index));
    const auto& class_name = cf.get_utf8(ci->name_index);

    // §5.5: Ensure class is initialized before instantiation
    ensure_initialized(thread, class_name);

    auto* obj = heap_.allocate_object(class_name);
    frame.push_ref(obj);
}

void Interpreter::do_newarray(Frame& frame, std::uint8_t atype) {
    auto length = frame.pop_int();
    auto* arr = heap_.allocate_primitive_array(atype, length);
    frame.push_ref(arr);
}

void Interpreter::do_anewarray(Frame& frame, std::uint16_t cp_index) {
    const auto& cf = frame.get_class_file();
    auto* ci = dynamic_cast<const CONSTANT_Class_info*>(cf.constant_pool[cp_index].get());
    if (!ci) throw InterpreterError(std::format("anewarray: cp index {} not a Class", cp_index));
    const auto& elem_class = cf.get_utf8(ci->name_index);
    auto length = frame.pop_int();
    auto* arr = heap_.allocate_ref_array(elem_class, length);
    frame.push_ref(arr);
}

void Interpreter::do_multianewarray(Frame& frame, std::uint16_t cp_index,
                                    std::uint8_t dimensions) {
    // Pop dimension counts
    std::vector<std::int32_t> dim_sizes(dimensions);
    for (int i = dimensions - 1; i >= 0; --i) {
        dim_sizes[static_cast<std::size_t>(i)] = frame.pop_int();
    }

    // Simplified: only allocate the outermost dimension as a ref array
    const auto& cf = frame.get_class_file();
    auto* ci = dynamic_cast<const CONSTANT_Class_info*>(cf.constant_pool[cp_index].get());
    if (!ci) throw InterpreterError("multianewarray: invalid class ref");
    const auto& class_name = cf.get_utf8(ci->name_index);

    auto* arr = heap_.allocate_ref_array(class_name, dim_sizes[0]);
    frame.push_ref(arr);
}

void Interpreter::do_checkcast([[maybe_unused]] Frame& frame, std::uint16_t cp_index) {
    // Simplified: always passes (no real type checking hierarchy yet)
    (void)cp_index;
    // objectref stays on stack — peek, don't pop
    // Per spec: if null, pass. If not null, we'd check type.
    // For now, always pass.
}

void Interpreter::do_instanceof(Frame& frame, std::uint16_t cp_index) {
    (void)cp_index;
    auto* ref = frame.pop_ref();
    // Simplified: null → 0, non-null → 1
    frame.push_int(ref != nullptr ? 1 : 0);
}

// ============================================================================
// §5.5 Class Initialization
// ============================================================================

void Interpreter::ensure_initialized(JavaThread& thread, std::string_view class_name) {
    // Load the class first — we need it to check/set init_state
    auto cf = class_loader_.load_class(class_name);
    if (!cf) {
        // System/bootstrap class without a loadable .class file — skip
        return;
    }

    // §5.5: Check initialization state on the ClassFile itself
    if (cf->init_state == ClassFile::InitState::Initialized ||
        cf->init_state == ClassFile::InitState::Initializing) {
        return;
    }

    // §5.5 Step 7: Recursively initialize the superclass first
    if (cf->super_class != 0) {
        auto* super_cls = dynamic_cast<const CONSTANT_Class_info*>(
            cf->constant_pool[cf->super_class].get());
        if (super_cls) {
            const auto& super_name = cf->get_utf8(super_cls->name_index);
            ensure_initialized(thread, super_name);
        }
    }

    // Mark as Initializing (re-entrant guard for circular dependencies)
    cf->init_state = ClassFile::InitState::Initializing;

    // Find <clinit> method
    const method_info* clinit = nullptr;
    for (const auto& m : cf->methods) {
        if (cf->get_utf8(m.name_index) == "<clinit>" &&
            cf->get_utf8(m.descriptor_index) == "()V") {
            clinit = &m;
            break;
        }
    }

    if (clinit) {
        // Find Code attribute
        const Code_attribute* code_attr = nullptr;
        for (const auto& attr : clinit->attributes) {
            code_attr = dynamic_cast<const Code_attribute*>(attr.get());
            if (code_attr) break;
        }

        if (code_attr) {
            // Create a frame for <clinit> and execute it synchronously
            auto frame = std::make_unique<Frame>(
                cf, clinit,
                code_attr->max_locals, code_attr->max_stack,
                std::span<const std::uint8_t>(code_attr->code));

            thread.push_frame(std::move(frame));

            // Execute <clinit> to completion within the current thread
            while (thread.current_frame() &&
                   thread.current_frame()->get_bytecode().data() == code_attr->code.data()) {
                (void)execute_instruction(thread, *thread.current_frame());
            }
        }
    }

    // Mark as Initialized
    cf->init_state = ClassFile::InitState::Initialized;
}

void Interpreter::trigger_gc(JavaThread& thread) {
    // Collect GC roots from:
    //   1. All reference slots in the thread's frame stack (locals + operand stack)
    //   2. Static fields are handled by Heap::gc() internally

    std::vector<void*> raw_roots;
    thread.collect_gc_roots(raw_roots);

    // Convert to JObject* for the GC interface
    std::vector<JObject*> roots;
    roots.reserve(raw_roots.size());
    for (auto* ptr : raw_roots) {
        roots.push_back(static_cast<JObject*>(ptr));
    }

    // Run GC
    heap_.gc(roots);

    // After GC, update all thread stack references via forwarding pointers
    thread.update_gc_references();
}

} // namespace aijvm::runtime
