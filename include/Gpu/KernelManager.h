// file: include/Gpu/KernelManager.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <unordered_map>
#include <mutex>
#include <cstdint>
#include "Gpu/Common/Buffer8.h"

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
        using KernelId = uint64_t;

        KernelManager()=default;
        ~KernelManager()=default;

        bool registerKernel(KernelId id, const Common::Buffer8& binary);
        bool has(KernelId id) const;
        const Common::Buffer8& get(KernelId id) const;
        bool erase(const KernelId id);
        bool clear();

    private:
        mutable std::mutex mutex_;
        std::unordered_map<KernelId, Common::Buffer8> table_;
    };

} // namespace Gpu
