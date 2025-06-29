/**
* @file include/utils/enum_ArgType.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

namespace utils {
    /**
     * @enum ArgType
     * @brief Enumerated type used to indicate whether an argument should be followed by a value or not.
     */
    enum class ArgType {
        NoValue,
        RequiredValue
    };

}
