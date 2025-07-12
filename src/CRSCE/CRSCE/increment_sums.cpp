/**
 * @file src/CRSCE/compress.cpp
 * @brief declare the CRSCE compression algorithm as a unit (with compress() and decompress() features).  This is
 *        the top-level class we should expose as a library.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "CRSCE/CRSCE.h"

void CRSCE::increment_sums(
    const bool bit_value,
    const CrossSumIndex r,
    const CrossSumIndex c,
    LateralSumMatrix &LSM,
    VerticalSumMatrix &VSM,
    DiagonalSumMatrix &XSM,
    AntidiagonalSumMatrix &DSM,
    LHashMatrix &LHASH
) {
    // Update cross-sum matrices
    if (bit_value) {
        LSM.increment(r, c);
        VSM.increment(r, c);
        XSM.increment(r, c);
        DSM.increment(r, c);
    }
    LHASH.push(r, c, bit_value);
}
