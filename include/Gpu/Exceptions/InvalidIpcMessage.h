// file: include/Gpu/exceptions/InvalidIpcMessage.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::InvalidIpcMessage
     * @brief Thrown when an Invalid Gpu::Ipc::Message is encountered due to serialization or deserialization
     * @exception Gpu::Exception::InvalidIpcMessage
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class InvalidIpcMessage final : public std::runtime_error {
    public:
        explicit InvalidIpcMessage(const std::string& what_arg)
            : std::runtime_error("InvalidIpcMessage: " + what_arg) {}
    };

}
