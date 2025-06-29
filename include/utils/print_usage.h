/**
 * @file include/utils/print_usage.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#ifndef UTILS_PRINT_USAGE_H
#define UTILS_PRINT_USAGE_H

#include <string>
#include <iostream>

namespace utils {
    int print_usage(const std::string& programName, const int exit_code=EXIT_SUCCESS);
}

#endif // UTILS_PRINT_USAGE_H
