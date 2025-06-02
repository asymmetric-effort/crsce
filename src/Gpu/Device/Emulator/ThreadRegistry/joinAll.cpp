/**
 * @file src/Gpu/ThreadRegistry/joinAll.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <ranges>

#include "Gpu/Device/Emulator/ThreadRegistry.h"
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name joinAll
     * @class ThreadRegistry
     * @public
     * @brief Joins all registered threads and clears the table.
     */
    void ThreadRegistry::joinAll() {

        std::lock_guard lock(mutex_);

        for (auto &thread: table_ | std::views::values) {

            if (thread.joinable())
                thread.join();

        }

        table_.clear();

    }

}
