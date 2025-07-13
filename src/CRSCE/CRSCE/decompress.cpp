// file: src/CRSCE/CRSCE/decompress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "CRSCE/constants/constants.h"
#include "Common/BitReader.h"

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include "CRSCE/CrossSum/DiagonalSumMatrix//DiagonalSumMatrix.h"
#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

int CRSCE::decompress() {
    std::cout << "[CRSCE] Decompressing..." << std::endl;

    // --- 1) Verify header
    std::string header(HEADER.length(), '\0');
    inputStream.read(&header[0], static_cast<std::streamsize>(HEADER.length()));
    if (header != HEADER) {
        throw std::runtime_error("[CRSCE] Invalid file header.");
    }

    // --- 2) Read block size (s) and compute bitwidth (b)
    uint16_t s = 0;
    inputStream.read(reinterpret_cast<char*>(&s), sizeof(s));
    if (s != 512) {
        throw std::runtime_error("[CRSCE] Unsupported block size. Only s=512 supported.");
    }
    const uint8_t b = static_cast<uint8_t>(std::ceil(std::log2(s)));

    // --- 3) Read block count
    uint32_t blockCount = 0;
    inputStream.read(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

    // --- 4) Loop over each block
    for (uint32_t blockIdx = 0; blockIdx < blockCount; ++blockIdx) {
        std::cout << "[CRSCE] Loading block " << blockIdx
                  << " of " << blockCount << "..." << std::endl;

        // 4a) Deserialize the lateral-hash matrix (LH)
        CRSCE::matrix::LHashMatrix lh(s);
        lh.deserialize(inputStream);

        // 4b) Prepare bit-reader for cross-sum data
        BitReader bitReader(inputStream);

        // 4c) Deserialize each cross-sum projection
        CRSCE::matrix::LateralSumMatrix   lsm(s, b);
        CRSCE::matrix::VerticalSumMatrix   vsm(s, b);
        CRSCE::matrix::DiagonalSumMatrix   dsm(s, b);
        CRSCE::matrix::XSumMatrix          xsm(s, b);

        lsm.deserialize(bitReader);
        vsm.deserialize(bitReader);
        dsm.deserialize(bitReader);
        xsm.deserialize(bitReader);

        // 4d) Allocate the CSM grid (unknown bits = –1)
        std::vector<std::vector<int8_t>> CSM(
            s, std::vector<int8_t>(s, -1)
        );

        // 4e) Decompression phases (placeholders)
        // TODO: Deterministic Elimination (DE) using lsm/vsm/dsm/xsm
        // TODO: Game of Beliefs Protocol (GOBP) over CSM
        // TODO: Validate each row of CSM against lh.hash(i)
        // TODO: Emit the reconstructed block to outputStream
    }

    return 0;
}
