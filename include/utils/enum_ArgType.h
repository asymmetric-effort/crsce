/**
 * @file include/utils/enum_ArgType.h
 * @brief Enumerated type used to indicate whether an argument should be followed by a value or not.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

namespace utils {
    /**
     * @enum ArgType
     * @brief Enumerated type used to indicate whether an argument should be followed by a value or not.
     */
    enum class ArgType {
        NoValue, // Flag has no value (e.g. --debug) which will continue processing.
        RequiredValue, // RequireValue has value (e.g. --file my_file.txt) which will continue processing.
        Terminate, // Terminate has no value and will cause parse_arg() to terminate (e.g. --help, --version)
    };
}
