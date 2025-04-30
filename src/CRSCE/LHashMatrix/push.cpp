// file: src/CRSCE/LHashMatrix/push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"

void LHashMatrix::push(CrossSumIndex r, CrossSumIndex c, bool bit_value) {
    bounds_check(r);
    bounds_check(c);

    if (row_buffers[r].count() >= s) {
        throw std::overflow_error(
            "Row overflow: more than s bits pushed. sz=" +
            std::to_string(row_buffers[r].count())
        );
    }

    row_buffers[r].set(c, bit_value);

    // Automatically hash and store once full
    if (row_buffers[r].count() == s) {
        hash_and_store(r);
    }
}
