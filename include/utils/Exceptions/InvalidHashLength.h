/**
 * @file include/utils/Exceptions/InvalidHashLength.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <stdexcept>
#include <string>
#include <format>

namespace Exceptions {
    /**
     * @name Exceptions::InvalidHashLength
     * @brief Thrown on invalid hash length in LHashMatrix::serialize
     */
    class InvalidHashLength final : public std::runtime_error {
    public:
        explicit InvalidHashLength(const size_t actual_size)
            : std::runtime_error(
                std::format(
                    "LHashMatrix::serialize() - Invalid hash length: {}",
                    std::to_string(actual_size)
                )
            ) {
        }
    };
} // namespace Gpu::Exceptions
