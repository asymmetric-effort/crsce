// file: test/z3-verify-multi-block-compression.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include "CRSCE/constants/constants.h"
#include "utils/generate_temp_filename.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>

bool create_multi_block_file(const std::string& path, size_t block_count) {
    std::string input_path = generate_temp_filename("z3_input", "bin");
    std::ofstream input(input_path, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "[FAIL] Could not open temp input file." << std::endl;
        return false;
    }

    size_t total_bits = s * s * block_count;
    size_t total_bytes = (total_bits + 7) / 8;
    for (size_t i = 0; i < total_bytes; ++i)
        input.put(0xAA);  // Alternating pattern for visibility
    input.close();

    CRSCE compressor(input_path, path);
    return (compressor.compress() == EXIT_SUCCESS);
}

bool check_block_count(const std::string& path, size_t expected_blocks) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[FAIL] Could not open file: " << path << std::endl;
        return false;
    }
    file.seekg(-2 * sizeof(uint64_t), std::ios::end);
    uint64_t block_size = 0, block_count = 0;
    file.read(reinterpret_cast<char*>(&block_size), sizeof(block_size));
    file.read(reinterpret_cast<char*>(&block_count), sizeof(block_count));

    std::cout << "[DEBUG] Footer block size: " << block_size << ", block count: " << block_count << std::endl;
    if (block_count != expected_blocks) {
        std::cerr << "[FAIL] Block count mismatch in " << path << ". Expected: " << expected_blocks << ", Got: " << block_count << std::endl;
        return false;
    }
    std::cout << "[PASS] Verified " << expected_blocks << " block(s) in " << path << std::endl;
    return true;
}

int main() {
    std::vector<size_t> tests = {2, 3, 10};
    bool all_passed = true;

    for (size_t blocks : tests) {
        std::string output_path = generate_temp_filename("z3_output", "crsce");
        std::cout << "[INFO] Testing " << blocks << " block(s)..." << std::endl;
        std::cout << "[DEBUG] Attempting compression to: " << output_path << std::endl;
        if (!create_multi_block_file(output_path, blocks)) {
            std::cerr << "[FAIL] Compression failed for " << blocks << " block(s)." << std::endl;
            all_passed = false;
            continue;
        }
        if (!check_block_count(output_path, blocks)) {
            all_passed = false;
        }
    }

    return all_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}