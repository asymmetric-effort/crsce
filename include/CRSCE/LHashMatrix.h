/**
 * @file include/CRSCE/LHashMatrix.h
 * @brief declare a lateral hash matrix of s-hashes, where this class will allow
 *        data to be acquired over time and when each row is filled, a hash is calculated.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @todo Consider implementing a streaming SHA256 hash where we can feed data directly into
 *       the hashing algorithm as it is received rather than buffer a row.  This should then
 *       allow the row-termination point to finalize the remaining calculation.
 */

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
    LHashMatrix(): row_positions{}{};
    ~LHashMatrix();

    void push(CrossSumIndex r, CrossSumIndex c, bool bit_value);
    void serialize(std::ostream& os) const;

protected:
    void hash_and_store(CrossSumIndex row_index);

private:
    // Bit buffer for each row
    std::array<std::bitset<s>, s> row_buffers;

    // Track current position in each row
    std::array<size_t, s> row_positions;

    // SHA256 hashes per row
    std::array<std::string, s> row_hashes;
};

#endif // CRSCE_LHASHMATRIX_H
