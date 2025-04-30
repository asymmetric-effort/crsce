// file: test/verify-crosssum-serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdlib>

int main() {
    try {
        LateralSumMatrix original;

        // Set alternating pattern in each row (0,1,0,1,...)
        for (size_t r = 0; r < s; ++r) {
            CrossSumValue val((r % 2 == 0) ? 0x2AA : 0x155); // binary 010101010 / 101010101
            original.set(r, 0, val);
        }

        std::ostringstream oss;
        original.serialize(oss);

        std::string serialized = oss.str();

        // Deserialize manually: rebuild LateralSumMatrix
        LateralSumMatrix reconstructed;
        std::istringstream iss(serialized);

        size_t bits_in = 0;
        std::bitset<b * s> bit_buffer;
        char chunk[8];

        while (iss.read(chunk, sizeof(chunk))) {
            uint64_t value = *reinterpret_cast<uint64_t*>(chunk);
            bit_buffer |= (std::bitset<b * s>(value) << bits_in);
            bits_in += 64;
        }

        for (size_t r = 0; r < s; ++r) {
            std::bitset<b> val_bits;
            for (size_t i = 0; i < b; ++i) {
                val_bits[i] = bit_buffer[(r * b) + i];
            }
            CrossSumValue val(static_cast<uint16_t>(val_bits.to_ulong()));
            reconstructed.set(r, 0, val);
        }

        for (size_t r = 0; r < s; ++r) {
            uint16_t expected = (r % 2 == 0) ? 0x2AA : 0x155;
            uint16_t actual = reconstructed.get(r, 0).to_uint16();
            if (actual != expected) {
                std::cerr << "[FAIL] row " << r << ": expected " << expected << ", got " << actual << std::endl;
                return EXIT_FAILURE;
            }
        }

        std::cout << "[PASS] CrossSum serialize/deserialize consistency verified." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
