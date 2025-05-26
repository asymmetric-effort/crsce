/**
 * @file include/utils/getEnv/String.h
 * @brief Declare getEnv::Boolean to retrieve and validate a string environment variable.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
    /**
     * @brief Retrieves an environment variable as a string.
     *
     * If the variable is unset, returns defaultValue.
     */
    std::string String(const std::string& varName, const std::string& defaultValue = "");

} // namespace utils
