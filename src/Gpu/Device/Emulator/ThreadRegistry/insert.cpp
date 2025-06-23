/**
 * @file src/Gpu/ThreadRegistry/insert.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRegistry.h"
#include <stdexcept>

namespace Gpu::Device {

    void ThreadRegistry::insert(const LaunchId id, std::jthread&& t) {
        std::lock_guard lock(mutex_);
        if (table_.contains(id)) {
            throw std::runtime_error("Gpu::ThreadRegistry::insert() - LaunchId already exists");
        }
        table_[id] = std::move(t);
    }

}
