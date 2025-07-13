// file: src/CRSCE/CRSCE.deserialize_input.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include "CRSCE/constants/constants.h"

#include "Common/BitReader.h"
#include "CRSCE/LHashMatrix.h"
#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

void CRSCE::deserialize_input(const LateralSumMatrix& LSM,
                              const VerticalSumMatrix& VSM,
                              const DiagonalSumMatrix& XSM,
                              const AntidiagonalSumMatrix& DSM,
                              const LHashMatrix& LHASH) {

    // 3) Read cross-sum bit-width b
    const uint8_t b = static_cast<uint8_t>(std::ceil(std::log2(s)));

    // 4) Read row-hash matrix (LHASH)
    LHASH.deserialize(inputStream);

    // 5) Prepare BitReader for unpacking cross-sums
    BitReader br(inputStream);

    // 6) Read and populate each CrossSum matrix
    lateralSum.clear();
    verticalSum.clear();
    diagonalSum.clear();
    antiDiagonalSum.clear();

    for (size_t i = 0; i < s; ++i) {
        lateralSum.set(i, 0, br.readBits(b));
    }
    for (size_t i = 0; i < s; ++i) {
        verticalSum.set(0, i, br.readBits(b));
    }
    for (size_t i = 0; i < s; ++i) {
        diagonalSum.set(i, 0, br.readBits(b));
    }
    for (size_t i = 0; i < s; ++i) {
        antiDiagonalSum.set(i, 0, br.readBits(b));
    }
}