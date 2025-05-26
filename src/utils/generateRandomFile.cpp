/**
 * @file generateRandomFile.cpp
 * @brief generate a file with a given name and size and random content.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/generateRandomFile.h"

/**
 * @name generateRandomFile
 * @brief generate a file with a given name and size and random content.
 * @param filename
 * @param file_size
 */
void generateRandomFile(const std::string& filename, const int file_size) {

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to create test input file");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> distrib(0, 255);

    for (size_t i = 0; i < file_size; ++i) {
        uint8_t byte = distrib(gen);
        ofs.write(reinterpret_cast<char*>(&byte), 1);
    }
}
