When I compile [ProduceConsumer.java](../tests/javaclasses/ProduceConsumer.java) with command "javac -XDstringConcat=inline ProduceConsumer.java" and then run the application, it report error:
terminate called after throwing an instance of 'aijvm::runtime::FrameError'
  what():  push_int: operand stack overflow in file frame.cpp line 133

Can you help to fix the error util it runs successfully.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.