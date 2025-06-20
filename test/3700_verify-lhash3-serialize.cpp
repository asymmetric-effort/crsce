/**
 * @file 3700_verify-lhash3-serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include "utils/TestPatterns.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>

class TestLHashMatrix final : public LHashMatrix {
public:
    std::string debug_serialize_to_hex() const {
        std::ostringstream oss;
        this->serialize(oss);
        const std::string &raw = oss.str();

        std::ostringstream hex_output;
        for (unsigned char c : raw) {
            hex_output << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        }
        return hex_output.str();
    }
};

bool run_lateral_hash_serialization_test(const std::string& name, PatternFn pattern) {
    std::cout << "[INFO] Running " << name << " test..." << std::endl;

    TestLHashMatrix matrix;
    for (CrossSumIndex r = 0; r < s; ++r) {
        for (CrossSumIndex c = 0; c < s; ++c) {
            matrix.push(r, c, pattern(r, c));
        }
    }

    const std::string serialized_hex = matrix.debug_serialize_to_hex();
    constexpr size_t expected_bytes = s * SHA256::DIGEST_SIZE;
    const size_t actual_bytes = serialized_hex.size() / 2;

    if (actual_bytes != expected_bytes) {
        std::cerr << "[FAIL] " << name << " - Serialized output size mismatch. Expected "
                  << expected_bytes << ", got " << actual_bytes << " bytes." << std::endl;
        return false;
    }

    std::cout << "[PASS] " << name << " - Output size OK: " << actual_bytes << " bytes." << std::endl;
    return true;
}

int main() {
    std::vector<TestPattern> patterns = {
        {"All Zeros", all_zeros},
        {"All Ones", all_ones},
        {"Checkerboard", checkerboard}
    };

    bool all_passed = true;
    for (const auto&[name, generator] : patterns) {
        all_passed &= run_lateral_hash_serialization_test(name, generator);
    }

    return all_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
