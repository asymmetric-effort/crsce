/**
 * @file include/Gpu/exceptions/DeviceNotReady.h
 * @brief Declare a GPU Abstraction Layer Interface.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::DeviceNotReady
     * @brief Thrown when any GPU operation is invoked before `init()` or after `shutdown()`.
     *        Ensures correct lifecycle. This derives from std::runtime_error.
     * @exception Gpu::Exception::DeviceNotReady
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class DeviceNotReady final : public std::runtime_error {
    public:
        explicit DeviceNotReady(const std::string& what_arg)
            : std::runtime_error("DeviceNotReady: " + what_arg) {}
    };

}
