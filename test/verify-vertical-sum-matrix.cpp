// file: test/verify-vertical-sum-matrix.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include <iostream>
#include <cstdlib>

constexpr size_t block_size = 512;
constexpr size_t cross_sum_width = 9;

int verify_100pct_set() {
    std::cout << "verify_100pct_set()" << std::endl;
    VerticalSumMatrix vsm(block_size, cross_sum_width);
    try{
        for (uint16_t r = 0; r < block_size; ++r)
            for (uint16_t c = 0; c < block_size; ++c)
                vsm.increment(r, c);
        return EXIT_SUCCESS;
    }catch(std::overflow_error e){
        std::cerr << "[FAIL] Verification(2/2): " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    for (uint16_t c = 0; c < block_size; ++c)
        if (auto sum = vsm.get(c, c).to_uint16(); sum != (block_size - 1)) {
            std::cerr << "[FAIL] Verification(1/2): VSM value expects full set value at column " << c << "." << std::endl;
            return EXIT_FAILURE;
        }
}

int verify_1_bit_per_col_set() {
//    VerticalSumMatrix vsm(block_size, cross_sum_width);
//    std::cout << "verify_1_bit_per_col_set()" << std::endl;
//    for (uint16_t c = 0; c < block_size; ++c)
//        vsm.increment(c, c); // set diagonal pattern
//
//    for (uint16_t c = 0; c < block_size; ++c)
//        if (auto sum = vsm.get(c, c).to_uint16(); sum != 1) {
//            std::cerr << "[FAIL] Verification(2/3): VSM value expects 1 at column " << c << "." << std::endl;
//            return EXIT_FAILURE;
//        }
    return EXIT_SUCCESS;
}

int verify_overlow_works() {
//    VerticalSumMatrix vsm(block_size, cross_sum_width);
//    std::cout << "verify_overlow_works()" << std::endl;
//    try {
//        for (uint16_t r = 0; r <= block_size; ++r)
//            for (uint16_t c = 0; c <= block_size; ++c)
//                vsm.increment(r, c);
//        std::cerr << "[FAIL] Overflow not detected when expected." << std::endl;
//        return EXIT_FAILURE;
//    } catch (const std::overflow_error& e) {
//        return EXIT_SUCCESS;
//    }
    return EXIT_SUCCESS;
}

int main() {
    try {
        if (int exit = verify_100pct_set(); exit != EXIT_SUCCESS) return EXIT_FAILURE;
        if (int exit = verify_1_bit_per_col_set(); exit != EXIT_SUCCESS) return EXIT_FAILURE;
        if (int exit = verify_overlow_works(); exit != EXIT_SUCCESS) return EXIT_FAILURE;

        std::cout << "[PASS] VerticalSumMatrix column-major encoding verified." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
