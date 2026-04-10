#include <gtest/gtest.h>

#include "runtime/slot.h"
#include "runtime/frame.h"
#include "runtime/heap.h"
#include "runtime/java_thread.h"
#include "runtime/safepoint.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <thread>
#include <vector>

using namespace aijvm::runtime;

// ============================================================================
// Helper: Create a Frame without needing a real ClassFile/method_info.
// Uses nullptr ClassFile and method for pure runtime logic testing.
// ============================================================================
static std::unique_ptr<Frame> make_test_frame(
    std::uint16_t max_locals,
    std::uint16_t max_stack,
    std::vector<std::uint8_t> bytecode_storage = {}) {
    // bytecode_storage must outlive the frame — caller is responsible.
    // For these tests we use the static-duration overload or keep storage alive.
    return std::make_unique<Frame>(
        nullptr, nullptr, max_locals, max_stack,
        std::span<const std::uint8_t>(bytecode_storage));
}

// ============================================================================
// §2.6.1 / §2.6.2 — Slot Tests
// ============================================================================

TEST(SlotTest, DefaultIsEmpty) {
    Slot s;
    EXPECT_TRUE(s.is_empty());
    EXPECT_FALSE(s.is_category2());
    EXPECT_EQ(s.type, SlotType::Empty);
}

TEST(SlotTest, MakeInt) {
    auto s = Slot::make_int(42);
    EXPECT_EQ(s.type, SlotType::Int);
    EXPECT_EQ(s.value.i, 42);
    EXPECT_FALSE(s.is_empty());
    EXPECT_FALSE(s.is_category2());
}

TEST(SlotTest, MakeIntNegative) {
    auto s = Slot::make_int(-1);
    EXPECT_EQ(s.value.i, -1);
}

TEST(SlotTest, MakeIntBoundary) {
    auto s_min = Slot::make_int(std::numeric_limits<std::int32_t>::min());
    auto s_max = Slot::make_int(std::numeric_limits<std::int32_t>::max());
    EXPECT_EQ(s_min.value.i, std::numeric_limits<std::int32_t>::min());
    EXPECT_EQ(s_max.value.i, std::numeric_limits<std::int32_t>::max());
}

TEST(SlotTest, MakeFloat) {
    auto s = Slot::make_float(3.14f);
    EXPECT_EQ(s.type, SlotType::Float);
    EXPECT_FLOAT_EQ(s.value.f, 3.14f);
    EXPECT_FALSE(s.is_category2());
}

TEST(SlotTest, MakeLong) {
    auto s = Slot::make_long(123456789012345LL);
    EXPECT_EQ(s.type, SlotType::Long);
    EXPECT_EQ(s.value.l, 123456789012345LL);
    EXPECT_TRUE(s.is_category2());
}

TEST(SlotTest, MakeDouble) {
    auto s = Slot::make_double(2.718281828);
    EXPECT_EQ(s.type, SlotType::Double);
    EXPECT_DOUBLE_EQ(s.value.d, 2.718281828);
    EXPECT_TRUE(s.is_category2());
}

TEST(SlotTest, MakeRef) {
    int dummy = 0;
    auto s = Slot::make_ref(&dummy);
    EXPECT_EQ(s.type, SlotType::Reference);
    EXPECT_EQ(s.value.ref, &dummy);
    EXPECT_FALSE(s.is_category2());
}

TEST(SlotTest, MakeRefNull) {
    auto s = Slot::make_ref(nullptr);
    EXPECT_EQ(s.type, SlotType::Reference);
    EXPECT_EQ(s.value.ref, nullptr);
}

TEST(SlotTest, MakeReturnAddress) {
    auto s = Slot::make_return_address(0x1234);
    EXPECT_EQ(s.type, SlotType::ReturnAddress);
    EXPECT_EQ(s.value.ret_addr, 0x1234u);
    EXPECT_FALSE(s.is_category2());
}

// ============================================================================
// §2.6.1 — Frame Local Variable Tests
// ============================================================================

