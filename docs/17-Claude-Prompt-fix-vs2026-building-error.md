When I try to compile this project in Windows VSCode, it says:

PS E:\github\aijvm> cd .\build\
PS E:\github\aijvm\build> cmake ..
cmake : The term 'cmake' is not recognized as the name of a cmdlet, function, script file, or operable program. Check the spelling of the name, or if a path was included, verify that the path is correct and try again.
At line:1 char:1
+ cmake ..
+ ~~~~~
    + CategoryInfo          : ObjectNotFound: (cmake:String) [], CommandNotFoundException
    + FullyQualifiedErrorId : CommandNotFoundException
 
PS E:\github\aijvm\build> cd ..
PS E:\github\aijvm> 

Can you help to fix the build error util it build successfully on both Windows and Linux.

Following our `claude.md` rules, please provide ONLY the header definitions (`.hpp`) and brief architectural explanations first. Do not implement the full `.cpp` loops yet. I want to review the exact state machine and frame-pushing contract first.