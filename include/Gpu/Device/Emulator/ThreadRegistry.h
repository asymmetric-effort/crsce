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
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name LaunchId
     * @brief 32-bit identifier representing an execution thread
     */
    using LaunchId = uint32_t;
    /**
     * @class Gpu::ThreadRegistry
     * @brief Tracks lifecycle of detached kernel threads for concurrent GPU emulation.
     * @ref docs/Gpu/Design/Gpu-ThreadRegistry.md
     */
    class ThreadRegistry final {
    public:
        /**
         * @name insert
         * @class ThreadRegistry
         * @public
         * @brief  Inserts a new kernel thread under a unique LaunchId. Takes ownership of the thread object.
         * @param id LaunchId
         * @param thread_id std::thread
         */
        void insert(LaunchId id, std::thread&& thread_id);

        /**
         * @name joinAll
         * @class ThreadRegistry
         * @public
         * @brief Joins all registered threads and clears the table.
         */
        void joinAll();

        /**
         * @name clear
         * @class ThreadRegistry
         * @public
         * @brief Clears thread map without joining. Use with caution.
         */
        void clear();

        /**
         * @name empty
         * @class ThreadRegistry
         * @public
         * @brief Checks if the registry is empty.
         * @return bool
         */
        bool empty() const;

    private:
        /**
         * @property mutex_
         * @private
         * @brief mutex lock
         */
        mutable std::mutex mutex_;
        /**
         * @property table
         * @private
         * @brief a table of launchIds and threads
         */
        std::unordered_map<LaunchId, std::thread> table_;
    };

} // namespace Gpu
