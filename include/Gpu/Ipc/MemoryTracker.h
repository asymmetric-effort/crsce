/**
 * @file include/Gpu/Ipc/MemoryTracker.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <unordered_map>
#include <vector>
#include <mutex>
#include <random>
#include "Common/AbstractPtr.h"
#include "Common/Buffer8.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::MemoryTracker
     * @brief Tracks pseudo-device memory allocations using AbstractPtr handles.
     * @ref docs/Gpu/Design/Gpu-Ipc-MemoryTracker.md
     *
     * This class emulates a memory allocator for the GPU abstraction layer. It generates opaque
     * 64-bit memory handles (AbstractPtr), maps them to host-side buffers, and supports safe read/write.
     *
     * Notes:
     *  - Uses std::mt19937_64 to avoid sequential AbstractPtr leakage
     *  - Internally thread-safe via std::mutex
     *  - Header-only for now; .cpp will be needed to define generateUniqueHandle() and method logic
     */
    class MemoryTracker final {
    public:
        /**
         * @name constructor
         * @class MemoryTracker
         * @public
         * @brief initialize the class
         */
        MemoryTracker();

        /**
         * @name destructor
         * @class MemoryTracker
         * @public
         * @brief tear-down the class
         */
        ~MemoryTracker() = default;

        /**
         * @name alloc
         * @class MemoryTracker
         * @public
         * @brief Allocate a buffer of `size` bytes and return a new AbstractPtr handle.
         */
        Common::AbstractPtr alloc(std::size_t size);

        /**
         * @name free
         * @class MemoryTracker
         * @public
         * @brief Free the memory associated with the given AbstractPtr.
         * @return true if the pointer was valid and freed.
         */
        bool free(Common::AbstractPtr ptr);

        /**
         * @name write
         * @class MemoryTracker
         * @public
         * @brief Write data into the buffer identified by AbstractPtr.
         * @param dst Common::AbstractPtr
         * @param src Common::Buffer8
         * @return bool - true on success, false if the pointer is invalid or size mismatch.
         */
        bool write(Common::AbstractPtr dst, const Common::Buffer8 &src);

        /**
         * @name read
         * @class MemoryTracker
         * @public
         * @brief Read data out of the buffer identified by AbstractPtr.
         * @param src Common::AbstractPtr
         * @param dst Common::Buffer8
         * @return bool - true on success, false if the pointer is invalid or size mismatch.
         */
        bool read(Common::AbstractPtr src, Common::Buffer8 &dst) const;

        /**
         * @name clear
         * @class MemoryTracker
         * @public
         * @brief Clear all allocations (used during reset).
         */
        void clear();

    private:
        /**
         * @property table_
         * @private
         * @brief a table of allocated memory objects mapping an abstract identifier to the memory object.
         */
        std::unordered_map<Common::AbstractPtr, Common::Buffer8> table_;
        /**
         * @property mutex_
         * @private
         * @brief a mutex lock for thread safety
         */
        mutable std::mutex mutex_;
        /**
         * @property prng_
         * @private
         * @brief random number generator
         */
        std::mt19937_64 prng_;

        /**
         * @property generateUniqueHandle
         * @private
         * @return Common::AbstractPtr
         */
        Common::AbstractPtr generateUniqueHandle();
    };
} // namespace Gpu::Ipc
