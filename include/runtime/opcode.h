#pragma once

#include <cstdint>

namespace aijvm::runtime {

// ============================================================================
// §6 / Chapter 7 — Complete JVM Opcode Definitions
// ============================================================================
// All 202 defined opcodes from the JVM SE 26 Specification, Chapter 7.
// Reserved opcodes (breakpoint, impdep1, impdep2) are included for
// completeness but are not implemented in the interpreter.
// ============================================================================

namespace Opcode {

    // §6.5 — Constants (0x00 – 0x14)
    constexpr std::uint8_t NOP           = 0x00;
    constexpr std::uint8_t ACONST_NULL   = 0x01;
    constexpr std::uint8_t ICONST_M1     = 0x02;
    constexpr std::uint8_t ICONST_0      = 0x03;
    constexpr std::uint8_t ICONST_1      = 0x04;
    constexpr std::uint8_t ICONST_2      = 0x05;
    constexpr std::uint8_t ICONST_3      = 0x06;
    constexpr std::uint8_t ICONST_4      = 0x07;
    constexpr std::uint8_t ICONST_5      = 0x08;
    constexpr std::uint8_t LCONST_0      = 0x09;
    constexpr std::uint8_t LCONST_1      = 0x0A;
    constexpr std::uint8_t FCONST_0      = 0x0B;
    constexpr std::uint8_t FCONST_1      = 0x0C;
    constexpr std::uint8_t FCONST_2      = 0x0D;
    constexpr std::uint8_t DCONST_0      = 0x0E;
    constexpr std::uint8_t DCONST_1      = 0x0F;
    constexpr std::uint8_t BIPUSH        = 0x10;
    constexpr std::uint8_t SIPUSH        = 0x11;
    constexpr std::uint8_t LDC           = 0x12;
    constexpr std::uint8_t LDC_W         = 0x13;
    constexpr std::uint8_t LDC2_W        = 0x14;

    // §6.5 — Loads (0x15 – 0x35)
    constexpr std::uint8_t ILOAD         = 0x15;
    constexpr std::uint8_t LLOAD         = 0x16;
    constexpr std::uint8_t FLOAD         = 0x17;
    constexpr std::uint8_t DLOAD         = 0x18;
    constexpr std::uint8_t ALOAD         = 0x19;
    constexpr std::uint8_t ILOAD_0       = 0x1A;
    constexpr std::uint8_t ILOAD_1       = 0x1B;
    constexpr std::uint8_t ILOAD_2       = 0x1C;
    constexpr std::uint8_t ILOAD_3       = 0x1D;
    constexpr std::uint8_t LLOAD_0       = 0x1E;
    constexpr std::uint8_t LLOAD_1       = 0x1F;
    constexpr std::uint8_t LLOAD_2       = 0x20;
    constexpr std::uint8_t LLOAD_3       = 0x21;
    constexpr std::uint8_t FLOAD_0       = 0x22;
    constexpr std::uint8_t FLOAD_1       = 0x23;
    constexpr std::uint8_t FLOAD_2       = 0x24;
    constexpr std::uint8_t FLOAD_3       = 0x25;
    constexpr std::uint8_t DLOAD_0       = 0x26;
    constexpr std::uint8_t DLOAD_1       = 0x27;
    constexpr std::uint8_t DLOAD_2       = 0x28;
    constexpr std::uint8_t DLOAD_3       = 0x29;
    constexpr std::uint8_t ALOAD_0       = 0x2A;
    constexpr std::uint8_t ALOAD_1       = 0x2B;
    constexpr std::uint8_t ALOAD_2       = 0x2C;
    constexpr std::uint8_t ALOAD_3       = 0x2D;
    constexpr std::uint8_t IALOAD        = 0x2E;
    constexpr std::uint8_t LALOAD        = 0x2F;
    constexpr std::uint8_t FALOAD        = 0x30;
    constexpr std::uint8_t DALOAD        = 0x31;
    constexpr std::uint8_t AALOAD        = 0x32;
    constexpr std::uint8_t BALOAD        = 0x33;
    constexpr std::uint8_t CALOAD        = 0x34;
    constexpr std::uint8_t SALOAD        = 0x35;

