/**
 * @file 9000_final-compression-test.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"
#include "CRSCE/constants/constants.h"
#include "utils/get_tmp_dir.h"
#include "utils/TestPatterns.h"
#include "utils/generate_temp_filename.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Write pattern into a temporary input file, then call CRSCE::compress()
bool run_compression_pattern(const TestPattern& pattern) {
    std::cout << "[INFO] Running compression pattern: " << pattern.name << std::endl;

    std::string input_filename = utils::generate_temp_filename("tmp_input", "bin");
    std::string output_filename = utils::generate_temp_filename("tmp_output", "crsce");
    std::ofstream input(input_filename, std::ios::binary);

    if (!input.is_open()) {
        std::cerr << "[FAIL] Could not open input file for writing." << std::endl;
        return false;
    }

    // Write the pattern as bytes row-wise into the file
    for (size_t r = 0; r < s; ++r) {
        uint8_t current_byte = 0;
        int bit_count = 0;
        for (size_t c = 0; c < s; ++c) {
            current_byte <<= 1;
            if (pattern.generator(r, c)) current_byte |= 1;
            bit_count++;

            if (bit_count == 8) {
                input.put(static_cast<char>(current_byte));
                current_byte = 0;
                bit_count = 0;
            }
        }
        if (bit_count > 0) {
            current_byte <<= (8 - bit_count);
            input.put(static_cast<char>(current_byte));
        }
    }
    input.close();

    // Setup CRSCE and call compression
    CRSCE compressor(input_filename, output_filename);

    if (const int result = compressor.compress(); result != EXIT_SUCCESS) {
        std::cerr << "[FAIL] CRSCE::compress() failed for pattern " << pattern.name << std::endl;
        return false;
    }

    // Verify output file size is at least non-zero and aligned to expected structure
    std::ifstream output(output_filename, std::ios::binary | std::ios::ate);
    if (!output.is_open()) {
        std::cerr << "[FAIL] Could not open output file for reading." << std::endl;
        return false;
    }

    std::streamsize size = output.tellg();
    if (size <= 0) {
        std::cerr << "[FAIL] Output file is empty." << std::endl;
        return false;
    }

    std::cout << "[PASS] Pattern " << pattern.name << " - Compressed output size: " << size << " bytes." << std::endl;
    return true;
}

int main() {
    std::vector<TestPattern> patterns = {
        {"All Zeros", all_zeros},
        {"All Ones", all_ones},
        {"Checkerboard", checkerboard}
    };

    for (const auto& pattern : patterns) {
        if (const bool success = run_compression_pattern(pattern); !success)
            return EXIT_FAILURE;
        std::cout << "[PASS] zzz-final-compression-test completed successfully." << std::endl;
    }
    return EXIT_SUCCESS;
}
