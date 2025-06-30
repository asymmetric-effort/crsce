/**
 * @file include/utils/match_args.h
 * @brief Implements utils::parse_args().
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */
#pragma once

#include <string>

namespace utils {
    /**
     * @name match_args
     * @brief evaluate whether or not this_argument matches either long_arg or short_arg
     * @param this_argument std::string
     * @param long_arg std::string
     * @param short_arg const char
     * @return bool
     */
    inline bool match_args(const std::string& this_argument, const std::string& long_arg, const char short_arg) {
        return this_argument == long_arg || (short_arg && this_argument == std::string{"-"} + short_arg);
    }
}