    // §6.5 — Stores (0x36 – 0x56)
    constexpr std::uint8_t ISTORE        = 0x36;
    constexpr std::uint8_t LSTORE        = 0x37;
    constexpr std::uint8_t FSTORE        = 0x38;
    constexpr std::uint8_t DSTORE        = 0x39;
    constexpr std::uint8_t ASTORE        = 0x3A;
    constexpr std::uint8_t ISTORE_0      = 0x3B;
    constexpr std::uint8_t ISTORE_1      = 0x3C;
    constexpr std::uint8_t ISTORE_2      = 0x3D;
    constexpr std::uint8_t ISTORE_3      = 0x3E;
    constexpr std::uint8_t LSTORE_0      = 0x3F;
    constexpr std::uint8_t LSTORE_1      = 0x40;
    constexpr std::uint8_t LSTORE_2      = 0x41;
    constexpr std::uint8_t LSTORE_3      = 0x42;
    constexpr std::uint8_t FSTORE_0      = 0x43;
    constexpr std::uint8_t FSTORE_1      = 0x44;
    constexpr std::uint8_t FSTORE_2      = 0x45;
    constexpr std::uint8_t FSTORE_3      = 0x46;
    constexpr std::uint8_t DSTORE_0      = 0x47;
    constexpr std::uint8_t DSTORE_1      = 0x48;
    constexpr std::uint8_t DSTORE_2      = 0x49;
    constexpr std::uint8_t DSTORE_3      = 0x4A;
    constexpr std::uint8_t ASTORE_0      = 0x4B;
    constexpr std::uint8_t ASTORE_1      = 0x4C;
    constexpr std::uint8_t ASTORE_2      = 0x4D;
    constexpr std::uint8_t ASTORE_3      = 0x4E;
    constexpr std::uint8_t IASTORE       = 0x4F;
    constexpr std::uint8_t LASTORE       = 0x50;
    constexpr std::uint8_t FASTORE       = 0x51;
    constexpr std::uint8_t DASTORE       = 0x52;
    constexpr std::uint8_t AASTORE       = 0x53;
    constexpr std::uint8_t BASTORE       = 0x54;
    constexpr std::uint8_t CASTORE       = 0x55;
    constexpr std::uint8_t SASTORE       = 0x56;

    // §6.5 — Stack (0x57 – 0x5F)
    constexpr std::uint8_t POP           = 0x57;
    constexpr std::uint8_t POP2          = 0x58;
    constexpr std::uint8_t DUP           = 0x59;
    constexpr std::uint8_t DUP_X1        = 0x5A;
    constexpr std::uint8_t DUP_X2        = 0x5B;
    constexpr std::uint8_t DUP2          = 0x5C;
    constexpr std::uint8_t DUP2_X1       = 0x5D;
    constexpr std::uint8_t DUP2_X2       = 0x5E;
    constexpr std::uint8_t SWAP          = 0x5F;

    // §6.5 — Math (0x60 – 0x84)
    constexpr std::uint8_t IADD          = 0x60;
    constexpr std::uint8_t LADD          = 0x61;
    constexpr std::uint8_t FADD          = 0x62;
    constexpr std::uint8_t DADD          = 0x63;
    constexpr std::uint8_t ISUB          = 0x64;
    constexpr std::uint8_t LSUB          = 0x65;
    constexpr std::uint8_t FSUB          = 0x66;
    constexpr std::uint8_t DSUB          = 0x67;
    constexpr std::uint8_t IMUL          = 0x68;
    constexpr std::uint8_t LMUL          = 0x69;
    constexpr std::uint8_t FMUL          = 0x6A;
    constexpr std::uint8_t DMUL          = 0x6B;
    constexpr std::uint8_t IDIV          = 0x6C;
    constexpr std::uint8_t LDIV          = 0x6D;
    constexpr std::uint8_t FDIV          = 0x6E;
    constexpr std::uint8_t DDIV          = 0x6F;
    constexpr std::uint8_t IREM          = 0x70;
    constexpr std::uint8_t LREM          = 0x71;
    constexpr std::uint8_t FREM          = 0x72;
    constexpr std::uint8_t DREM          = 0x73;
    constexpr std::uint8_t INEG          = 0x74;
    constexpr std::uint8_t LNEG          = 0x75;
    constexpr std::uint8_t FNEG          = 0x76;
    constexpr std::uint8_t DNEG          = 0x77;
    constexpr std::uint8_t ISHL          = 0x78;
    constexpr std::uint8_t LSHL          = 0x79;
    constexpr std::uint8_t ISHR          = 0x7A;
    constexpr std::uint8_t LSHR          = 0x7B;
    constexpr std::uint8_t IUSHR         = 0x7C;
    constexpr std::uint8_t LUSHR         = 0x7D;
    constexpr std::uint8_t IAND          = 0x7E;
    constexpr std::uint8_t LAND          = 0x7F;
    constexpr std::uint8_t IOR           = 0x80;
    constexpr std::uint8_t LOR           = 0x81;
    constexpr std::uint8_t IXOR          = 0x82;
    constexpr std::uint8_t LXOR          = 0x83;
    constexpr std::uint8_t IINC          = 0x84;

    // §6.5 — Conversions (0x85 – 0x93)
    constexpr std::uint8_t I2L           = 0x85;
    constexpr std::uint8_t I2F           = 0x86;
    constexpr std::uint8_t I2D           = 0x87;
    constexpr std::uint8_t L2I           = 0x88;
    constexpr std::uint8_t L2F           = 0x89;
    constexpr std::uint8_t L2D           = 0x8A;
    constexpr std::uint8_t F2I           = 0x8B;
    constexpr std::uint8_t F2L           = 0x8C;
    constexpr std::uint8_t F2D           = 0x8D;
    constexpr std::uint8_t D2I           = 0x8E;
    constexpr std::uint8_t D2L           = 0x8F;
    constexpr std::uint8_t D2F           = 0x90;
    constexpr std::uint8_t I2B           = 0x91;
    constexpr std::uint8_t I2C           = 0x92;
    constexpr std::uint8_t I2S           = 0x93;

