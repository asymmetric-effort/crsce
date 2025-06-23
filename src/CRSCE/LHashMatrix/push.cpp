/**
 * @file src/CRSCE/LHashMatrix/push.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include <format>

void LHashMatrix::push(CrossSumIndex r, CrossSumIndex c, bool bit_value) {
    bounds_check(r);
    bounds_check(c);

    if (row_position_data[r] >= s) {
        throw std::overflow_error(
            std::format(
                "Row overflow: more than s bits pushed. position={}",
                std::to_string(row_position_data[r])
            )
        );
    }

    row_buffer_data[r].set(c, bit_value);
    row_position_data[r]++; // track how many bits have been pushed

    // Automatically hash and store once row is full
    if (row_position_data[r] == s) {
        hash_and_store(r);
    }
}
