// file: test/3000_verify-lhash1-push.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
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
    Tester tester("test/3000_verify-lhash1-push", TerminateOnError);
    tester.deadline(60);
    tester.skip("disabled for debug");

    TestLHashMatrix matrix;

    CrossSumIndex row = 0;
    CrossSumIndex col = 0;
    bool value = true;

    matrix.push(row, col, value);
    tester.debug(std::format("Pushed bit at ({},{})={}",row,col,value));

    // Verify bit value
    bool stored_value = matrix.debug_get_bit(row, col);
    tester.assertNotEqual(
        stored_value,
        value,
        std::format(
            "Bit at ({},{}) was {}, expected {}",
            row, col, stored_value, value
        )
    );

    // Verify row position incremented to 1
    size_t position = matrix.debug_get_row_position(row);

    tester.assertEqual(position,size_t(1),std::format("Row position for row {} is {} expected 1",row,position));

    tester.pass("verify-lhash1-push completed successfully.");
    return EXIT_SUCCESS;
}
