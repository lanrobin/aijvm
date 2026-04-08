#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/lang/StringBuilder
void register_java_lang_StringBuilder(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
