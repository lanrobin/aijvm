#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/lang/Thread
void register_java_lang_Thread(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
