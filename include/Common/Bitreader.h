// file: include/Common/Bitreader.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <istream>
#include <cstdint>

/**
 * @class BitReader
 * @brief Provides bit-level deserialization from an input stream.
 *
 * This utility class reads an arbitrary number of bits (≤ 16) from
 * a byte-aligned `std::istream`, buffering partial bytes as needed.
 */
class BitReader {
public:
    /**
     * @name constructor
     * @brief Construct a BitReader from an input stream.
     * @param in Reference to an open std::istream (must remain valid).
     */
    explicit BitReader(std::istream& in);

    /**
     * @readBits
     * @brief Read `numBits` (≤ 16) from the stream.
     * @param numBits Number of bits to read (must be 1–16).
     * @return The extracted bits as a right-aligned uint16_t value.
     * @throws std::runtime_error on invalid bit count or EOF.
     */
    uint16_t readBits(uint8_t numBits);

    /**
     * @name alignToByte
     * @brief Align the bit position to the next full byte boundary.
     */
    void alignToByte();

private:
    std::istream& stream;
    uint8_t buffer = 0;      ///< Current byte buffer
    uint8_t bitsRemaining = 0; ///< Bits remaining in buffer
};
