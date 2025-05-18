// file: include/Gpu/Kernel.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/KernelId.h"

namespace Gpu {

    /// Base class for all kernels; each backend registers concrete Kernel implementations
    class Kernel {
    public:
        virtual ~Kernel() = default;
        /// Execute kernel logic on the given device pointer and element count
        virtual void run(void* buffer, std::size_t count) = 0;
    };

    /// Factory/registry for kernels
    class KernelRegistry {
    public:
        static KernelRegistry& instance();

        /// Register a kernel implementation for a given id
        void registerKernel(KernelId id, Kernel* kernel);

        /// Retrieve kernel by id, or nullptr if not found
        Kernel* get(KernelId id) const;

    private:
        KernelRegistry() = default;
        std::unordered_map<KernelId, std::unique_ptr<Kernel>> table_;
    };

} // namespace Gpu