TEST(FrameLocalsTest, SetGetInt) {
    auto frame = make_test_frame(4, 4);
    frame->set_local_int(0, 100);
    frame->set_local_int(3, -50);
    EXPECT_EQ(frame->get_local_int(0), 100);
    EXPECT_EQ(frame->get_local_int(3), -50);
}

TEST(FrameLocalsTest, SetGetFloat) {
    auto frame = make_test_frame(2, 2);
    frame->set_local_float(0, 1.5f);
    EXPECT_FLOAT_EQ(frame->get_local_float(0), 1.5f);
}

TEST(FrameLocalsTest, SetGetLongTwoSlots) {
    // §2.6.1: long occupies two consecutive local variable slots
    auto frame = make_test_frame(4, 2);
    frame->set_local_long(0, 9876543210LL);
    EXPECT_EQ(frame->get_local_long(0), 9876543210LL);

    // Slot [1] should be invalidated (Empty)
    EXPECT_THROW((void)frame->get_local_int(1), FrameError);
}

TEST(FrameLocalsTest, SetGetDoubleTwoSlots) {
    // §2.6.1: double occupies two consecutive local variable slots
    auto frame = make_test_frame(4, 2);
    frame->set_local_double(1, 3.14159265358979);
    EXPECT_DOUBLE_EQ(frame->get_local_double(1), 3.14159265358979);

    // Slot [2] should be invalidated
    EXPECT_THROW((void)frame->get_local_int(2), FrameError);
}

TEST(FrameLocalsTest, SetGetRef) {
    auto frame = make_test_frame(2, 2);
    int obj = 42;
    frame->set_local_ref(0, &obj);
    EXPECT_EQ(frame->get_local_ref(0), &obj);
}

TEST(FrameLocalsTest, OutOfBounds) {
    auto frame = make_test_frame(2, 2);
    EXPECT_THROW(frame->set_local_int(2, 0), FrameError);
    EXPECT_THROW((void)frame->get_local_int(5), FrameError);
}

TEST(FrameLocalsTest, LongAtLastSlotOverflow) {
    // Long at max_locals-1 should fail (needs index+1)
    auto frame = make_test_frame(3, 2);
    EXPECT_THROW(frame->set_local_long(2, 0LL), FrameError);
    // But at index 1 (needs 1 and 2) should succeed
    EXPECT_NO_THROW(frame->set_local_long(1, 42LL));
}

TEST(FrameLocalsTest, TypeMismatch) {
    auto frame = make_test_frame(2, 2);
    frame->set_local_int(0, 42);
    EXPECT_THROW((void)frame->get_local_float(0), FrameError);
    EXPECT_THROW((void)frame->get_local_long(0), FrameError);
    EXPECT_THROW((void)frame->get_local_ref(0), FrameError);
}

// ============================================================================
// §2.6.2 — Frame Operand Stack Tests
// ============================================================================

TEST(FrameStackTest, PushPopInt) {
    auto frame = make_test_frame(1, 4);
    frame->push_int(10);
    frame->push_int(20);
    EXPECT_EQ(frame->stack_depth(), 2u);
    EXPECT_EQ(frame->pop_int(), 20);  // LIFO
    EXPECT_EQ(frame->pop_int(), 10);
    EXPECT_TRUE(frame->stack_empty());
}

TEST(FrameStackTest, PushPopFloat) {
    auto frame = make_test_frame(1, 2);
    frame->push_float(1.5f);
    EXPECT_FLOAT_EQ(frame->pop_float(), 1.5f);
}

TEST(FrameStackTest, PushPopLong) {
    // §2.6.2: long counts as 2 depth units
    auto frame = make_test_frame(1, 4);
    frame->push_long(123456789012345LL);
    EXPECT_EQ(frame->stack_depth(), 2u);  // occupies 2 slots
    EXPECT_EQ(frame->pop_long(), 123456789012345LL);
    EXPECT_TRUE(frame->stack_empty());
}

TEST(FrameStackTest, PushPopDouble) {
    auto frame = make_test_frame(1, 4);
    frame->push_double(2.71828);
    EXPECT_EQ(frame->stack_depth(), 2u);
    EXPECT_DOUBLE_EQ(frame->pop_double(), 2.71828);
    EXPECT_TRUE(frame->stack_empty());
}

