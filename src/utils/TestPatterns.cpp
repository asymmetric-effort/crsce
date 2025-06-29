/**
 * @file src/utils/TestPatterns.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/TestPatterns.h"

namespace utils {

    /**
     * @name all_zeros
     * @brief return false (0) to produce an all-zero test pattern
     * @param size_t is ignored
     * @param size_t is ignored
     * @return bool false
     */
    bool all_zeros(size_t, size_t) {
        return false;
    }
    /**
     * @name all_ones
     * @brief return true (1) to produce an all-ones test pattern
     * @param size_t is ignored
     * @param size_t is ignored
     * @return bool true
     */
    bool all_ones(size_t, size_t) {
        return true;
    }
    /**
     * @name all_ones
     * @brief return an alternating pattern of zeroes and ones.
     * @param row size_t
     * @param col size_t
     * @return bool true
     */
    bool checkerboard(const size_t row, const size_t col) {
        return (row + col) % 2 == 0;
    }

}
