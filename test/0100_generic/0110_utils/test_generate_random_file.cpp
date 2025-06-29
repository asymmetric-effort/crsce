/**
* @file test/0100_generic/0110_utils/test_generate_random_file.cpp
 * @brief Unit tests for utils::generate_random_file() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/generate_random_file.h"
#include "utils/test/Tester.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>

int main() {
    Tester tester("utils::generate_random_file");

    namespace fs = std::filesystem;

    const std::string filename = "test_rand_file.bin";
    const int file_size = 1024;  // 1 KB

    // Generate the random file
    utils::generate_random_file(filename, file_size);

    // 1) File should exist
    tester.assertTrue(fs::exists(filename), "Generated file exists");

    // 2) File size should match requested size
    std::error_code ec;
    auto actual_size = fs::file_size(filename, ec);
    tester.assertTrue(!ec, "file_size did not set an error");
    tester.assertTrue(actual_size == static_cast<uintmax_t>(file_size),
                     "Generated file has correct size");

    // 3) Contents should not be all zeros (i.e., contain at least one non-zero byte)
    std::ifstream in(filename, std::ios::binary);
    tester.assertTrue(in.is_open(), "Able to open generated file");
    bool non_zero_found = false;
    char c;
    while (in.get(c)) {
        if (static_cast<unsigned char>(c) != 0) {
            non_zero_found = true;
            break;
        }
    }
    tester.assertTrue(non_zero_found, "Generated file contains non-zero bytes");

    // Cleanup
    fs::remove(filename, ec);

    tester.pass();
    return EXIT_SUCCESS;
}
