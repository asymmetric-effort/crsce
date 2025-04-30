// file: test/verify-lhash1-push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "[INFO] verify-lhash1-push starting..." << std::endl;

    LHashMatrix matrix;

    CrossSumIndex row = 0;
    CrossSumIndex col = 0;
    bool value = true;

    matrix.push(row, col, value);

    std::cout << "[INFO] Pushed bit at (" << row << ", " << col << ") = " << value << std::endl;
    std::cout << "[PASS] verify-lhash1-push completed successfully." << std::endl;

    return EXIT_SUCCESS;
}
