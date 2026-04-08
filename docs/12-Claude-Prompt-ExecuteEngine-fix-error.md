When I compile [HelloWorld.java](../tests/javaclasses/HelloAdd.java) with command "javac -XDstringConcat=inline HelloWorld.java" and then run the application, it report error:
[error] [main.cpp:41 main] Unexpected error: NativeMethodNotFoundError: java/lang/Class.desiredAssertionStatus0:(Ljava/lang/Class;)Z

Can you help to add the native method implement to fix the error util it runs successfully.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.