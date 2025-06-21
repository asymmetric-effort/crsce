// file: src/CRSCE/CrossSum/LHashMatrix/padRemainingBits.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"  // for s
#include <iostream>

void LHashMatrix::padRemainingBits(const std::size_t block_count, const std::size_t block_bits) {
    if (constexpr std::size_t total_bits = s * s; block_bits < total_bits) {
        std::cerr << "[CRSCE] Padding block " << block_count
                  << " from " << block_bits << " to " << total_bits << " bits." << std::endl;
        for (std::size_t i = block_bits; i < total_bits; ++i) {
            const CrossSumIndex r = static_cast<CrossSumIndex>(i / s);
            const CrossSumIndex c = static_cast<CrossSumIndex>(i % s);
            push(r, c, false);
        }
    }
}
