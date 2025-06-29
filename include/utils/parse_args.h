/**
 * @file include/utils/parse_args.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <string>
#include <vector>
#include <functional>

namespace utils {
    /**
     * @enum ArgType
     * @brief Enumerated type used to indicate whether an argument should be followed by a value or not.
     */
    enum class ArgType {
        NoValue,
        RequiredValue
    };

    /**
     * @struct Option
     * @brief Create reusable structure used to define cli arguments for parse_args.
     */
    struct Option {
        /**
         * @name long_name
         * @brief cli argument using --long pattern
         */
        std::string long_name;
        /**
         * @name short_name
         * @brief cli argument using -a short pattern.  It is null (0x00) if no short argument is specified.
         */
        char short_name;
        /**
         * @name arg_type
         * @brief enumerated type representing whether or not the argument has a value
         */
        ArgType arg_type; // NoValue vs. RequiredValue
        /**
         * @name handler
         * @brief A function used to process an argument when discovered. See parse_args().
         * @param std::string represents the evaluated value
         * @returns bool returns true on success; false => print usage & early-exit
         */
        std::function<bool(const std::string&)> handler;
    };

    /**
     * @function parse_args
     * @brief Generic argument parser over a user-supplied Option list.
     *
     * @param argc   From main().
     * @param argv   From main().
     * @param opts   Vector of Option descriptors.
     * @return EXIT_SUCCESS (0) if parsing ended normally or after --help/--version,
     *         EXIT_FAILURE (non-zero) on parse error or missing required opts.
     */
    int parse_args(const int argc,
                   const char* argv[],
                   const std::vector<Option>& opts);
} // namespace utils
