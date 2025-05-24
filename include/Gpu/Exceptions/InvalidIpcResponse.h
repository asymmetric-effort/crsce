// file: include/Gpu/exceptions/InvalidIpcResponse.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::InvalidIpcResponse
     * @brief Thrown when an Invalid Gpu::Ipc::Response is encountered due to serialization or deserialization
     * @exception Gpu::Exception::InvalidIpcResponse
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class InvalidIpcResponse final : public std::runtime_error {
    public:
        explicit InvalidIpcResponse(const std::string& what_arg)
            : std::runtime_error("InvalidIpcResponse: " + what_arg) {}
    };

}
