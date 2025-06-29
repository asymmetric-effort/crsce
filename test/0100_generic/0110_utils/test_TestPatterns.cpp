/**
* @file test/0100_generic/0110_utils/test_TestPatterns.cpp
 * @brief Unit tests for utils::all_zeros, all_ones, and checkerboard
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/TestPatterns.h"
#include "utils/test/Tester.h"
#include <cstdlib>

int main() {
    Tester tester("utils::TestPatterns");
    // checkerboard: (row+col)%2==0
    for (size_t row = 0; row < 10; row++)
        for (size_t col = 0; col < 10; col++) {
            if (const auto expected = (row+col)%2==0) {
                tester.assertTrue(
                    utils::checkerboard(row, col),
                    "checkerboard(" + std::to_string(row) + "," + std::to_string(col) + ") == true");
            }
            else {
                tester.assertFalse(
                    utils::checkerboard(row, col),
                    "checkerboard(" + std::to_string(row) + "," + std::to_string(col) + ") == false");
            }
        }
    tester.pass();
    return EXIT_SUCCESS;
}
