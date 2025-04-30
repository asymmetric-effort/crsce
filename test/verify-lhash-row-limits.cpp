// file: test/verify-lhash-row-limits.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include "CRSCE/crypto/SHA256.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

int test_exact_row_fill() {
    LHashMatrix lhash;

    // Fill row 0 with s bits: alternating 0,1 pattern
    for (uint16_t i = 0; i < s; ++i) {
        bool bit = (i % 2 == 0);
        lhash.push(0, i, bit);
    }

    try {
        std::ostringstream oss;
        lhash.serialize(oss);  // Should succeed
        std::string output = oss.str();

        if (output.size() < 32) {
            std::cerr << "[FAIL] Row hash too short after exact fill." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "[PASS] Exact row of s bits serialized and hashed correctly." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Exception during serialization: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int test_row_overflow() {
    LHashMatrix lhash;

    // Fill row 0 with s+1 bits: expect an exception
    try {
        for (uint16_t i = 0; i <= s; ++i) {
            lhash.push(0, i, true);
        }
        std::cerr << "[FAIL] Overflow not triggered for row length > s." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::overflow_error& e) {
        std::cout << "[PASS] Overflow correctly triggered on row > s bits." << std::endl;
        return EXIT_SUCCESS;
    } catch (...) {
        std::cerr << "[FAIL] Unexpected exception type for row overflow." << std::endl;
        return EXIT_FAILURE;
    }
}

int main() {
    try {
        if (test_exact_row_fill() != EXIT_SUCCESS) return EXIT_FAILURE;
        if (test_row_overflow() != EXIT_SUCCESS) return EXIT_FAILURE;

        std::cout << "[PASS] LHashMatrix row completion behavior verified." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Unexpected exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
