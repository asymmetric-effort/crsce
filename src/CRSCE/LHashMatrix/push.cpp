// file: src/CRSCE/LHashMatrix/push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/constants/constants.h"
#include "CRSCE/LHashMatrix.h"


void LHashMatrix::push(uint32_t r, uint32_t c, bool bit_value) {
    if (r > max_index || c > max_index) {
        throw std::out_of_range("LHashMatrix push out of bounds");
    }

    row_buffers[r][c] = bit_value;

    //We are at the end of the row.
    if (c >= max_index) {
        hash_and_store(r);
    }
}
