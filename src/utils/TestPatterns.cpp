/**
 * @file src/utils/TestPatterns.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/TestPatterns.h"

/**
 * @name all_zeros
 * @brief return false (representing a byte with all zeroes)
 * @param row size_t
 * @param col size_t
 * @return bool
 */
bool all_zeros(const size_t, const size_t) {
    return false;
}

/**
 * @name all_ones
 * @brief return true (representing a by te with all ones)
 * @param row size_t
 * @param col size_t
 * @return bool
 */
bool all_ones(const size_t, const size_t) {
    return true;
}

/**
 * @name checkerboard
 * @brief return an alternating pattern of 0s and 1s
 * @param row size_t
 * @param col size_t
 * @return
 */
bool checkerboard(const size_t row, const size_t col) {
    return (row + col) % 2 == 0;
}
