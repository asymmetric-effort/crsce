// file: src/Gpu/ThreadRegistry/empty.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/ThreadRegistry.h"

namespace Gpu {

    bool ThreadRegistry::empty() const {
        std::lock_guard lock(mutex_);
        return table_.empty();
    }

}
