#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/lang/System
void register_java_lang_System(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
