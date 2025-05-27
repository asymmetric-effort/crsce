/**
 * @file include/utils/TestPatterns.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_UTILS_TEST_PATTERNS_H
#define CRSCE_UTILS_TEST_PATTERNS_H

#include <string>

using PatternFn = bool(*)(size_t row, size_t col);

bool all_zeros(const size_t, const size_t);

bool all_ones(const size_t, const size_t);

bool checkerboard(const size_t row, const size_t col);

struct TestPattern {
    std::string name;
    PatternFn generator;
};

#endif // CRSCE_UTILS_TEST_PATTERNS_H
