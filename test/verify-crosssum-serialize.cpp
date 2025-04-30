// file: test/verify-crosssum-serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <cstdint>
#include <cstdlib>

int main() {
    try {                                        //   987654321
        const CrossSumValue pattern_even(0x2AA); // 0b101010101
        const CrossSumValue pattern_odd (0x1FF); // 0b111111111

        LateralSumMatrix lsm;

        // Set alternating rows with two patterns
        for (size_t i = 0; i < s; ++i) {
            CrossSumValue pattern = (i % 2 == 0) ? pattern_even : pattern_odd;
            lsm.set(i, 0, pattern);
        }

        // Serialize to memory
        std::ostringstream oss;
        lsm.serialize(oss);
        std::string serialized = oss.str();

        // Convert expected bits manually
        std::bitset<s * b> expected_bits;
        size_t bit_index = 0;
        for (size_t i = 0; i < s; ++i) {
            uint16_t value = (i % 2 == 0) ? 0x2AA : 0x1FF;
            std::bitset<b> bits(value);
            for (size_t j = 0; j < b; ++j)
                expected_bits[bit_index++] = bits[j];
        }

        // Reconstruct actual bitstream from serialized bytes
        std::bitset<s * b> actual_bits;
        bit_index = 0;
        for (char ch : serialized) {
            uint8_t byte = static_cast<uint8_t>(ch);
            for (size_t j = 0; j < 8; ++j)
                actual_bits[bit_index++] = (byte >> j) & 1;
        }

        if (expected_bits != actual_bits) {
            std::cerr << "[FAIL] Serialized bitstream does not match expected pattern." << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "[PASS] CrossSum::serialize() output matches expected alternating pattern." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
