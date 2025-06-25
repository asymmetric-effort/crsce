/**
* @file include/Gpu/Common/KernelDescriptor.h
 * @brief Define the KernelDescriptor used by Ipc and Gpu::Device
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

namespace Common {
    /**
     * @name KernelDescriptor
     * @brief A struct that describes a single kernel object registered with the GPU controller
     */
    struct KernelDescriptor {
        uint64_t kernel_id; // pseudo-random identifier
        uint64_t size; // kernel blob size
        Common::AbstractPtr ptr; // starting address of kernel blob
        std::array<uint8_t,32> id; // kernel hash
    };
}
