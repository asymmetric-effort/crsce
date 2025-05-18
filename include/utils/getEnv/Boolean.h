// file: include/utils/getEnv/Boolean.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {

    /**
     * @brief Retrieves an environment variable and interprets it as a boolean.
     *
     * Matches (case-insensitive): "true" => true, "false" => false.
     * If the variable is not set or has any other value, returns defaultValue.
     *
     * @param varName       Name of the environment variable.
     * @param defaultValue  Value to return if variable is unset or unrecognized.
     * @return Parsed boolean or defaultValue.
     */
    bool Boolean(const std::string& varName, bool defaultValue = false);

} // namespace getEnv
