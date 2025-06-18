/**
 * @file 9600_verify-multi-block-compression.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"
#include "CRSCE/constants/constants.h"
#include "utils/generate_temp_filename.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

// Create an input file with `blocks` worth of data (bytes padded)
bool create_multi_block_file(const std::string& path, size_t blocks) {
    std::string input_path = generate_temp_filename("z3_input", "bin");
    std::ofstream input(input_path, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "[FAIL] Could not open temp input file." << std::endl;
        return false;
    }

    // Write alternating pattern bytes
    size_t bits = blocks * s * s;
    size_t bytes = (bits + 7) / 8;  // pad up to full byte
    for (size_t i = 0; i < bytes; ++i)
        input.put(0xAA);
    input.close();

    CRSCE compressor(input_path, path);
    return (compressor.compress() == EXIT_SUCCESS);
}

// Check footer's block count matches expected
bool check_block_count(const std::string& path, size_t expected_blocks) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[FAIL] Could not open file: " << path << std::endl;
        return false;
    }
    // Seek to footer
    // cppcheck-suppress signConversion
    file.seekg(-2 * sizeof(uint64_t), std::ios::end);
    uint64_t block_size = 0, block_count = 0;
    file.read(reinterpret_cast<char*>(&block_size), sizeof(block_size));
    file.read(reinterpret_cast<char*>(&block_count), sizeof(block_count));

    std::cout << "[DEBUG] Footer block size: " << block_size
              << ", block count: " << block_count << std::endl;

    if (block_count != expected_blocks) {
        std::cerr << "[FAIL] Block count mismatch in " << path
                  << ". Expected: " << expected_blocks
                  << ", Got: " << block_count << std::endl;
        return false;
    }
    std::cout << "[PASS] Verified " << expected_blocks
              << " block(s) in " << path << std::endl;
    return true;
}

int main() {
    std::vector<size_t> tests = {2, 3, 10};
    bool all_passed = true;

    for (size_t blocks : tests) {
        // Compute expected blocks accounting for byte padding
        size_t bits = blocks * s * s;
        size_t bytes = (bits + 7) / 8;
        size_t total_bits = bytes * 8;
        size_t expected = (total_bits + (s*s) - 1) / (s*s);

        std::string output_path = generate_temp_filename("z3_output", "crsce");
        std::cout << "[INFO] Testing " << blocks << " block(s)... (expecting " << expected << ")" << std::endl;
        if (!create_multi_block_file(output_path, blocks)) {
            std::cerr << "[FAIL] Compression failed for " << blocks << " block(s)." << std::endl;
            all_passed = false;
            continue;
        }
        if (!check_block_count(output_path, expected)) {
            all_passed = false;
        }
    }

    return all_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
