/**
 * @file 4000-AntiDiagonal-Cross-Sum-Matrix-Verify.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <cstdlib>

constexpr size_t block_size = s;

int verify_100pct_set() {
    std::cout << "verify_100pct_set()" << std::endl;
    AntidiagonalSumMatrix dsm;
    try {
        for (uint16_t r = 0; r < block_size; ++r)
            for (uint16_t c = 0; c < block_size; ++c)
                dsm.increment(r, c);
    } catch (std::overflow_error& error) {
        std::cerr << "[FAIL] verify_100pct_set(): " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Validate that sums on antidiagonals are correct
    for (uint16_t r = 0; r < block_size; ++r) {
        if (dsm.get(r, r).to_uint16() != block_size) {
            std::cerr << "[FAIL] DSM[" << r << "] = "
                      << dsm.get(r, r).to_uint16()
                      << " expected " << block_size << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int verify_1_bit_per_antidiagonal() {
    std::cout << "verify_1_bit_per_antidiagonal()" << std::endl;
    AntidiagonalSumMatrix dsm;

    for (uint16_t r = 0; r < block_size; ++r)
        dsm.increment(r, r);  // Set diagonal bits only

    for (uint16_t i = 0; i < block_size; ++i) {
        if (const uint16_t expected = (i == 0) ? block_size : 0; dsm.get(i, 0).to_uint16() != expected) {
            std::cerr << "[FAIL] DSM[" << i << "] = "
                      << dsm.get(i, 0).to_uint16()
                      << " expected " << expected << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


int verify_overflow_works() {
    std::cout << "verify_overflow_works()" << std::endl;

    try {
        AntidiagonalSumMatrix dsm;
        for (uint16_t r = 0; r <= block_size; ++r)
            for (uint16_t c = 0; c <= block_size; ++c)
                dsm.increment(r, c);

        std::cerr << "[FAIL] Expected overflow not triggered." << std::endl;
        return EXIT_FAILURE;
    } catch (std::overflow_error) {
        return EXIT_SUCCESS;
    }
}

int main() {
    try {
        if (const int exit = verify_100pct_set(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_1_bit_per_antidiagonal(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_overflow_works(); exit != EXIT_SUCCESS) return exit;

        std::cout << "[PASS] AntidiagonalSumMatrix antidiagonal encoding verified." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
