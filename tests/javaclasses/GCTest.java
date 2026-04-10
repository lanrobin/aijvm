public class GCTest {
    
    // Custom Node class containing primitives, references, and arrays.
    // This thoroughly tests if your GC can correctly scan internal object references.
    static class Node {
        int id;
        byte[] payload; // Bulk memory consumer to quickly trigger natural GC.
        Node next;      // Reference type to test Cheney's Breadth-First Search (BFS).

        public Node(int id, int size) {
            this.id = id;
            // Requires the 'newarray' bytecode implementation.
            this.payload = new byte[size]; 
        }
    }

    public static void main(String[] args) {
        System.out.println("Starting AIJVM GC Test...");

        // 1. Create a strong reference (GC Root).
        // This 'head' exists in the Local Variable Array of the main method's Frame.
        Node head = new Node(0, 10240); // 10KB
        Node current = head;

        System.out.println("Phase 1: Allocating objects to trigger natural GC...");
        
        // 2. Loop object allocation to intentionally fill memory.
        // Assuming -Xmx10M (From-Space is 5M), this loop is enough to trigger natural GC multiple times.
        for (int i = 1; i <= 400000; i++) {
            
            if (i % 1000 == 0) {
                // Keep one object alive every 1000 iterations by appending it to the linked list.
                current.next = new Node(i, 10240); // 10KB
                current = current.next;
                System.out.println("Kept alive node id: " + i);
            } else {
                // Most objects become garbage immediately after creation.
                // No GC Roots point to them, so they will be abandoned in From-Space 
                // and will NOT be copied to To-Space.
                Node garbage = new Node(-1, 256);
            }
        }
        System.out.println("Phase 1: Natural allocation finished.");

        // 3. Explicitly trigger system GC.
        System.out.println("Phase 2: Explicitly calling System.gc()...");
        System.gc(); // This should trigger 'invokestatic java/lang/System.gc()'.
        System.out.println("System.gc() call completed.");

        // 4. Final Verification: Traverse surviving objects.
        // If objects were moved to To-Space but their forwarding pointers weren't updated, 
        // this loop will cause a Segfault or read garbage data in C++.
        System.out.println("Phase 3: Verifying survived objects...");
        int count = 0;
        Node temp = head;
        while (temp != null) {
            count++;
            // If payload.length throws an error or holds an invalid value, 
            // the array object header was corrupted during the Cheney copy phase.
            if (temp.payload.length != 10240) {
                System.out.println("Error: Object corruption detected at node " + temp.id);
            }
            temp = temp.next;
        }
        
        System.out.println("Total survived nodes in linked list: " + count);
        
        // Expected output: 1 (head) + (400000 / 1000) = 401 nodes.
        if (count == 401) {
            System.out.println("GC Test Finished Successfully! Cheney Algorithm is solid.");
        } else {
            System.out.println("GC Test FAILED. Expected 401 nodes, found: " + count);
        }
    }
}