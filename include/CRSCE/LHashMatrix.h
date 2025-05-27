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
    /**
     * @name constructor
     * @brief initialize the values with zeroes
     */
    LHashMatrix();
    /**
     * @name destructor
     * @brief noop
     */
    ~LHashMatrix();
    /**
     * @name push
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param bit_value bool
     * @brief push value 'bit_value' to position (r,c)
     */
    void push(const CrossSumIndex r, const CrossSumIndex c, const bool bit_value);
    /**
     * @name serialize
     * @param os std::ostream
     * @brief write the LHashMatrix data out as a serialized bit-packed sequence.
     */
    void serialize(std::ostream& os) const;

protected:
    // Bit buffer for each row
    std::array<std::bitset<s>, s> row_buffers;

    // Track current position in each row
    std::array<size_t, s> row_positions;

    // SHA256 hashes per row
    std::array<std::string, s> row_hashes;
    /**
     * @name hash_and_store
     * @brief hash the current row buffer and store to the LHashMatrix row_index
     */
    void hash_and_store(CrossSumIndex row_index);
};

#endif // CRSCE_LHASHMATRIX_H