TEST(FrameStackTest, PushPopRef) {
    auto frame = make_test_frame(1, 2);
    int dummy = 0;
    frame->push_ref(&dummy);
    EXPECT_EQ(frame->pop_ref(), &dummy);
}

TEST(FrameStackTest, MixedTypes) {
    auto frame = make_test_frame(1, 8);
    frame->push_int(42);
    frame->push_long(100LL);    // 2 slots
    frame->push_float(1.0f);
    frame->push_double(2.0);    // 2 slots
    EXPECT_EQ(frame->stack_depth(), 6u);  // 1 + 2 + 1 + 2 = 6

    // Pop in reverse order (LIFO)
    EXPECT_DOUBLE_EQ(frame->pop_double(), 2.0);
    EXPECT_FLOAT_EQ(frame->pop_float(), 1.0f);
    EXPECT_EQ(frame->pop_long(), 100LL);
    EXPECT_EQ(frame->pop_int(), 42);
    EXPECT_TRUE(frame->stack_empty());
}

TEST(FrameStackTest, Overflow) {
    auto frame = make_test_frame(1, 2);
    frame->push_int(1);
    frame->push_int(2);
    EXPECT_THROW(frame->push_int(3), FrameError);
}

TEST(FrameStackTest, LongOverflow) {
    // Long needs 2 slots; stack of 1 should fail
    auto frame = make_test_frame(1, 1);
    EXPECT_THROW(frame->push_long(42LL), FrameError);
}

TEST(FrameStackTest, Underflow) {
    auto frame = make_test_frame(1, 2);
    EXPECT_THROW((void)frame->pop_int(), FrameError);
}

TEST(FrameStackTest, TypeMismatchOnPop) {
    auto frame = make_test_frame(1, 2);
    frame->push_int(42);
    EXPECT_THROW((void)frame->pop_float(), FrameError);
    // Stack should be unchanged after failed pop
    EXPECT_EQ(frame->stack_depth(), 1u);
    EXPECT_EQ(frame->pop_int(), 42);
}

TEST(FrameStackTest, PeekSlot) {
    auto frame = make_test_frame(1, 4);
    frame->push_int(10);
    frame->push_int(20);
    EXPECT_EQ(frame->peek_slot(0).value.i, 20);  // top
    EXPECT_EQ(frame->peek_slot(1).value.i, 10);  // second from top
    EXPECT_THROW((void)frame->peek_slot(2), FrameError);
}

TEST(FrameStackTest, PushPopRawSlot) {
    auto frame = make_test_frame(1, 4);
    auto slot = Slot::make_int(99);
    frame->push_slot(slot);
    EXPECT_EQ(frame->stack_depth(), 1u);
    auto popped = frame->pop_slot();
    EXPECT_EQ(popped.type, SlotType::Int);
    EXPECT_EQ(popped.value.i, 99);
}

// ============================================================================
// Frame PC / Bytecode Reader Tests
// ============================================================================

TEST(FramePCTest, DefaultPCIsZero) {
    auto frame = make_test_frame(1, 1);
    EXPECT_EQ(frame->pc(), 0u);
}

TEST(FramePCTest, SetAndAdvancePC) {
    auto frame = make_test_frame(1, 1);
    frame->set_pc(10);
    EXPECT_EQ(frame->pc(), 10u);
    frame->advance_pc(5);
    EXPECT_EQ(frame->pc(), 15u);
    frame->advance_pc(-3);
    EXPECT_EQ(frame->pc(), 12u);
}

// Bytecode reading tests need bytecode that outlives the frame
static std::vector<std::uint8_t> test_bytecode = {
    0x2A,                   // aload_0 (opcode 42)
    0x00, 0x0A,             // u2 = 10
    0xFF, 0xFE,             // s2 = -2
    0x00, 0x01, 0x02, 0x03  // s4 = 66051
};

TEST(FramePCTest, ReadU1) {
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 1, 1,
        std::span<const std::uint8_t>(test_bytecode));

    EXPECT_EQ(frame->read_u1(), 0x2A);
    EXPECT_EQ(frame->pc(), 1u);
}

