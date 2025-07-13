/**
 * @file src/CRSCE/LHashMatrix/hash_and_store.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include <array>
#include "CRSCE/crypto/SHA256.h"
#include <vector>

void LHashMatrix::hash_and_store(const CrossSumIndex row_index) const {
    std::array<uint8_t, 64> row_bytes{}; // 512 bits = 64 bytes

    for (size_t i = 0; i < s; ++i) {
        if (row_buffer_data[row_index][i]) {
            const size_t byte_index = i / 8;
            const size_t bit_offset = 7 - (i % 8);
            row_bytes[byte_index] |= (1 << bit_offset);
        }
    }

    const auto hash = SHA256::digest(row_bytes.data(), row_bytes.size());
    row_hash_data[row_index] = std::string(reinterpret_cast<const char*>(hash.data()), hash.size());
}
