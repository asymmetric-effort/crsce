/**
 * @file include/Gpu/ThreadRegistry.h
 * @brief Declare the class that tracks lifecycle of detached kernel threads for concurrent GPU emulation.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <unordered_map>
#include <thread>
#include <mutex>
#include <cstdint>

namespace Gpu::Device {

    /**
     * @name Gpu::ThreadRegistry
     * @brief Tracks lifecycle of detached kernel threads for concurrent GPU emulation.
     * @ref docs/Gpu/Design/Gpu-ThreadRegistry.md
     */
    class ThreadRegistry final {
    public:
        using LaunchId = uint32_t;

        /**
         * Inserts a new kernel thread under a unique LaunchId.
         * Takes ownership of the thread object.
         */
        void insert(LaunchId id, std::jthread&& t);

        /**
         * Joins all registered threads and clears the table.
         */
        void joinAll();

        /**
         * Clears thread map without joining. Use with caution.
         */
        void clear();

        /**
         * Checks if the registry is empty.
         */
        bool empty() const;

    private:
        mutable std::mutex mutex_;
        std::unordered_map<LaunchId, std::jthread> table_;
    };

} // namespace Gpu
