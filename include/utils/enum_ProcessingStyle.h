/**
 * @file include/utils/enum_ProcessingStyle.h
 * @brief Define an enum type indicating how a cli argument is processed
 * @copyright
 */
#pragma once

namespace utils {
    /**
     * @enum ProcessingStyle
     * @brief Indicates how a cli argument is processed
     * @details
     *      When an argument is "Terminate" the argument will cause processing to terminate.
     *      For example, a --help, -h, -v or --version flag will process then terminate execution.
     *
     *      An argument with a "HasValue" ProcessingStyle will be evaluated for its meaning and then
     *      allow execution to continue to the next argument.
     */
    enum class ProcessingStyle {
        HasValue,
        Terminate,
    };
}
