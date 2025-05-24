// file: include/Gpu/Exceptions/InvalidIpcResult.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Ipc/Result.h"
#include <stdexcept>
#include <string>
#include <format>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::InvalidIpcResult
     * @brief Thrown when an IPC result value is invalid
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class InvalidIpcResult final : public std::runtime_error {
    public:
        explicit InvalidIpcResult(const Gpu::Ipc::Result &result)
            : std::runtime_error(
                std::format(
                    "InvalidIpcResult: {}",
                    std::to_string(
                        static_cast<uint8_t>(result)
                    )
                )
            ) {
        }

        explicit InvalidIpcResult(const std::string &what_arg)
            : std::runtime_error("InvalidIpcResult: " + what_arg) {
        }
    };
} // namespace Gpu::Exceptions
