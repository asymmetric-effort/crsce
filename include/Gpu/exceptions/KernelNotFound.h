// file: include/Gpu/exceptions/KernelNotFound.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::KernelNotFound
     * @brief Thrown when a kernel ID is not found in the `Gpu::KernelManager`. Prevents invalid task launches.
     *        This derives from std::runtime_error
     * @exception Gpu::Exception::KernelNotFound
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class KernelNotFound final : public std::runtime_error {
    public:
        explicit KernelNotFound(const std::string& what_arg)
            : std::runtime_error("KernelNotFound: " + what_arg) {}
    };

}
