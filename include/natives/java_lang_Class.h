#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/lang/Class
void register_java_lang_Class(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
