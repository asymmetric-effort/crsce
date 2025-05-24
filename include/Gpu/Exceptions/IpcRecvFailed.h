// file: include/Gpu/Exceptions/IpcRecvFailed.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Ipc/Result.h"
#include <stdexcept>
#include <string>
#include <format>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::IpcRecvFailed
     * @brief Thrown when an IPC receive operation fails unexpectedly.
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class IpcRecvFailed final : public std::runtime_error {
    public:
        explicit IpcRecvFailed(const Gpu::Ipc::Result &result)
            : std::runtime_error(std::format("IpcRecvFailed: {}", result)) {
        }

        explicit IpcRecvFailed(const std::string &what_arg)
            : std::runtime_error("IpcSendFailed: " + what_arg) {
        }
    };
} // namespace Gpu::Exceptions
