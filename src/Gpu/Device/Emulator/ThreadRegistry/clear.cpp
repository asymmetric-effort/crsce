/**
 * @file src/Gpu/ThreadRegistry/clear.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRegistry.h"

namespace Gpu::Device {

    void ThreadRegistry::clear() {
        std::lock_guard lock(mutex_);
        table_.clear();  // Does not join threads. Dangerous if called prematurely.
    }

}
