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
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"

#include <bitset>
#include <string>
#include <array>
#include <stdexcept>
#include <iomanip>


class LHashMatrix {
public:
    /**
     * @name default constructor
     * @brief Constructor assumes CRSCE s-value pre-defined.
     * @todo make s-value configurable (representing the number of rows)
     */
    LHashMatrix() = default;

    /**
     * @name default destructor
     * @brief Default destructor
     */
    virtual ~LHashMatrix() = default;

    /**
     * @name push
     * @brief push a given bit_value (0,1) for CSM[r,c] to the internal buffer.
     * @param r row index
     * @param c column index
     * @param bit_value CSM bit value (0,1)
     */
    void push(CrossSumIndex r, CrossSumIndex c, bool bit_value);

    /**
     * @name serialize
     * @brief given an output stream, serialize the hash state (s-rows of hashes) and write to the output stream.
     * @param os output stream
     */
    void serialize(std::ostream &os) const;

    /**
     * @name deserialize
     * @brief given an input stream (e.g., file) read the input state into the LHASH rows with an assumed s-value
     *        representing the number of rows to consume and fixed 32-byte hash length.
     * @param is input stream
     */
    void deserialize(std::istream &is) const;

    /**
     * @name padRemainingBits
     * @brief If the current block has fewer than s×s bits, pad the rest with zeros.
     * @param block_count Index of the block being padded (for logging).
     * @param block_bits  Number of bits already pushed in this block.
     */
    void padRemainingBits(std::size_t block_count, std::size_t block_bits);

protected:
    /**
     * @name hash_and_store
     * @brief Given a current buffer state, calculate the SHA-256 hash and store the resulting lateral hash.
     * @param row_index CrossSumIndex (0...s-1)
     */
    void hash_and_store(CrossSumIndex row_index) const;

    /**
     * @name row_buffers
     * @brief return the current buffer state.
     * @return std::array<std::bitset<s>,s> the full row-buffer state.
     */
    virtual std::array<std::bitset<s>, s> &row_buffers() { return row_buffer_data; }
    [[nodiscard]] virtual const std::array<std::bitset<s>, s> &row_buffers() const { return row_buffer_data; }
    /**
     * @name row_positions
     * @brief return the current row-position data within the buffer
     * @return std::array<size_t, s>
     */
    virtual std::array<size_t, s> &row_positions() { return row_position_data; }
    [[nodiscard]] virtual const std::array<size_t, s> &row_positions() const { return row_position_data; }
    /**
     * @name row_hashes
     * @brief return the current output hash state.
     * @return std::array<std::string, s> representing the hashes calculated at the point of invocation.
     */
    virtual std::array<std::string, s> &row_hashes() { return row_hash_data; }
    [[nodiscard]] virtual const std::array<std::string, s> &row_hashes() const { return row_hash_data; }

private:
    /**
     * @name row_buffer_data
     * @brief Bit buffer for each row. zero-initialize all positions at initialization.
     */
    std::array<std::bitset<s>, s> row_buffer_data{};
    /**
     * @name row_position_data
     * @brief Track current position in each row. zero-initialize all positions at initialization.
     */
    std::array<size_t, s> row_position_data{};

    /**
     * @name row_hash_data
     * @brief SHA256 hashes per row. zero-initialize all positions at initialization.
     */
    mutable std::array<std::string, s> row_hash_data{};
};
