/**
 * @file 4000_verify-vertical-sum-matrix.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <cstdlib>

constexpr size_t block_size = s;

int verify_100pct_set() {
    std::cout << "verify_100pct_set()" << std::endl;
    VerticalSumMatrix vsm;
    try {
        for (uint16_t r = 0; r < block_size; ++r)
            for (uint16_t c = 0; c < block_size; ++c)
                vsm.increment(r, c);
    } catch (std::overflow_error& error) {
        std::cerr << "[FAIL] verify_100pct_set(): " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    for (uint16_t c = 0; c < block_size; ++c) {
        if (vsm.get(c, c).to_uint16() != block_size) {
            std::cerr << "[FAIL] VSM[" << c << "] = "
                      << vsm.get(c, c).to_uint16()
                      << " expected " << block_size << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int verify_1_bit_per_col_set() {
    std::cout << "verify_1_bit_per_col_set()" << std::endl;
    VerticalSumMatrix vsm;

    for (uint16_t c = 0; c < block_size; ++c)
        vsm.increment(c, c);  // Set (r==c)

    for (uint16_t c = 0; c < block_size; ++c) {
        if (vsm.get(c, c).to_uint16() != 1) {
            std::cerr << "[FAIL] VSM[" << c << "] = "
                      << vsm.get(c, c).to_uint16()
                      << " expected 1" << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int verify_overflow_works() {
    std::cout << "verify_overflow_works()" << std::endl;

    try {
        VerticalSumMatrix vsm;
        for (uint16_t r = 0; r <= block_size; ++r)
            for (uint16_t c = 0; c <= block_size; ++c)
                vsm.increment(r, c);

        std::cerr << "[FAIL] Expected overflow not triggered." << std::endl;
        return EXIT_FAILURE;
    } catch (std::overflow_error) {
        return EXIT_SUCCESS;
    }
}

int main() {
    try {
        if (const int exit = verify_100pct_set(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_1_bit_per_col_set(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_overflow_works(); exit != EXIT_SUCCESS) return exit;

        std::cout << "[PASS] VerticalSumMatrix column-major encoding verified." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
