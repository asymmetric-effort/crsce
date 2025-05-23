// file: include/Gpu/exceptions/DeviceNotReady.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {

    class DeviceNotReady final : public std::runtime_error {
    public:
        explicit DeviceNotReady(const std::string& what_arg)
            : std::runtime_error("DeviceNotReady: " + what_arg) {}
    };

}
