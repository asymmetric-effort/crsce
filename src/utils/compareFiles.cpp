/**
 * @file utils/compareFiles.cpp
 * @brief compare two files.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/compareFiles.h"
#include <fstream>  // for std::ifstream
#include <cstring>  // for std::memcmp

/**
 * @name compareFiles
 * @brief Byte‐level comparison of two files.
 * @param lhs_file Path to the first file.
 * @param rhs_file Path to the second file.
 * @return true if files exist and have identical contents; false otherwise.
 */
bool compareFiles(const std::string& lhs_file, const std::string& rhs_file) {
    std::ifstream lhs_stream(lhs_file, std::ios::binary);
    std::ifstream rhs_stream(rhs_file, std::ios::binary);

    if (!lhs_stream.is_open() || !rhs_stream.is_open()) {
        return false;
    }

    constexpr std::size_t BufferSize = 4096;
    char lhs_buffer[BufferSize];
    char rhs_buffer[BufferSize];

    while (true) {
        lhs_stream.read(lhs_buffer, BufferSize);
        rhs_stream.read(rhs_buffer, BufferSize);

        std::streamsize lhs_read = lhs_stream.gcount();
        std::streamsize rhs_read = rhs_stream.gcount();

        if (lhs_read != rhs_read) {
            return false;
        }
        if (lhs_read == 0) {
            // both streams reached EOF simultaneously
            break;
        }
        if (std::memcmp(lhs_buffer, rhs_buffer, static_cast<std::size_t>(lhs_read)) != 0) {
            return false;
        }
    }

    return true;
}
