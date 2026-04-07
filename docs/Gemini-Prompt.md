我决定依赖Claude code AI 引擎来辅助我实现一个基本的JVM,以让我熟悉基于AI的编程的工作模式，要求如下：
1. 我要基于<The Java® Virtual Machine Specification>, Java SE 26 Edition来实现。
2. 我的开发环境是Windows下的VSCode + WSL + GitbHub Copilot with Claude Opus AI引擎。
3. 基于c++ std 20来开发，所以在实现跨平台(Windows/Linux/MacOS)的功能时，优先使用C++和标准库提供的函数和功能。
4. 项目要基于CMake以便实现跨平台的编译。
5.JVM要实现的主要功能有，类文件的加载解析、解析执行引擎、一个简单的Swap GC、多线程功能、能运行Console Java应用、和支持这些功能必要的其它功能。
基于以上这些需要，请为我提供一个详细的项目执行计划和项目配置。