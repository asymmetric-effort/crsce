// file: include/utils/getEnv/String.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
    /**
     * @brief Retrieves an environment variable as a string.
     *
     * If the variable is unset, returns defaultValue.
     */
    std::string String(const std::string& varName, const std::string& defaultValue = "") {
        const char* env = std::getenv(varName.c_str());
        if (!env) return defaultValue;
        return std::string(env);
    }

} // namespace utils
