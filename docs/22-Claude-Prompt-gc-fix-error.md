When I run the aijvm with -Xmx20M of class [GCTest.clss](../tests/javaclasses/GCTest.class), it run into error:
Kept alive node id: 343000
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc

Can you help to fix it?

Following our rules, output ONLY the header definitions (`.hpp`) and brief architectural reasoning. Focus heavily on how the `ObjectHeader` accommodates the forwarding pointer, and how the cooperative STW handshake is synchronized. Do not write the full `.cpp` GC implementation yet.