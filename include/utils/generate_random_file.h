/**
 * @file utils/generate_random_file.h
 * @brief generate a file with a given name and size and random content.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <fstream>

namespace utils {
    /**
     * @name generate_random_file
     * @brief generate a file with a given name and size and random content.
     * @param filename
     * @param file_size
     */
    void generate_random_file(const std::string& filename, int file_size);
}
