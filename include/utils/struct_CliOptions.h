/**
* @file include/utils/struct_CliOptions.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "utils/enum_ArgType.h"
#include <functional>
#include <string>

namespace utils {
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
     * @name CliOptions
     * @brief a collection of command-line option (Utils::Option) descriptors
     */
    using cliOptions = std::vector<Option>;

}
