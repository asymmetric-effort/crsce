// file: include/Gpu/exceptions/KernelNotFound.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {

    class KernelNotFound final : public std::runtime_error {
    public:
        explicit KernelNotFound(const std::string& what_arg)
            : std::runtime_error("KernelNotFound: " + what_arg) {}
    };

}
