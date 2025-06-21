/**
* @file include/utils/Exceptions/FileOpenFailed.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once
#include <stdexcept>
#include <string>

namespace Exceptions {
    /**
     * @name Exceptions::FileOpenFailed
     * @brief Thrown on file open operation failure
     */
    class FileOpenFailed final : public std::runtime_error {
    public:
        explicit FileOpenFailed(const std::string &fileName)
            : std::runtime_error(std::format("file open failed for %s", fileName)) {
        }
    };
} // namespace Gpu::Exceptions
