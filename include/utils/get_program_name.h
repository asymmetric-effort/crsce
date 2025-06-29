/**
* @file include/utils/get_program_name.h
 * @brief Return the program name as a std::string
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */
#pragma once

#include <string>
#include <filesystem>

namespace utils {
    /**
     * @name get_program_name
     * @brief Returns the program's basename from argv[0].
     * @param argv Array of C-style argument strings from main().
     * @return The program name (basename of argv[0]) or "program" if unavailable.
     */
    inline std::string get_program_name(const char* argv[]) {
        if (argv && argv[0]) {
            return std::filesystem::path(argv[0]).filename().string();
        }
        return "undefined";
    }
} // namespace utils
