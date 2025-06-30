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
     *      When an argument is "Terminal" the argument will cause processing to terminate.
     *      For example, a --help, -h, -v or --version flag will process then terminate execution.
     */
    enum class ProcessingStyle {
        Semantic, // The argument has value
        Terminal, // The argument terminates execution
    };
}
