/**
* @file include/Gpu/Exceptions/InvalidKernelBlob.h
 * @brief Declare a GPU Abstraction Layer Interface.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Gpu/Ipc/Result.h"
#include "utils/to_underlying.h"
#include <stdexcept>
#include <string>
#include <format>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::InvalidKernelBlob
     * @brief Thrown when an IPC result value is invalid
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class InvalidKernelBlob final : public std::runtime_error {
    public:
        explicit InvalidKernelBlob(const Gpu::Ipc::Result &result)
            : std::runtime_error(
                std::format("InvalidKernelBlob: {}",std::to_string(std::to_underlying(result)))) {
            /*noop*/
        }

        explicit InvalidKernelBlob(const std::string &what_arg)
            : std::runtime_error("InvalidKernelBlob: " + what_arg) {
            /*noop*/
        }
    };
} // namespace Gpu::Exceptions
