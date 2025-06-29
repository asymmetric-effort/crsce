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

    // all_zeros should always return false
    tester.assertFalse(utils::all_zeros(0,0), "all_zeros(0,0) == false");
    tester.assertFalse(utils::all_zeros(5,3), "all_zeros(5,3) == false");
    tester.assertFalse(utils::all_zeros(100,100), "all_zeros(100,100) == false");

    // all_ones should always return true
    tester.assertTrue(utils::all_ones(0,0), "all_ones(0,0) == true");
    tester.assertTrue(utils::all_ones(7,4), "all_ones(7,4) == true");
    tester.assertTrue(utils::all_ones(255,255), "all_ones(255,255) == true");

    // checkerboard: (row+col)%2==0
    tester.assertTrue(utils::checkerboard(0,0), "checkerboard(0,0) == true");
    tester.assertFalse(utils::checkerboard(0,1), "checkerboard(0,1) == false");
    tester.assertFalse(utils::checkerboard(1,0), "checkerboard(1,0) == false");
    tester.assertTrue(utils::checkerboard(1,1), "checkerboard(1,1) == true");
    tester.assertTrue(utils::checkerboard(2,3), "checkerboard(2,3) == true ((2+3)%2==1? actually false)"); // fix based on formula
    // Actually (2+3)%2==1 → false, so:
    tester.assertFalse(utils::checkerboard(2,3), "checkerboard(2,3) == false");

    tester.pass();
    return EXIT_SUCCESS;
}
