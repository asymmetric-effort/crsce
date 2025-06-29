/**
 * @file 3500_verify-lhash2-store-and-hash.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include "CRSCE/crypto/SHA256.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <vector>

class TestLHashMatrix final : public LHashMatrix {
public:
    std::string debug_get_row_hash(const CrossSumIndex r) const {
        return row_hashes()[r];
    }
};

std::string hex(const std::vector<uint8_t> &input) {
    std::ostringstream oss;
    for (const uint8_t c : input) {
        oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c);
    }
    return oss.str();
}

bool run_test_pattern(const std::string& label, bool (*bit_pattern)(size_t)) {
    std::cout << "[INFO] Running " << label << "..." << std::endl;

    TestLHashMatrix matrix;
    constexpr CrossSumIndex row = 0;
    std::vector<uint8_t> raw_bytes((s + 7) / 8, 0);

    for (CrossSumIndex col = 0; col < s; ++col) {
        const bool bit = bit_pattern(col);
        matrix.push(row, col, bit);
        if (bit) {
            raw_bytes[col / 8] |= (1 << (7 - (col % 8)));
        }
    }

    const std::vector<uint8_t> expected = SHA256::digest(raw_bytes.data(), raw_bytes.size());
    std::string actual = matrix.debug_get_row_hash(row);

    if (actual.size() != SHA256::DIGEST_SIZE) {
        std::cerr << "[FAIL] " << label << " - Hash not computed or incorrect size." << std::endl;
        return false;
    }

    const std::string actual_hex = hex(std::vector<uint8_t>(actual.begin(), actual.end()));

    if (const std::string expected_hex = hex(expected); actual_hex != expected_hex) {
        std::cerr << "[FAIL] " << label << " - Hash mismatch." << std::endl;
        std::cerr << "Expected: " << expected_hex << std::endl;
        std::cerr << "Actual:   " << actual_hex << std::endl;
        return false;
    }

    std::cout << "[PASS] " << label << std::endl;
    return true;
}

bool pattern_all_zeroes(size_t) { return false; }
bool pattern_all_ones(size_t) { return true; }
bool pattern_alternating(size_t i) { return (i % 2 == 0); }

int main() {
    std::cout << "[INFO] verify-lhash2-store-and-hash starting..." << std::endl;

    bool pass = true;

    pass &= run_test_pattern("Pass #1: All Zeros", pattern_all_zeroes);
    pass &= run_test_pattern("Pass #2: All Ones", pattern_all_ones);
    pass &= run_test_pattern("Pass #3: Alternating", pattern_alternating);

    if (!pass) return EXIT_FAILURE;
    std::cout << "[PASS] verify-lhash2-store-and-hash completed successfully." << std::endl;
    return EXIT_SUCCESS;
}
