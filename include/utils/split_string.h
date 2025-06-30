/**
* @file include/utils/split_string.h
 * @brief Split a string into a vector of substrings by a delimiter
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */
#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace utils {
    /**
     * @name split_string
     * @brief Splits `s` on each occurrence of `delim` and returns the parts.
     * @param s     The input string to split.
     * @param delim The character to split on.
     * @return A vector of substrings (empty substrings are included if delimiters are consecutive or at ends).
     */
    inline std::vector<std::string> split_string(const std::string& s, char delim) {
        std::vector<std::string> parts;
        std::string item;
        std::istringstream stream(s);
        while (std::getline(stream, item, delim)) {
            parts.push_back(item);
        }
        return parts;
    }
}
