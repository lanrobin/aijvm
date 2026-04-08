#pragma once

#include "runtime/native_registry.h"

namespace aijvm::natives {

/// Register native methods for java/io/PrintStream
void register_java_io_PrintStream(aijvm::runtime::NativeMethodRegistry& registry);

} // namespace aijvm::natives