TEST(FramePCTest, ReadU2) {
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 1, 1,
        std::span<const std::uint8_t>(test_bytecode));

    frame->set_pc(1);
    EXPECT_EQ(frame->read_u2(), 10u);
    EXPECT_EQ(frame->pc(), 3u);
}

TEST(FramePCTest, ReadS2) {
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 1, 1,
        std::span<const std::uint8_t>(test_bytecode));

    frame->set_pc(3);
    EXPECT_EQ(frame->read_s2(), -2);
    EXPECT_EQ(frame->pc(), 5u);
}

TEST(FramePCTest, ReadS4) {
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 1, 1,
        std::span<const std::uint8_t>(test_bytecode));

    frame->set_pc(5);
    EXPECT_EQ(frame->read_s4(), 0x00010203);
    EXPECT_EQ(frame->pc(), 9u);
}

TEST(FramePCTest, ReadPastEnd) {
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 1, 1,
        std::span<const std::uint8_t>(test_bytecode));

    frame->set_pc(static_cast<std::uint32_t>(test_bytecode.size()));
    EXPECT_THROW((void)frame->read_u1(), FrameError);
}

// ============================================================================
// §2.5.1 / §2.5.2 — JavaThread Tests
// ============================================================================

TEST(JavaThreadTest, DefaultConstruction) {
    JavaThread thread;
    EXPECT_EQ(thread.name(), "main");
    EXPECT_EQ(thread.state(), ThreadState::New);
    EXPECT_TRUE(thread.stack_empty());
    EXPECT_EQ(thread.frame_count(), 0u);
    EXPECT_EQ(thread.current_frame(), nullptr);
}

TEST(JavaThreadTest, NamedConstruction) {
    JavaThread thread("worker-1");
    EXPECT_EQ(thread.name(), "worker-1");
}

TEST(JavaThreadTest, PushPopFrame) {
    JavaThread thread;
    auto frame = make_test_frame(2, 4);
    auto* raw = frame.get();
    thread.push_frame(std::move(frame));

    EXPECT_EQ(thread.frame_count(), 1u);
    EXPECT_FALSE(thread.stack_empty());
    EXPECT_EQ(thread.current_frame(), raw);

    auto popped = thread.pop_frame();
    EXPECT_EQ(popped.get(), raw);
    EXPECT_TRUE(thread.stack_empty());
}

TEST(JavaThreadTest, NestedFrames) {
    JavaThread thread;
    auto f1 = make_test_frame(1, 1);
    auto f2 = make_test_frame(2, 2);
    auto* raw1 = f1.get();
    auto* raw2 = f2.get();

    thread.push_frame(std::move(f1));
    thread.push_frame(std::move(f2));

    EXPECT_EQ(thread.frame_count(), 2u);
    EXPECT_EQ(thread.current_frame(), raw2);  // top of stack

    thread.pop_frame();
    EXPECT_EQ(thread.current_frame(), raw1);  // previous frame restored
}

TEST(JavaThreadTest, StackOverflow) {
    JavaThread thread("test", 2);  // max 2 frames
    thread.push_frame(make_test_frame(1, 1));
    thread.push_frame(make_test_frame(1, 1));
    EXPECT_THROW(thread.push_frame(make_test_frame(1, 1)), StackOverflowError);
}

TEST(JavaThreadTest, PopEmptyStack) {
    JavaThread thread;
    EXPECT_THROW(thread.pop_frame(), StackOverflowError);
}

TEST(JavaThreadTest, AliveFlag) {
    JavaThread thread;
    EXPECT_EQ(thread.state(), ThreadState::New);
    EXPECT_FALSE(thread.is_alive());  // New state, not yet started
    thread.set_alive(true);
    EXPECT_TRUE(thread.is_alive());
    thread.set_alive(false);
    EXPECT_FALSE(thread.is_alive());
}

// ============================================================================
// §2.5.1 — JavaThread OS Thread Tests
// ============================================================================

