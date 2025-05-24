// file: include/Gpu/Exceptions/IpcSendFailed.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Ipc/Result.h"
#include <stdexcept>
#include <string>
#include <format>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::IpcSendFailed
     * @brief Thrown when an IPC send operation fails unexpectedly.
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class IpcSendFailed final : public std::runtime_error {
    public:
        explicit IpcSendFailed(const Gpu::Ipc::Result &result)
            : std::runtime_error(std::format("IpcSendFailed: {}", result)) {
        }

        explicit IpcSendFailed(const std::string &what_arg)
            : std::runtime_error("IpcSendFailed: " + what_arg) {
        }
    };
} // namespace Gpu::Exceptions
