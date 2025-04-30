// file: test/AntiDiagonalCoordinateTransform.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <map>
#include <cstdlib>

int main() {
    try {
        AntidiagonalSumMatrix dsm;
        std::map<CrossSumIndex, int> index_count;

        for (CrossSumIndex r = 0; r < s; ++r) {
            for (CrossSumIndex c = 0; c < s; ++c) {
                CrossSumIndex i = dsm.transform(r, c);
                if (i >= s) {
                    std::cerr << "[FAIL] transform(" << r << "," << c << ") = " << i
                              << " out of bounds (max " << s - 1 << ")" << std::endl;
                    return EXIT_FAILURE;
                }
                index_count[i]++;
            }
        }

        if (index_count.size() != s) {
            std::cerr << "[FAIL] Antidiagonal index count map size is " << index_count.size()
                      << ", expected " << s << std::endl;
            return EXIT_FAILURE;
        }

        for (const auto& [index, count] : index_count) {
            if (count != s) {
                std::cerr << "[FAIL] Antidiagonal index " << index << " occurred "
                          << count << " times, expected " << s << std::endl;
                return EXIT_FAILURE;
            }
        }

        std::cout << "[PASS] AntidiagonalSumMatrix::transform() covers 0.." << s - 1
                  << " exactly " << s << " times each." << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
