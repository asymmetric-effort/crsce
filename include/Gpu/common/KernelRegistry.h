// file: include/Gpu/common/KernelRegistry.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/common/Kernel.h"
#include "Gpu/common/KernelId.h"
#include <memory>
#include <unordered_map>

namespace Gpu {

/**
 * @brief A registry mapping KernelId values to concrete Kernel implementations.
 *
 * This allows backends (Emulator, CUDA, Metal, etc.) to register their versions
 * of each kernel once, and then dispatch via polymorphism in a unified way.
 */
class KernelRegistry {
public:
    /// Get the singleton instance of the registry.
    static KernelRegistry& instance();

    /**
     * @brief Register a concrete Kernel for the given id.
     * @param id     Identifier of the kernel (e.g. KernelId::Increment).
     * @param kernel Pointer to a newly-allocated Kernel; ownership is transferred.
     */
    void registerKernel(KernelId id, Kernel* kernel);

    /**
     * @brief Retrieve the Kernel implementation for the given id.
     * @param id     Identifier of the kernel to fetch.
     * @return       Pointer to the Kernel if registered, or nullptr otherwise.
     */
    Kernel* get(KernelId id) const;

private:
    KernelRegistry() = default;
    KernelRegistry(const KernelRegistry&) = delete;
    KernelRegistry& operator=(const KernelRegistry&) = delete;

    std::unordered_map<KernelId, std::unique_ptr<Kernel>> table_;
};

} // namespace Gpu
