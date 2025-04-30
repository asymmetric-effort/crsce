// file: src/CRSCE/LHashMatrix/hash_and_store.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"

void LHashMatrix::hash_and_store(CrossSumIndex row_index) {
    uint8_t row_bytes[64] = {0}; // 512 bits = 64 bytes

    for (size_t i = 0; i < s; ++i) {
        if (row_buffers[row_index][i]) {
            size_t byte_index = i / 8;
            size_t bit_offset = 7 - (i % 8);
            row_bytes[byte_index] |= (1 << bit_offset);
        }
    }

    auto hash = SHA256::digest(row_bytes, sizeof(row_bytes));
    row_hashes[row_index] = std::string(reinterpret_cast<const char*>(hash.data()), hash.size());
}
