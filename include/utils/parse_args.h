/**
 * @file include/utils/parse_args.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "utils/print_usage.h"
#include "utils/print_version.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace utils {

    enum class ArgType { NoValue, RequiredValue };

    struct Option {
        std::string long_name;          // e.g. "--in"
        char        short_name;         // e.g. 'i', or 0 if none
        ArgType     arg_type;           // NoValue vs. RequiredValue
        std::function<bool(const std::string&)> handler;
        // returns true on success; false => print usage & early-exit
    };

    /**
     * @name parse_args
     * @brief Generic argument parser over a user-supplied Option list.
     *
     * @param argc   From main().
     * @param argv   From main().
     * @param prog   Program name for usage prints.
     * @param opts   Vector of Option descriptors.
     * @return EXIT_SUCCESS (0) if parsing ended normally or after --help/--version,
     *         EXIT_FAILURE (non-zero) on parse error or missing required opts.
     */
    int parse_args(int argc,
                   const char* argv[],
                   const char* prog,
                   const std::vector<Option>& opts);
    }  // namespace utils

}  // namespace utils
