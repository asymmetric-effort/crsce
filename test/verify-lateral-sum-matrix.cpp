// file: test/verify-lateral-sum-matrix.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

int verify_100pct_set() {
    LateralSumMatrix lsm;

    try {
        for (uint16_t r = 0; r < s; ++r)
            for (uint16_t c = 0; c < s; ++c) // s-1
                lsm.increment(r, c);
    } catch (std::overflow_error& error) {
        std::cerr << "verify_100pct_set() failed(1): " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    try {
        for (uint16_t r = 0; r < s; ++r) {
            uint16_t actual = lsm.get(r, r).to_uint16();
            if (actual != s) {
                std::cerr << "[FAIL] LSM[" << r << "] = "
                          << actual
                          << " expected " << s << std::endl;
                return EXIT_FAILURE;
            }
        }
    } catch (std::overflow_error& error) {
        std::cerr << "verify_100pct_set() failed(2): " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int verify_1_bit_per_row_set() {
    LateralSumMatrix lsm;
    std::cout << "verify_1_bit_per_row_set()" << std::endl;
    for (uint16_t r = 0; r < s; ++r)
      lsm.increment(r, r); // set diagonal pattern
    for (uint16_t r = 0; r < s; ++r)
        if (auto sum = lsm.get(r, r).to_uint16(); sum != 1) {
            std::cerr << "[FAIL] Verification(2): LSM value expects 1 value." << std::endl;
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS; // Must return success if all OK
}

int verify_overlow_works(){
    LateralSumMatrix lsm;
    std::cout << "verify_overlow_works()" << std::endl;
    try{
        for (uint16_t r = 0; r <= s; ++r)
            for(uint16_t c = 0; c <= s; ++c)
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
