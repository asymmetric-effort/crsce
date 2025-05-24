// file: include/Gpu/exceptions/MatrixOutOfRange.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <stdexcept>
#include <string>

namespace Gpu::Exceptions {
    /**
     * @name Gpu::Exceptions::MatrixOutOfRange
     * @brief Throws `Gpu::MatrixOutOfRange` when index is out of range. This derives from std::runtime_error
     * @exception Gpu::Exception::MatrixOutOfRange
     * @ref docs/Gpu/Design/Gpu-Exceptions.md
     */
    class MatrixOutOfRange final : public std::runtime_error {
    public:
        explicit MatrixOutOfRange(const std::string& what_arg)
            : std::runtime_error("MatrixOutOfRange: " + what_arg) {}
    };

}
