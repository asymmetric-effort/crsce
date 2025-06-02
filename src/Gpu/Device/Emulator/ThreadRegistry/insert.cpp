/**
 * @file src/Gpu/ThreadRegistry/insert.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRegistry.h"
#include <stdexcept>
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name insert
     * @class ThreadRegistry
     * @public
     * @brief  Inserts a new kernel thread under a unique LaunchId. Takes ownership of the thread object.
     * @param id LaunchId
     * @param thread_id std::thread
     */
    void ThreadRegistry::insert(const LaunchId id, std::thread&& t) {
        std::lock_guard lock(mutex_);
        if (table_.contains(id)) {
            throw std::runtime_error("Gpu::ThreadRegistry::insert() - LaunchId already exists");
        }
        table_[id] = std::move(t);
    }

}
