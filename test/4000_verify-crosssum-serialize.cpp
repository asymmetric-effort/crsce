// file: test/verify-crosssum-serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdlib>

constexpr uint16_t white = 511;
constexpr uint16_t grey = 341;

void create_alternating_pattern(CrossSum &original) {
    std::cout << "[INFO] create_alterating_pattern()" << std::endl;
    for (size_t r = 0; r < s; ++r) {
        CrossSumValue val((r % 2 == 0) ? white : grey);
        original.set(r, 0, val);
    }
}

void serialize_matrix(CrossSum &original, std::string &serialized) {
    std::cout << "[INFO] serialize_matrix()" << std::endl;
    std::ostringstream oss;
    original.serialize(oss);
    serialized = oss.str();
}

void deserialize_bitstream(const std::string &serialized, std::bitset<b * s> &bitstream) {
    std::cout << "[INFO] deserialize_bitstream()" << std::endl;
    size_t bit_index = 0;
    for (unsigned char c : serialized) {
        for (int i = 7; i >= 0; --i) {
            if (bit_index < b * s) {
                bitstream[bit_index++] = (c >> i) & 1;
            }
        }
    }
}

void reconstruct_matrix(const std::bitset<b * s> &bitstream, LateralSumMatrix &matrix) {
    std::cout << "[INFO] reconstruct_matrix()" << std::endl;
    for (size_t r = 0; r < s; ++r) {
        std::bitset<b> val_bits;
        for (size_t i = 0; i < b; ++i) {
            val_bits[i] = bitstream[(r * b) + i];
        }
        CrossSumValue val(static_cast<uint16_t>(val_bits.to_ulong()));
        matrix.set(r, 0, val);
    }
}

bool validate_matrix(const LateralSumMatrix &matrix) {
    std::cout << "[INFO] validate_matrix()" << std::endl;
    for (size_t r = 0; r < s; ++r) {
        uint16_t expected = (r % 2 == 0) ? white : grey;
        uint16_t actual = matrix.get(r, 0).to_uint16();
        if (actual != expected) {
            std::cerr << "[FAIL] row " << r << ": expected " << expected << ", got " << actual << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    LateralSumMatrix original;
    create_alternating_pattern(original);

    std::string serialized;
    serialize_matrix(original, serialized);

    std::bitset<b * s> bitstream;
    deserialize_bitstream(serialized, bitstream);

    LateralSumMatrix reconstructed;
    reconstruct_matrix(bitstream, reconstructed);

    if (!validate_matrix(reconstructed)) return EXIT_FAILURE;

    std::cout << "[PASS] CrossSum serialize/deserialize consistency verified." << std::endl;
    return EXIT_SUCCESS;
}
