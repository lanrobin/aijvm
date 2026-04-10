When I run the aijvm with -Xmx20M of class [GCTest.clss](../tests/javaclasses/GCTest.class), it run into error:
Error: Object corruption detected at node 393000
Error: Object corruption detected at node 394000
Error: Object corruption detected at node 395000
Error: Object corruption detected at node 396000
Error: Object corruption detected at node 397000
Error: Object corruption detected at node 398000
Error: Object corruption detected at node 399000
Error: Object corruption detected at node 400000
Total survived nodes in linked list: 401
GC Test FAILED. Expected 41 nodes, found: 401

Can you help to fix it?

Following our rules, output ONLY the header definitions (`.hpp`) and brief architectural reasoning. Focus heavily on how the `ObjectHeader` accommodates the forwarding pointer, and how the cooperative STW handshake is synchronized. Do not write the full `.cpp` GC implementation yet.