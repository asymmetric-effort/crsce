// file: src/utils/getEnv/Boolean.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdlib>
#include <string>
#include <algorithm>

namespace getEnv {
    bool Boolean(const std::string& varName, bool defaultValue = false) {
        const char* env = std::getenv(varName.c_str());
        if (!env) return defaultValue;
        std::string s(env);
        // Convert to lowercase for case-insensitive comparison
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
        if (s == "true")  return true;
        if (s == "false") return false;
        return defaultValue;
    }

} // namespace getEnv
