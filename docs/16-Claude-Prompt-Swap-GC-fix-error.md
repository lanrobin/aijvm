When I compile [GCTest.java](../tests/javaclasses/GCTest.java) with command "javac -XDstringConcat=inline GCTest.java" and then run the application, it report error:
Phase 1: Natural allocation finished.
Phase 2: Explicitly calling System.gc()...
terminate called after throwing an instance of 'aijvm::runtime::FrameError'
  what():  push_ref: operand stack overflow

Can you help to fix the error util it runs successfully.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.