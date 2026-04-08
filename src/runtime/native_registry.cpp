#include "runtime/native_registry.h"

namespace aijvm::runtime {

void NativeMethodRegistry::register_method(const std::string& key, NativeMethodFn fn) {
    methods_[key] = std::move(fn);
}

const NativeMethodFn* NativeMethodRegistry::find(const std::string& key) const {
    auto it = methods_.find(key);
    return it != methods_.end() ? &it->second : nullptr;
}

bool NativeMethodRegistry::has(const std::string& key) const {
    return methods_.contains(key);
}

std::string NativeMethodRegistry::make_key(std::string_view class_name,
                                           std::string_view method_name,
                                           std::string_view descriptor) {
    std::string key;
    key.reserve(class_name.size() + 1 + method_name.size() + 1 + descriptor.size());
    key += class_name;
    key += '.';
    key += method_name;
    key += ':';
    key += descriptor;
    return key;
}

void NativeMethodRegistry::register_defaults() {
    // All built-in native bindings are registered here via their
    // per-class registration functions. Add new classes below.
    // (Actual registration is done in JVMEngine to avoid circular deps)
}

} // namespace aijvm::runtime
