/**
 * @file src/utils/getEnv/Boolean.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
    bool Boolean(const std::string &varName, bool defaultValue = false) {
        const char *env = std::getenv(varName.c_str());
        if (!env) return defaultValue;
        std::string s(env);

        // Convert to lowercase for case-insensitive comparison
        std::ranges::transform(
            s,
            s.begin(),
            [](const unsigned char c) {
                return std::tolower(c);
            });

        if (s == "true") return true;
        if (s == "false") return false;
        return defaultValue;
    }
} // namespace getEnv
