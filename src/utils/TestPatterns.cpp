/**
 * @file src/utils/TestPatterns.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/TestPatterns.h"

bool all_zeros(size_t, size_t) {
    return false;
}

bool all_ones(size_t, size_t) {
    return true;
}

bool checkerboard(size_t row, size_t col) {
    return (row + col) % 2 == 0;
}
