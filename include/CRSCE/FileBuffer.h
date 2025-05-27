/**
 * @file include/CRSCE/FileBuffer.h
 * @brief Declare a FileBuffer as a vector of 64-bit values.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_FILE_BUFFER_H
#define CRSCE_FILE_BUFFER_H

#include <vector>
/**
 * @property FILE_BUFFER_WIDTH
 * @brief the size of the file buffer
 */
constexpr size_t FILE_BUFFER_WIDTH = 64;
/**
 * @property FileBuffer
 * @brief an alias of std::vector<uint64_t> which should allow file reads in increments of 64-bytes.
 */
using FileBuffer = std::vector<uint64_t>;

#endif //CRSCE_FILE_BUFFER_H
