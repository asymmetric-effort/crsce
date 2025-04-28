// file: test/verify_lhash.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/crypto/SHA256.h"
#include <iostream>
#include <vector>
#include <cstring> // for memcmp
#include <cstdlib> // for EXIT_SUCCESS / EXIT_FAILURE

int main() {
    try {
        constexpr size_t block_size = 512;
        LHashMatrix lhash(block_size);

        // Example fixed input - 64 bytes of known pattern
        uint8_t input[64];
        for (size_t i = 0; i < 64; ++i) {
            input[i] = static_cast<uint8_t>(i); // deterministic pattern 0x00, 0x01, ..., 0x3F
        }

        // Push 512 bits into row 0
        for (uint32_t bit_index = 0; bit_index < block_size; ++bit_index) {
            size_t byte_index = bit_index / 8;
            size_t bit_in_byte = 7 - (bit_index % 8);
            bool bit_value = (input[byte_index] >> bit_in_byte) & 0x01;
            lhash.push(0, bit_index, bit_value);
        }

        // Expected SHA256 of the input array
        auto expected_hash = SHA256::digest(input, sizeof(input));

        // Retrieve actual hash from LHashMatrix
        std::ostringstream oss;
        lhash.serialize(oss);
        std::string actual_serialized = oss.str();

        if (actual_serialized.size() < 32) {
            std::cerr << "[FAIL] LHash serialization too small." << std::endl;
            return EXIT_FAILURE;
        }

        const char* actual_hash = actual_serialized.data(); // First row hash (32 bytes)

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
