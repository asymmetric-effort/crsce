// file: src/CRSCE/CrossSum/CrossSum.serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/CrossSum/CrossSum.h"
#include <bitset>
#include <cstdint>
#include <ostream>

void CrossSum::serialize(std::ostream &os) const {
    constexpr size_t total_bits = b * s;
    std::bitset<total_bits> bits;

    // Flatten each CrossSumValue into b-bit segments and place into bitset
    for (size_t i = 0; i < s; ++i) {
        CrossSumValue val = data[i];
        std::bitset<b> val_bits(val.to_uint16());

        for (size_t j = 0; j < b; ++j) {
            bits[i * b + j] = val_bits[j];
        }
    }

    // Output the entire bitset to the stream, one byte at a time (MSB-first)
    for (size_t byte = 0; byte < (total_bits + 7) / 8; ++byte) {
        uint8_t out = 0;
        for (size_t bit = 0; bit < 8; ++bit) {
            size_t index = byte * 8 + bit;
            if (index < total_bits && bits[index]) {
                out |= (1 << (7 - bit));
            }
        }
        os.put(static_cast<char>(out));
    }
}
