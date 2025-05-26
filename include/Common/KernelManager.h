/**
 * @file include/Common/KernelManager.h
 * @brief Declare and manage a GPU kernel blob manager which allows the consumer to register and manage GPU kernel
 *        binary code (blobs) for execution.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <unordered_map>
#include <mutex>
#include "Common/Buffer8.h"
#include "Common/KernelId.h"

namespace Gpu {
    /**
     * @name Gpu::KernelManager
     * @brief Tracks and manages GPU kernel blobs by ID.
     * @ref docs/Gpu/Design/Gpu-KernelManager.md
     *
     * Stores binary blobs indexed by kernel ID. Blobs are immutable and thread-safe.
     */
    class KernelManager final {
    public:

        KernelManager()=default;
        ~KernelManager()=default;

        bool registerKernel(Common::KernelId id, const Common::Buffer8& binary);
        bool has(Common::KernelId id) const;
        const Common::Buffer8& get(Common::KernelId id) const;
        bool erase(const Common::KernelId id);
        bool clear();

    private:
        mutable std::mutex mutex_;
        std::unordered_map<Common::KernelId, Common::Buffer8> table_;
    };

} // namespace Gpu
