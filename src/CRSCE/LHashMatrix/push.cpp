/**
 * @file src/CRSCE/LHashMatrix/push.cpp
 * @brief Define a one-dimensional matrix of row-aligned hashes.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
/**
 * @name push
 * @class LHashMatrix
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @param bit_value bool
 * @brief push value 'bit_value' to position (r,c)
 */
void LHashMatrix::push(const CrossSumIndex r, const CrossSumIndex c, const bool bit_value) {
    bounds_check(r);
    bounds_check(c);

    if (row_positions[r] >= s) {
        throw std::overflow_error(
            "Row overflow: more than s bits pushed. position=" +
            std::to_string(row_positions[r])
        );
    }

    row_buffers[r].set(c, bit_value);
    row_positions[r]++;  // track how many bits have been pushed

    // Automatically hash and store once row is full
    if (row_positions[r] == s) {
        hash_and_store(r);
    }
}
