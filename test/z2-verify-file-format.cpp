// file: test/z2-verify-file-format.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/constants/constants.h"
#include "CRSCE/CRSCE.h"
#include "utils/TestPatterns.h"
#include "utils/generate_temp_filename.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

bool generate_test_compression(const std::string& output_path) {
    std::string input_path = generate_temp_filename("z2_input", "bin");

    // Create all-zero test input block (s x s bits = 32640+1 bits → 4080 bytes)
    std::ofstream input(input_path, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "[FAIL] Could not open temp input file for writing." << std::endl;
        return false;
    }
    size_t total_bits = s * s;
    size_t total_bytes = (total_bits + 7) / 8;
    for (size_t i = 0; i < total_bytes; ++i)
        input.put(0x00);
    input.close();

    CRSCE compressor(input_path, output_path);
    if (compressor.compress() != EXIT_SUCCESS) {
        std::cerr << "[FAIL] Compression failed during setup." << std::endl;
        return false;
    }

    std::cout << "[PASS] Test compression file generated at " << output_path << std::endl;
    return true;
}

bool verify_header(std::ifstream &in) {
    char header_buffer[HEADER_LENGTH];
    in.seekg(0, std::ios::beg);
    in.read(header_buffer, HEADER_LENGTH);
    if (!in) {
        std::cerr << "[FAIL] Could not read header from file." << std::endl;
        return false;
    }
    if (std::memcmp(header_buffer, HEADER, HEADER_LENGTH) != 0) {
        std::cerr << "[FAIL] Header does not match expected CRSCE signature." << std::endl;
        std::cerr << "[DEBUG] Read:   ";
        for (int i = 0; i < HEADER_LENGTH; ++i) std::cerr << header_buffer[i];
        std::cerr << "\n[DEBUG] Expect: ";
        for (int i = 0; i < HEADER_LENGTH; ++i) std::cerr << HEADER[i];
        std::cerr << std::endl;
        return false;
    }
    std::cout << "[PASS] Header verified." << std::endl;
    return true;
}

bool verify_footer(std::ifstream &in) {
    in.seekg(-2 * sizeof(uint64_t), std::ios::end);
    if (!in) {
        std::cerr << "[FAIL] Failed to seek to footer." << std::endl;
        return false;
    }

    uint64_t block_size = 0;
    uint64_t block_count = 0;
    in.read(reinterpret_cast<char*>(&block_size), sizeof(block_size));
    in.read(reinterpret_cast<char*>(&block_count), sizeof(block_count));

    if (!in) {
        std::cerr << "[FAIL] Could not read footer." << std::endl;
        return false;
    }

    if (block_size != s) {
        std::cerr << "[FAIL] Footer block size mismatch. Expected " << s << ", got " << block_size << std::endl;
        return false;
    }

    std::cout << "[PASS] Footer verified. Block size: " << block_size << ", Block count: " << block_count << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    std::string filepath;
    if (argc == 2) {
        filepath = argv[1];
    } else {
        filepath = generate_temp_filename("z2_output", "crsce");
        std::cerr << "[INFO] No file specified. Generating test file at: " << filepath << std::endl;
        if (!generate_test_compression(filepath)) return EXIT_FAILURE;
    }

    std::ifstream infile(filepath, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "[FAIL] Could not open input file: " << filepath << std::endl;
        return EXIT_FAILURE;
    }

    bool header_ok = verify_header(infile);
    bool footer_ok = verify_footer(infile);

    return (header_ok && footer_ok) ? EXIT_SUCCESS : EXIT_FAILURE;
}
