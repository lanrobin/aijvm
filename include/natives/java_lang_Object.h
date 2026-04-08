#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/lang/Object
void register_java_lang_Object(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
