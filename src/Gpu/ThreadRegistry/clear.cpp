// file: src/Gpu/ThreadRegistry/clear.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/ThreadRegistry.h"

namespace Gpu {

    void ThreadRegistry::clear() {
        std::lock_guard lock(mutex_);
        table_.clear();  // Does not join threads. Dangerous if called prematurely.
    }

}
