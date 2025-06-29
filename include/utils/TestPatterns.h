/**
 * @file include/utils/TestPatterns.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <string>

namespace utils {
    using PatternFn = bool(*)(size_t row, size_t col);

    bool all_zeros(size_t, size_t);
    bool all_ones(size_t, size_t);
    bool checkerboard(size_t row, size_t col);

    struct TestPattern {
        std::string name;
        PatternFn generator;
    };

}
