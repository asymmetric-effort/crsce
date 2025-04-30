// file: test/verify-compress-bit-mapping.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include "CRSCE/FileBuffer.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <cstdlib>

int verify_single_bit_location(uint64_t bit_offset) {
    LateralSumMatrix lsm;

    FileBuffer buffer((bit_offset / FILE_BUFFER_WIDTH) + 1, 0);
    size_t word_index = bit_offset / FILE_BUFFER_WIDTH;
    size_t bit_index = FILE_BUFFER_WIDTH - 1 - (bit_offset % FILE_BUFFER_WIDTH);
    buffer[word_index] = uint64_t(1) << bit_index;

    uint64_t bit_index_global = 0;
    for (const auto& word : buffer) {
        for (int bit = FILE_BUFFER_WIDTH - 1; bit >= 0; --bit) {
            bool bit_value = (word >> bit) & 0x01;
            CrossSumIndex r = bit_index_global / s;
            CrossSumIndex c = bit_index_global % s;

            if (bit_value)
                lsm.increment(r, c);
            ++bit_index_global;
        }
    }

    // Now validate: exactly one matrix element should be 1, all others 0
    size_t ones = 0;
    CrossSumIndex expected_r = bit_offset / s;
    CrossSumIndex expected_c = bit_offset % s;

    for (CrossSumIndex r = 0; r < s; ++r) {
        CrossSumValue val = lsm.get(r, expected_c);
        uint16_t v = val.to_uint16();
        if (r == expected_r) {
            if (v != 1) {
                std::cerr << "[FAIL] Expected (r=" << r << ",c=" << expected_c
                          << ") to be 1, got " << v << std::endl;
                return EXIT_FAILURE;
            }
            ones++;
        } else {
            if (v != 0) {
                std::cerr << "[FAIL] Unexpected value at (r=" << r << ",c=" << expected_c
                          << "): got " << v << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    if (ones != 1) {
        std::cerr << "[FAIL] Expected exactly one 1 in LSM, found " << ones << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main() {
    try {
        // Sample a few strategic offsets:
        std::vector<uint64_t> bit_offsets = {0, s - 1, s, s + 1, s * 10 + 5, s * s - 1};

        for (auto offset : bit_offsets) {
            std::cout << "Testing bit offset " << offset << "..." << std::endl;
            if (verify_single_bit_location(offset) != EXIT_SUCCESS)
                return EXIT_FAILURE;
        }

        std::cout << "[PASS] Bit-to-(r,c) mapping verified in compress() simulation." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
