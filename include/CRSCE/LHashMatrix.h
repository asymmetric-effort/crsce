/**
 * @file include/CRSCE/LHashMatrix.h
 * @brief declare a lateral hash matrix of s-hashes, where this class will allow
 *        data to be acquired over time and when each row is filled, a hash is calculated.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @todo Consider implementing a streaming SHA256 hash where we can feed data directly into
 *       the hashing algorithm as it is received rather than buffer a row.  This should then
 *       allow the row-termination point to finalize the remaining calculation.
 */
#pragma once

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
    LHashMatrix() = default;

    virtual ~LHashMatrix();

    void push(CrossSumIndex r, CrossSumIndex c, bool bit_value);
    void serialize(std::ostream& os) const;

    /**
     * @brief If the current block has fewer than s×s bits, pad the rest with zeros.
     * @param block_count Index of the block being padded (for logging).
     * @param block_bits  Number of bits already pushed in this block.
     */
    void padRemainingBits(std::size_t block_count, std::size_t block_bits);

protected:
    void hash_and_store(CrossSumIndex row_index) const;

    virtual std::array<std::bitset<s>, s> &row_buffers() { return row_buffer_data; }
    [[nodiscard]] virtual const std::array<std::bitset<s>, s> &row_buffers() const { return row_buffer_data; }

    virtual std::array<size_t, s> &row_positions() { return row_position_data; }
    [[nodiscard]] virtual const std::array<size_t, s> &row_positions() const { return row_position_data; }

    virtual std::array<std::string, s> &row_hashes() { return row_hash_data; }
    [[nodiscard]] virtual const std::array<std::string, s> &row_hashes() const { return row_hash_data; }

private:
    // Bit buffer for each row
    std::array<std::bitset<s>, s> row_buffer_data{};  // zero-initialize all positions

    // Track current position in each row
    std::array<size_t, s> row_position_data{};  // zero-initialize all positions

    // SHA256 hashes per row
    mutable std::array<std::string, s> row_hash_data{};  // zero-initialize all positions
};
