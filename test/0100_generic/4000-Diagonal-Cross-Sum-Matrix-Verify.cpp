/**
 * @file 4000-Diagonal-Cross-Sum-Matrix-Verify.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <map>
#include <cstdlib>

constexpr size_t block_size = s;

int verify_100pct_set() {
    std::cout << "verify_100pct_set()" << std::endl;
    DiagonalSumMatrix xsm;

    try {
        for (uint16_t r = 0; r < block_size; ++r)
            for (uint16_t c = 0; c < block_size; ++c)
                xsm.increment(r, c);
    } catch (std::overflow_error& error) {
        std::cerr << "[FAIL] verify_100pct_set(): " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    for (uint16_t i = 0; i < block_size; ++i) {
        if (xsm.get(i, i).to_uint16() != block_size) {
            std::cerr << "[FAIL] XSM[" << i << "] = "
                      << xsm.get(i, i).to_uint16()
                      << " expected " << block_size << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int verify_1_bit_per_diagonal() {
    std::cout << "verify_1_bit_per_diagonal()" << std::endl;
    DiagonalSumMatrix xsm;

    for (uint16_t i = 0; i < block_size; ++i)
        xsm.increment(i, i);

    for (uint16_t i = 0; i < block_size; ++i) {
        if (xsm.get(i, i).to_uint16() != 1) {
            std::cerr << "[FAIL] XSM[" << i << "] = "
                      << xsm.get(i, i).to_uint16()
                      << " expected 1" << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int verify_transform_distribution() {
    std::cout << "verify_transform_distribution()" << std::endl;
    const DiagonalSumMatrix xsm;
    std::map<CrossSumIndex, int> value_count;

    for (CrossSumIndex r = 0; r < block_size; ++r)
        for (CrossSumIndex c = 0; c < block_size; ++c)
            value_count[xsm.transform(r, c)]++;

    if (value_count.size() != block_size) {
        std::cerr << "[FAIL] XSM transform() did not produce full index range. "
                  << "Expected " << block_size << " but got " << value_count.size() << std::endl;
        return EXIT_FAILURE;
    }

    for (const auto& [index, count] : value_count) {
        if (count != block_size) {
            std::cerr << "[FAIL] XSM transform index " << index
                      << " appeared " << count << " times, expected " << block_size << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int main() {
    try {
        if (const int exit = verify_100pct_set(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_1_bit_per_diagonal(); exit != EXIT_SUCCESS) return exit;
        if (const int exit = verify_transform_distribution(); exit != EXIT_SUCCESS) return exit;

        std::cout << "[PASS] DiagonalSumMatrix diagonal encoding verified." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
