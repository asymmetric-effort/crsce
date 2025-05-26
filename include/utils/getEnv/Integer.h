/**
 * @file include/utils/getEnv/Integer.h
 * @brief Declare getEnv::Boolean to retrieve and validate an integer environment variable.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
/**
 * @brief Retrieves an environment variable as an integer.
 *
 * Converts the value using std::stoi; on failure or if unset, returns defaultValue.
 */
int Integer(const std::string& varName, int defaultValue = 0);

} // namespace getEnv
