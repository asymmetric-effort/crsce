// file: test/verify-lhash3-serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>

class TestLHashMatrix : public LHashMatrix {
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

bool pattern_all_zeros(size_t, size_t) { return false; }

int main() {
    std::cout << "[INFO] verify-lhash3-serialize starting..." << std::endl;

    TestLHashMatrix matrix;

    // Fill all rows with all 0s to guarantee complete CSM
    for (CrossSumIndex r = 0; r < s; ++r) {
        for (CrossSumIndex c = 0; c < s; ++c) {
            matrix.push(r, c, pattern_all_zeros(r, c));
        }
    }

    // Serialize matrix and capture output
    std::string serialized_hex = matrix.debug_serialize_to_hex();

    // Confirm output length = s * SHA256::DIGEST_SIZE (rows * 32 bytes)
    size_t expected_bytes = s * SHA256::DIGEST_SIZE;
    size_t actual_bytes = serialized_hex.size() / 2;

    if (actual_bytes != expected_bytes) {
        std::cerr << "[FAIL] Serialized output size mismatch. Expected " << expected_bytes
                  << " bytes, got " << actual_bytes << " bytes." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "[PASS] Serialization produced expected output size: " << actual_bytes << " bytes." << std::endl;
    return EXIT_SUCCESS;
}
