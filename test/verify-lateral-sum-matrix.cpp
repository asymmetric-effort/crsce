// file: test/verify-lateral-sum-matrix.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include <iostream>
#include <cstdlib>

int verify_100pct_set(){

    constexpr size_t block_size = 512;

    constexpr size_t cross_sum_width = 9;

    LateralSumMatrix lsm(block_size, cross_sum_width);

    std::cout << "verify_100pct_set()" << std::endl;
    for (uint16_t r = 0; r < block_size; ++r)
        for (uint16_t c = 0; c < block_size - 1; ++c) // 0..510
            lsm.increment(r, c);

    for(uint16_t r = 0; r < block_size; r++)
        if(auto sum=lsm.get(r,r).to_uint16(); sum != (block_size-1)){
            std::cerr << "[FAIL] Verification(1/3): LSM value expects full set value." << std::endl;
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}

int verify_1_bit_per_row_set() {
    constexpr size_t block_size = 512;
    constexpr size_t cross_sum_width = 9;
    LateralSumMatrix lsm(block_size, cross_sum_width);
    std::cout << "verify_1_bit_per_row_set()" << std::endl;
    for (uint16_t r = 0; r < block_size; ++r)
      lsm.increment(r, r); // set diagonal pattern

    for (uint16_t r = 0; r < block_size; ++r)
        if (auto sum = lsm.get(r, r).to_uint16(); sum != 1) {
            std::cerr << "[FAIL] Verification(1/3): LSM value expects 1 value." << std::endl;
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS; // Must return success if all OK
}

int verify_overlow_works(){
    constexpr size_t block_size = 512;
    constexpr size_t cross_sum_width = 9;
    LateralSumMatrix lsm(block_size, cross_sum_width);
    std::cout << "verify_overlow_works()" << std::endl;
    try{
        for (uint16_t r = 0; r <= block_size; ++r)
            for(uint16_t c = 0; c <= block_size; ++c)
                lsm.increment(r, c); // set diagonal pattern
        std::cerr << "set oversize value should cause overflow." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::overflow_error& e) {
        return EXIT_SUCCESS;
    }
}

int main() {
    try {

        if(int exit=verify_100pct_set();exit!=EXIT_SUCCESS) return EXIT_FAILURE;

        if(int exit=verify_1_bit_per_row_set();exit!=EXIT_SUCCESS) return EXIT_FAILURE;

        if(int exit=verify_overlow_works();exit!=EXIT_SUCCESS) return EXIT_FAILURE;

        std::cout << "[PASS] LateralSumMatrix row-major encoding verified." << std::endl;

        return EXIT_SUCCESS;

    } catch (const std::exception& e) {

        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;

        return EXIT_FAILURE;

    }

}
