/**
* @file include/Common/KernelId.h
 * @brief Declare a 64-bit unsigned KernelId for use in KernelManager
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <cstdint>

namespace Common {
    /**
     * @name KernelId
     * @brief Represents a GPU Kernel object
     * @ref docs/Gpu/Design/Gpu-KernelManager.md
     */
    using KernelId = uint64_t;
} // namespace Gpu
