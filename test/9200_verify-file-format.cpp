/**
 * @file 9000_verify-file-format.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/constants/constants.h"
#include "CRSCE/CRSCE.h"
#include "utils/test/Tester.h"
#include "utils/generate_temp_filename.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

bool generate_test_compression(const std::string &output_path) {
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

    if (CRSCE compressor(input_path, output_path); compressor.compress() != EXIT_SUCCESS) {
        std::cerr << "[FAIL] Compression failed during setup." << std::endl;
        return false;
    }

    std::cout << "[PASS] Test compression file generated at " << output_path << std::endl;
    return true;
}

bool verify_header(std::ifstream &in) {
    const size_t header_len = HEADER.length();  // runtime-safe
    std::vector<char> header_buffer(header_len);  // avoid VLA

    in.seekg(0, std::ios::beg);
    in.read(header_buffer.data(), header_len);
    if (!in) {
        std::cerr << "[FAIL] Could not read header from file." << std::endl;
        return false;
    }
    if (std::memcmp(header_buffer.data(), HEADER.c_str(), header_len) != 0) {
        std::cerr << "[FAIL] Header does not match expected CRSCE signature." << std::endl;
        std::cerr << "[DEBUG] Read:   " << std::string(header_buffer.begin(), header_buffer.end()) << std::endl;
        std::cerr << "[DEBUG] Expect: " << HEADER << std::endl;
        return false;
    }
    std::cout << "[PASS] Header verified." << std::endl;
    return true;
}

bool verify_footer(std::ifstream &in) {
    // cppcheck-suppress signConversion
    in.seekg(-2 * sizeof(uint64_t), std::ios::end);
    if (!in) {
        std::cerr << "[FAIL] Failed to seek to footer." << std::endl;
        return false;
    }

    uint64_t block_size = 0;
    uint64_t block_count = 0;
    in.read(reinterpret_cast<char *>(&block_size), sizeof(block_size));
    in.read(reinterpret_cast<char *>(&block_count), sizeof(block_count));

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

bool verify_structure(const std::ifstream &in, const std::streamsize actual_size, const uint64_t block_count) {
    constexpr size_t footer_bytes = 2 * sizeof(uint64_t);
    const size_t header_bytes = HEADER.length();
    constexpr size_t lateral_bits = 4 * s * b;
    constexpr size_t lateral_bytes = (lateral_bits + 7) / 8;
    constexpr size_t lhash_bytes = s * 32;
    constexpr size_t block_bytes = lateral_bytes + lhash_bytes;
    const size_t expected_size = static_cast<size_t>(std::ceil(
        static_cast<double>(header_bytes + block_count * block_bytes + footer_bytes)));

    if (static_cast<std::size_t>(actual_size) != expected_size) {
        std::cerr << "[FAIL] File size mismatch." << std::endl;
        std::cerr << "        Actual:   " << actual_size << " bytes" << std::endl;
        std::cerr << "        Expected: " << expected_size << " bytes" << std::endl;
        return false;
    }
    std::cout << "[PASS] File size matches expected structure layout." << std::endl;
    return true;
}

int main(const int argc, const char *argv[]) {
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

    const bool header_ok = verify_header(infile);
    const bool footer_ok = verify_footer(infile);

    infile.seekg(0, std::ios::end);
    const std::streamsize total_size = infile.tellg();
    // cppcheck-suppress signConversion
    infile.seekg(-2 * sizeof(uint64_t), std::ios::end);
    uint64_t block_size = 0;
    uint64_t block_count = 0;
    infile.read(reinterpret_cast<char *>(&block_size), sizeof(block_size));
    infile.read(reinterpret_cast<char *>(&block_count), sizeof(block_count));

    const bool structure_ok = verify_structure(infile, total_size, block_count);

    return (header_ok && footer_ok && structure_ok) ? EXIT_SUCCESS : EXIT_FAILURE;
}
