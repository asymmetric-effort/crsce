// file: src/Common/BitReader/readBits.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Common/BitReader.h"
#include <stdexcept>

uint16_t BitReader::readBits(uint8_t numBits) {
    if (numBits == 0 || numBits > 16) {
        throw std::runtime_error("[BitReader] Invalid bit count: must be 1–16.");
    }

    uint16_t result = 0;
    uint8_t bitsNeeded = numBits;

    while (bitsNeeded > 0) {
        if (bitsRemaining == 0) {
            char byte;
            if (!stream.get(byte)) {
                throw std::runtime_error("[BitReader] Unexpected end of stream.");
            }
            buffer = static_cast<uint8_t>(byte);
            bitsRemaining = 8;
        }

        uint8_t bitsToTake = std::min(bitsNeeded, bitsRemaining);
        uint8_t shift = bitsRemaining - bitsToTake;
        uint8_t bits = (buffer >> shift) & ((1u << bitsToTake) - 1);

        result = (result << bitsToTake) | bits;
        bitsRemaining -= bitsToTake;
        bitsNeeded -= bitsToTake;
    }

    return result;
}