    // §6.5 — Comparisons (0x94 – 0xA6)
    constexpr std::uint8_t LCMP          = 0x94;
    constexpr std::uint8_t FCMPL         = 0x95;
    constexpr std::uint8_t FCMPG         = 0x96;
    constexpr std::uint8_t DCMPL         = 0x97;
    constexpr std::uint8_t DCMPG         = 0x98;
    constexpr std::uint8_t IFEQ          = 0x99;
    constexpr std::uint8_t IFNE          = 0x9A;
    constexpr std::uint8_t IFLT          = 0x9B;
    constexpr std::uint8_t IFGE          = 0x9C;
    constexpr std::uint8_t IFGT          = 0x9D;
    constexpr std::uint8_t IFLE          = 0x9E;
    constexpr std::uint8_t IF_ICMPEQ     = 0x9F;
    constexpr std::uint8_t IF_ICMPNE     = 0xA0;
    constexpr std::uint8_t IF_ICMPLT     = 0xA1;
    constexpr std::uint8_t IF_ICMPGE     = 0xA2;
    constexpr std::uint8_t IF_ICMPGT     = 0xA3;
    constexpr std::uint8_t IF_ICMPLE     = 0xA4;
    constexpr std::uint8_t IF_ACMPEQ     = 0xA5;
    constexpr std::uint8_t IF_ACMPNE     = 0xA6;

    // §6.5 — Control (0xA7 – 0xB1)
    constexpr std::uint8_t GOTO          = 0xA7;
    constexpr std::uint8_t JSR           = 0xA8;
    constexpr std::uint8_t RET           = 0xA9;
    constexpr std::uint8_t TABLESWITCH   = 0xAA;
    constexpr std::uint8_t LOOKUPSWITCH  = 0xAB;
    constexpr std::uint8_t IRETURN       = 0xAC;
    constexpr std::uint8_t LRETURN       = 0xAD;
    constexpr std::uint8_t FRETURN       = 0xAE;
    constexpr std::uint8_t DRETURN       = 0xAF;
    constexpr std::uint8_t ARETURN       = 0xB0;
    constexpr std::uint8_t RETURN        = 0xB1;

    // §6.5 — References (0xB2 – 0xC3)
    constexpr std::uint8_t GETSTATIC     = 0xB2;
    constexpr std::uint8_t PUTSTATIC     = 0xB3;
    constexpr std::uint8_t GETFIELD      = 0xB4;
    constexpr std::uint8_t PUTFIELD      = 0xB5;
    constexpr std::uint8_t INVOKEVIRTUAL = 0xB6;
    constexpr std::uint8_t INVOKESPECIAL = 0xB7;
    constexpr std::uint8_t INVOKESTATIC  = 0xB8;
    constexpr std::uint8_t INVOKEINTERFACE = 0xB9;
    constexpr std::uint8_t INVOKEDYNAMIC = 0xBA;
    constexpr std::uint8_t NEW           = 0xBB;
    constexpr std::uint8_t NEWARRAY      = 0xBC;
    constexpr std::uint8_t ANEWARRAY     = 0xBD;
    constexpr std::uint8_t ARRAYLENGTH   = 0xBE;
    constexpr std::uint8_t ATHROW        = 0xBF;
    constexpr std::uint8_t CHECKCAST     = 0xC0;
    constexpr std::uint8_t INSTANCEOF    = 0xC1;
    constexpr std::uint8_t MONITORENTER  = 0xC2;
    constexpr std::uint8_t MONITOREXIT   = 0xC3;

    // §6.5 — Extended (0xC4 – 0xC9)
    constexpr std::uint8_t WIDE          = 0xC4;
    constexpr std::uint8_t MULTIANEWARRAY = 0xC5;
    constexpr std::uint8_t IFNULL        = 0xC6;
    constexpr std::uint8_t IFNONNULL     = 0xC7;
    constexpr std::uint8_t GOTO_W        = 0xC8;
    constexpr std::uint8_t JSR_W         = 0xC9;

    // §6.2 — Reserved opcodes (not for normal use)
    constexpr std::uint8_t BREAKPOINT    = 0xCA;
    constexpr std::uint8_t IMPDEP1       = 0xFE;
    constexpr std::uint8_t IMPDEP2       = 0xFF;

} // namespace Opcode

// §6.5 newarray — atype values for primitive array creation
namespace ArrayType {
    constexpr std::uint8_t T_BOOLEAN = 4;
    constexpr std::uint8_t T_CHAR    = 5;
    constexpr std::uint8_t T_FLOAT   = 6;
    constexpr std::uint8_t T_DOUBLE  = 7;
    constexpr std::uint8_t T_BYTE    = 8;
    constexpr std::uint8_t T_SHORT   = 9;
    constexpr std::uint8_t T_INT     = 10;
    constexpr std::uint8_t T_LONG    = 11;
} // namespace ArrayType

} // namespace aijvm::runtime
