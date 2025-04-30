// file: test/verify_lhash4_overall.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/crypto/SHA256.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <vector>
#include <cstring>  // for memcmp
#include <cstdlib>  // for EXIT_SUCCESS / EXIT_FAILURE
#include <sstream>

int main() {
    try {
        LHashMatrix lhash;

        // Example input — 64 bytes of deterministic data
        uint8_t input[64];
        for (size_t i = 0; i < 64; ++i) {
            input[i] = static_cast<uint8_t>(i);
        }

        // Push only s = 511 bits into row 0
        for (uint32_t bit_index = 0; bit_index < s; ++bit_index) {
            size_t byte_index = bit_index / 8;
            size_t bit_in_byte = 7 - (bit_index % 8); // <-- MSB first to match original push order
            bool bit_value = (input[byte_index] >> bit_in_byte) & 0x01;
            lhash.push(0, bit_index, bit_value);
        }

        // Expected SHA256 over only the first 511 bits
        uint8_t input_bits_only[64] = {0};

        // Copy 511 bits manually
        for (uint32_t bit_index = 0; bit_index < s; ++bit_index) {
            size_t byte_index = bit_index / 8;
            size_t bit_in_byte = 7 - (bit_index % 8);
            bool bit_value = (input[byte_index] >> bit_in_byte) & 0x01;

            input_bits_only[byte_index] |= (bit_value << bit_in_byte);
        }

        auto expected_hash = SHA256::digest(input_bits_only, sizeof(input_bits_only));

        // Get LHash serialized
        std::ostringstream oss;
        lhash.serialize(oss);
        std::string actual_serialized = oss.str();

        if (actual_serialized.size() < 32) {
            std::cerr << "[FAIL] LHash serialization too small." << std::endl;
            return EXIT_FAILURE;
        }

        const char* actual_hash = actual_serialized.data();

        if (memcmp(actual_hash, expected_hash.data(), expected_hash.size()) != 0) {
            std::cerr << "[FAIL] LHash does not match expected SHA256." << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "[PASS] LHash correctly matches SHA256 of input." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
