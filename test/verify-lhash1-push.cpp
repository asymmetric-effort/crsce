// file: test/verify-lhash1-push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <cstdlib>

class TestLHashMatrix : public LHashMatrix {
public:
    bool debug_get_bit(CrossSumIndex r, CrossSumIndex c) const {
        return row_buffers[r][c];
    }

    size_t debug_get_row_position(CrossSumIndex r) const {
        return row_positions[r];
    }

    std::string debug_get_row_hash(CrossSumIndex r) const {
        return row_hashes[r];
    }
};

int main() {
    std::cout << "[INFO] verify-lhash1-push starting..." << std::endl;

    TestLHashMatrix matrix;

    CrossSumIndex row = 0;
    CrossSumIndex col = 0;
    bool value = true;

    matrix.push(row, col, value);
    std::cout << "[INFO] Pushed bit at (" << row << ", " << col << ") = " << value << std::endl;

    // Verify bit value
    bool stored_value = matrix.debug_get_bit(row, col);
    if (stored_value != value) {
        std::cerr << "[FAIL] Bit at (" << row << ", " << col << ") was " << stored_value << ", expected " << value << std::endl;
        return EXIT_FAILURE;
    }

    // Verify row position incremented to 1
    size_t position = matrix.debug_get_row_position(row);
    if (position != 1) {
        std::cerr << "[FAIL] Row position for row " << row << " is " << position << ", expected 1" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "[PASS] verify-lhash1-push completed successfully." << std::endl;
    return EXIT_SUCCESS;
}
