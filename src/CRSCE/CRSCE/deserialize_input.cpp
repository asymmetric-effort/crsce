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

void CRSCE::deserialize_input(const LateralSumMatrix& LSM, const VerticalSumMatrix& VSM,
    const DiagonalSumMatrix& XSM, const AntidiagonalSumMatrix& DSM, const LHashMatrix& LHASH) {

    // 1) Verify and consume block header and size
    std::string hdr(HEADER.size(), '\0');
    inputStream.read(&hdr[0], static_cast<std::streamsize>(HEADER.size()));
    if (hdr != HEADER) {
        throw std::runtime_error("[CRSCE] Invalid block header");
    }

    // 2) Read block size s (must match configured value)
    uint16_t s = 0;
    inputStream.read(reinterpret_cast<char*>(&s), sizeof(s));
    if (s != this->blockSize) {
        throw std::runtime_error("[CRSCE] Unexpected block size");
    }

    // 3) Read cross-sum bit-width b
    const uint8_t b = static_cast<uint8_t>(std::ceil(std::log2(s)));

    // 4) Read row-hash matrix (LHASH)
    lhMatrix.clear();
    for (size_t r = 0; r < s; ++r) {
        std::string hash(SHA256::DIGEST_SIZE, '\0');
        inputStream.read(&hash[0], static_cast<std::streamsize>(SHA256::DIGEST_SIZE));
        lhMatrix.push_back(hash);
    }

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