TEST(JavaThreadTest, StartAndJoin) {
    JavaThread thread("worker");
    EXPECT_EQ(thread.state(), ThreadState::New);

    bool executed = false;
    thread.start([&executed]([[maybe_unused]] JavaThread& t) {
        executed = true;
    });

    thread.join();
    EXPECT_TRUE(executed);
    EXPECT_EQ(thread.state(), ThreadState::Terminated);
}

TEST(JavaThreadTest, StartWithBytecodeExecution) {
    // Run a simple bytecode program on a child OS thread
    static const std::vector<std::uint8_t> code = {
        0x08,  // iconst_5
        0x3C,  // istore_1
        0xB1   // return
    };

    JavaThread thread("bytecode-worker");
    auto frame = std::make_unique<Frame>(
        nullptr, nullptr, 2, 1,
        std::span<const std::uint8_t>(code));
    thread.push_frame(std::move(frame));

    bool completed = false;
    thread.start([&completed](JavaThread& t) {
        // Manual single-step execution
        auto* f = t.current_frame();
        ASSERT_NE(f, nullptr);
        // iconst_5
        auto op1 = f->read_u1();
        EXPECT_EQ(op1, 0x08);
        f->push_int(5);
        // istore_1
        auto op2 = f->read_u1();
        EXPECT_EQ(op2, 0x3C);
        f->set_local_int(1, f->pop_int());
        EXPECT_EQ(f->get_local_int(1), 5);
        // return
        auto op3 = f->read_u1();
        EXPECT_EQ(op3, 0xB1);
        (void)t.pop_frame();
        completed = true;
    });

    thread.join();
    EXPECT_TRUE(completed);
    EXPECT_TRUE(thread.stack_empty());
}

// ============================================================================
// Auto-GC Trigger Tests — Heap::should_gc()
// ============================================================================

TEST(HeapAutoGCTest, ShouldGcReturnsFalseWhenUnlimited) {
    // max_heap_size = 0 means unlimited — should never trigger auto-GC
    Heap heap(std::make_unique<NoOpGC>(), 0);
    for (int i = 0; i < 100; ++i) {
        heap.allocate_object("java/lang/Object");
    }
    EXPECT_FALSE(heap.should_gc());
}

TEST(HeapAutoGCTest, ShouldGcReturnsFalseBelowThreshold) {
    // max_heap_size large enough that a few objects don't exceed half
    // estimated_memory_usage = object_count * 256
    // Threshold = max_heap_size / 2
    // With 10 objects: 10 * 256 = 2560. Need max/2 > 2560 => max > 5120
    Heap heap(std::make_unique<SemiSpaceGC>(), 65536);
    for (int i = 0; i < 10; ++i) {
        heap.allocate_object("java/lang/Object");
    }
    EXPECT_FALSE(heap.should_gc());
}

TEST(HeapAutoGCTest, ShouldGcReturnsTrueAboveThreshold) {
    // max_heap_size = 4096 => threshold = 2048
    // Need enough objects so object_count * 256 > 2048 => > 8 objects
    Heap heap(std::make_unique<SemiSpaceGC>(), 4096);
    for (int i = 0; i < 10; ++i) {
        heap.allocate_object("java/lang/Object");
    }
    EXPECT_TRUE(heap.should_gc());
}

TEST(HeapAutoGCTest, ShouldGcReturnsFalseAfterGcWithNoNewAllocations) {
    // After GC runs, should_gc() returns false until new allocations happen
    Heap heap(std::make_unique<SemiSpaceGC>(), 4096);
    for (int i = 0; i < 10; ++i) {
        heap.allocate_object("java/lang/Object");
    }
    EXPECT_TRUE(heap.should_gc());

    // Run GC with no roots — all objects become garbage
    heap.gc({});

    // After GC, no new allocations => should_gc() returns false
    EXPECT_FALSE(heap.should_gc());
}

TEST(HeapAutoGCTest, ShouldGcReturnsTrueAfterNewAllocationsPostGc) {
    Heap heap(std::make_unique<SemiSpaceGC>(), 4096);
    for (int i = 0; i < 10; ++i) {
        heap.allocate_object("java/lang/Object");
    }

    // Run GC with no roots — clears all objects
    heap.gc({});
    EXPECT_FALSE(heap.should_gc());

    // Allocate again past threshold
    for (int i = 0; i < 10; ++i) {
        heap.allocate_object("java/lang/Object");
    }
    EXPECT_TRUE(heap.should_gc());
}

