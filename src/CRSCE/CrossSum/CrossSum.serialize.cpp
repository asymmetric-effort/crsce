// file: src/CRSCE/CrossSum/CrossSum.serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/CrossSum/CrossSum.h"
#include <bitset>
#include <cstdint>
#include <ostream>

void CrossSum::serialize(std::ostream &os) const {
    static constexpr size_t BIT_BUFFER_MASK = 0xFFFFFFFFFFFFFFFF;
    static constexpr size_t BIT_BUFFER_SIZE = b * 8;
    std::bitset<BIT_BUFFER_SIZE> bit_buffer;
    size_t bits_in_buffer = 0;

    for (const auto& value : data) {
        std::bitset<b> value_bits(value.to_uint16());

        // Insert value_bits into LSB of bit_buffer
        bit_buffer |= (std::bitset<BIT_BUFFER_SIZE>(value_bits.to_ullong()) << bits_in_buffer);
        bits_in_buffer += CrossSumValue::b; // b = 9

        // While we have enough bits for a full uint64_t
        if (bits_in_buffer >= FILE_BUFFER_WIDTH) {
            uint64_t chunk = (bit_buffer & std::bitset<BIT_BUFFER_SIZE>(BIT_BUFFER_MASK)).to_ullong();
            os.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));

            // Shift leftover bits into lower positions
            bit_buffer >>= FILE_BUFFER_WIDTH;
            bits_in_buffer -= FILE_BUFFER_WIDTH;
        }
    }

    // Write any remaining bits
    if (bits_in_buffer > 0) {
        uint64_t final_chunk = (bit_buffer & std::bitset<BIT_BUFFER_SIZE>(BIT_BUFFER_MASK)).to_ullong();
        os.write(reinterpret_cast<const char*>(&final_chunk), sizeof(final_chunk));
    }
}
