/**
 * @file include/utils/generate_temp_filename.h
 * @brief Declare a function which will generate a temporary filename with a given prefix and extension.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include <string>

namespace utils {
    /**
     * @name generate_temp_filename
     * @brief Declare a function which will generate a temporary filename with a given prefix and extension.
     * @param prefix
     * @param ext
     * @return std::string
     */
    std::string generate_temp_filename(const std::string& prefix, const std::string& ext);

}
