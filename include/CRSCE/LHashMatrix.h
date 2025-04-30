// file: include/CRSCE/LHashMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LHASHMATRIX_H
#define CRSCE_LHASHMATRIX_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/crypto/SHA256.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include <bitset>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <stdexcept>

class LHashMatrix {
public:
    // Constructor assumes CRSCE s-value
    LHashMatrix();
    ~LHashMatrix();

    void push(CrossSumIndex r, CrossSumIndex c, bool bit_value);
    void serialize(std::ostream& os) const;

protected:
    // Bit buffer for each row
    std::array<std::bitset<s>, s> row_buffers;

    // Track current position in each row
    std::array<size_t, s> row_positions;

    // SHA256 hashes per row
    std::array<std::string, s> row_hashes;

    void hash_and_store(CrossSumIndex row_index);
};

#endif // CRSCE_LHASHMATRIX_H
