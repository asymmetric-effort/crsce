// file: src/CRSCE/LHashMatrix/push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"


void LHashMatrix::push(uint32_t r, uint32_t c, bool bit_value) {
    if (r >= block_size || c >= block_size) {
        throw std::out_of_range("LHashMatrix push out of bounds");
    }

    row_buffers[r][c] = bit_value;

    if (c == block_size - 1) {
        hash_and_store(r);
    }
}
