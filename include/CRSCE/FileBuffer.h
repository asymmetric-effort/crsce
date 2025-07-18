/**
 * @file include/CRSCE/FileBuffer.h
 * @brief Declare a FileBuffer as a vector of 64-bit values.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <vector>
#include <cstdint>

constexpr size_t FILE_BUFFER_WIDTH = 64;

using FileBuffer = std::vector<uint64_t>;
