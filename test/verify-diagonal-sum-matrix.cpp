// file: test/verify-diagonal-sum-matrix.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
#include <iostream>
#include <cstdlib>

constexpr size_t block_size = 512;
constexpr size_t cross_sum_width = 9;

int verify_100pct_set() {
    DiagonalSumMatrix xsm(block_size, cross_sum_width);
    std::cout << "verify_100pct_set()" << std::endl;
    for (uint16_t r = 0; r < block_size; ++r)
        for (uint16_t c = 0; c < block_size - 1; ++c)
            xsm.increment(r, c);
    for (uint16_t r = 0; r < block_size; ++r)
        if (auto sum = xsm.get(r, r).to_uint16(); sum != (block_size - 1)) {
            std::cerr << "[FAIL] Verification(1/3): XSM value expects full set value at (" << r << "," << r << ")." << std::endl;
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}

int verify_1_bit_per_diagonal() {
    DiagonalSumMatrix xsm(block_size, cross_sum_width);
    std::cout << "verify_1_bit_per_diagonal()" << std::endl;
    for (uint16_t r = 0; r < block_size; ++r)
        xsm.increment(r, r); // Diagonal set (r == c)

    for (uint16_t r = 0; r < block_size; ++r)
        if (auto sum = xsm.get(r, r).to_uint16(); sum != 1) {
            std::cerr << "[FAIL] Verification(2/3): XSM expected 1 at (" << r << "," << r << ")." << std::endl;
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}

int verify_overlow_works() {
    DiagonalSumMatrix xsm(block_size, cross_sum_width);
    std::cout << "verify_overlow_works()" << std::endl;
    try {
        for (uint16_t r = 0; r <= block_size; ++r)
            for (uint16_t c = 0; c <= block_size; ++c)
                xsm.increment(r, c);
        std::cerr << "[FAIL] Overflow not detected when expected." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::overflow_error& e) {
        return EXIT_SUCCESS;
    }
}

int main() {
    try {
        if (int exit = verify_100pct_set(); exit != EXIT_SUCCESS) return EXIT_FAILURE;
        if (int exit = verify_1_bit_per_diagonal(); exit != EXIT_SUCCESS) return EXIT_FAILURE;
        if (int exit = verify_overlow_works(); exit != EXIT_SUCCESS) return EXIT_FAILURE;

        std::cout << "[PASS] DiagonalSumMatrix diagonal encoding verified." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