// ============================================================================
// Stop-The-World Safepoint Tests
// ============================================================================

TEST(SafepointSTWTest, RegisterAndUnregisterThread) {
    SafepointManager mgr;
    JavaThread t1("t1");
    JavaThread t2("t2");

    mgr.register_thread(&t1);
    mgr.register_thread(&t2);
    EXPECT_EQ(mgr.registered_threads().size(), 2u);

    mgr.unregister_thread(&t1);
    EXPECT_EQ(mgr.registered_threads().size(), 1u);
    EXPECT_EQ(mgr.registered_threads()[0], &t2);

    mgr.unregister_thread(&t2);
    EXPECT_TRUE(mgr.registered_threads().empty());
}

TEST(SafepointSTWTest, RequestSTWFromMutatorSingleThread) {
    // A single registered mutator thread calls request_stw with caller_is_mutator.
    // No other threads need to park; the STW work should execute immediately.
    SafepointManager mgr;
    JavaThread t1("main");
    mgr.register_thread(&t1);

    bool work_done = false;
    mgr.request_stw([&work_done]() {
        work_done = true;
    }, /*caller_is_mutator=*/true);

    EXPECT_TRUE(work_done);
    mgr.unregister_thread(&t1);
}

TEST(SafepointSTWTest, RequestSTWWithMultipleThreads) {
    // Simulate multi-threaded STW: register 2 threads, one requests STW,
    // the other parks via safepoint_poll.
    SafepointManager mgr;
    JavaThread t1("main");
    JavaThread t2("worker");

    mgr.register_thread(&t1);
    mgr.register_thread(&t2);

    std::atomic<bool> work_done{false};
    std::atomic<bool> worker_started{false};

    // Worker thread: polls safepoints until it sees work_done
    std::thread worker([&]() {
        worker_started.store(true);
        // Keep polling until the GC cycle completes
        while (!work_done.load()) {
            mgr.safepoint_poll();
        }
    });

    // Wait for worker to start
    while (!worker_started.load()) {
        std::this_thread::yield();
    }

    // Main thread requests STW — worker should park at safepoint_poll
    mgr.request_stw([&]() {
        // During STW, both threads should be accessible
        EXPECT_EQ(mgr.registered_threads().size(), 2u);
        work_done.store(true);
    }, /*caller_is_mutator=*/true);

    worker.join();
    EXPECT_TRUE(work_done.load());

    mgr.unregister_thread(&t1);
    mgr.unregister_thread(&t2);
}

TEST(SafepointSTWTest, STWCollectsRootsFromAllThreads) {
    // Verify that registered_threads() returns all threads during STW,
    // enabling root collection from all.
    SafepointManager mgr;
    Heap heap(std::make_unique<SemiSpaceGC>(), 65536);

    JavaThread t1("main");
    JavaThread t2("worker");
    mgr.register_thread(&t1);
    mgr.register_thread(&t2);

    std::vector<JavaThread*> seen_threads;
    std::atomic<bool> done{false};
    std::atomic<bool> worker_ready{false};

    std::thread worker([&]() {
        worker_ready.store(true);
        while (!done.load()) {
            mgr.safepoint_poll();
        }
    });

    while (!worker_ready.load()) {
        std::this_thread::yield();
    }

    mgr.request_stw([&]() {
        for (auto* t : mgr.registered_threads()) {
            seen_threads.push_back(t);
        }
        done.store(true);
    }, /*caller_is_mutator=*/true);

    worker.join();

    EXPECT_EQ(seen_threads.size(), 2u);
    // Both threads should be in the list (order not guaranteed)
    EXPECT_TRUE(std::find(seen_threads.begin(), seen_threads.end(), &t1) != seen_threads.end());
    EXPECT_TRUE(std::find(seen_threads.begin(), seen_threads.end(), &t2) != seen_threads.end());

    mgr.unregister_thread(&t1);
    mgr.unregister_thread(&t2);
}
