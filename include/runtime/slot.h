#pragma once

#include <cstdint>

namespace aijvm::runtime {

// ============================================================================
// Slot Design: Tagged Union (union + enum tag)
// ============================================================================
//
// Architectural choice justification:
//   We use a union-based tagged Slot over std::variant for three reasons:
//   1. Lower per-slot memory overhead — critical for operand stack and locals
//      in hot interpreter dispatch loops. sizeof(Slot) = 16 bytes (tag + padding
//      + 8-byte union) vs std::variant which adds additional bookkeeping.
//   2. Direct mapping to JVM spec semantics — JVM slots are fundamentally
//      untyped storage with dynamic type tracking. A union naturally models this.
//   3. Explicit control over two-slot long/double layout (§2.6.1) — the Frame
//      class enforces the spec rule that long/double occupy two consecutive
//      local variable indices, invalidating the upper slot.
//
// The union holds 64-bit storage so long/double fit in a single physical entry.
// Two-slot semantics are enforced at the Frame level: pushing a long/double
// occupies 2 stack depth units, and storing to locals[n] invalidates locals[n+1].
// ============================================================================

/// JVM value types that can be stored in a Slot.
/// Per §2.2, §2.3: primitive types (numeric + boolean + returnAddress) and reference types.
/// Per §2.11.1: boolean, byte, char, short are all promoted to int for computation.
enum class SlotType : std::uint8_t {
    Empty,          ///< Uninitialized or invalidated (upper half of long/double)
    Int,            ///< int (also stores byte, short, char, boolean per §2.11.1)
    Float,          ///< float (32-bit IEEE 754)
    Long,           ///< long (64-bit signed) — occupies two logical slots (§2.6.1)
    Double,         ///< double (64-bit IEEE 754) — occupies two logical slots (§2.6.1)
    Reference,      ///< Reference to object instance or array (§2.4)
    ReturnAddress   ///< returnAddress for jsr/ret instructions (§2.3.3)
};

/// Raw storage union for JVM slot data.
/// 64-bit union avoids splitting long/double across physical entries.
union JValue {
    std::int32_t  i;         ///< int (also byte, short, char, boolean)
    float         f;         ///< float
    std::int64_t  l;         ///< long
    double        d;         ///< double
    void*         ref;       ///< Object reference (typed when Heap is implemented)
    std::uint32_t ret_addr;  ///< returnAddress (bytecode offset for jsr/ret)
};

/// Slot: tagged union representing a single entry in local variables or operand stack.
/// Per §2.6.1: "A single local variable can hold a value of type boolean, byte, char,
/// short, int, float, reference, or returnAddress. A pair of local variables can hold
/// a value of type long or double."
struct Slot {
    SlotType type  = SlotType::Empty;
    JValue   value{.l = 0};

    // --- Factory methods for type-safe construction ---

    static Slot make_int(std::int32_t v) noexcept;
    static Slot make_float(float v) noexcept;
    static Slot make_long(std::int64_t v) noexcept;
    static Slot make_double(double v) noexcept;
    static Slot make_ref(void* v) noexcept;
    static Slot make_return_address(std::uint32_t addr) noexcept;
    static Slot make_empty() noexcept;

    /// Category 2 types (long/double) occupy two logical slots per §2.11.1.
    [[nodiscard]] bool is_category2() const noexcept;

    /// Check if slot is empty/invalidated.
    [[nodiscard]] bool is_empty() const noexcept;
};

} // namespace aijvm::runtime
