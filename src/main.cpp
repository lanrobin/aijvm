#include <iostream>
#include "ClassFile.h"

int main()
{
#ifdef _WIN32
    const char* homeEnv = std::getenv("USERPROFILE");
#else
    const char* homeEnv = std::getenv("HOME");
#endif
    if (!homeEnv)
        throw std::runtime_error("Home directory environment variable not set");

    std::filesystem::path classPath =
        std::filesystem::path(homeEnv) / "aijvm/aijvm/tests/data/ArrayList.class";

    ClassReader reader(classPath);
    auto objectclz = reader.parse();
    std::cout << "ClassName: " << objectclz->major_version << std::endl;
    return 0;
}
