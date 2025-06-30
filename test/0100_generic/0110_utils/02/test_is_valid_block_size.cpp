/**
 * @file test/0100_utils/is_valid_block_size.cpp
 * @brief Unit tests for utils::is_valid_block_size() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/is_valid_block_size.h"
#include "utils/test/Tester.h"

int main() {
    Tester tester("utils::is_valid_block_size");

    // Happy‐path cases
    tester.assertTrue(utils::is_valid_block_size(512),"512 is valid");
    tester.assertTrue(utils::is_valid_block_size(1024),"1024 is valid");
    tester.assertTrue(utils::is_valid_block_size(2048),"2048 is valid");
    tester.assertTrue(utils::is_valid_block_size(4096),"4096 is valid");

    tester.assertFalse(utils::is_valid_block_size(0),"0 is not valid");
    tester.assertFalse(utils::is_valid_block_size(511),"511 is not valid");
    tester.assertFalse(utils::is_valid_block_size(513),"513 is not valid");
    tester.assertFalse(utils::is_valid_block_size(1000),"1000 is not valid");
    tester.assertFalse(utils::is_valid_block_size(5000),"5000 is not valid");
    tester.assertFalse(utils::is_valid_block_size(12345),"12345 is not valid");
    tester.pass();
    return EXIT_SUCCESS;
}
