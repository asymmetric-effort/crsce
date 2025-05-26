/**
 * @file include/utils/getEnv/Integer.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
    /**
     * @brief Retrieves an environment variable as an integer.
     *
     * Converts the value using std::stoi; on failure or if unset, returns defaultValue.
     */
    int Integer(const std::string& varName, int defaultValue = 0) {
        const char* env = std::getenv(varName.c_str());
        if (!env) return defaultValue;
        try {
            size_t idx;
            long val = std::stol(env, &idx);
            return static_cast<int>(val);
        } catch (...) {
            return defaultValue;
        }
    }

} // namespace getEnv

