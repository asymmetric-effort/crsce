/**
 * @file include/Gpu/Ipc/MemoryTracker.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <mutex>
#include <random>
#include "Common/AbstractPtr.h"
#include "Common/Buffer8.h"

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
        MemoryTracker();

        /**
         * Allocate a buffer of `size` bytes and return a new AbstractPtr handle.
         */
        Common::AbstractPtr alloc(std::size_t size);

        /**
         * Free the memory associated with the given AbstractPtr.
         * Returns true if the pointer was valid and freed.
         */
        bool free(Common::AbstractPtr ptr);

        /**
         * Write data into the buffer identified by AbstractPtr.
         * Returns true on success, false if the pointer is invalid or size mismatch.
         */
        bool write(Common::AbstractPtr dst, const Common::Buffer8& src);

        /**
         * Read data out of the buffer identified by AbstractPtr.
         * Returns true on success, false if the pointer is invalid or size mismatch.
         */
        bool read(Common::AbstractPtr src, Common::Buffer8& dst) const;

        /**
         * Clear all allocations (used during reset).
         */
        void clear();

    private:
        std::unordered_map<Common::AbstractPtr, Common::Buffer8> table_;
        mutable std::mutex mutex_;
        std::mt19937_64 prng_;
        Common::AbstractPtr generateUniqueHandle();
    };

} // namespace Gpu::Ipc
