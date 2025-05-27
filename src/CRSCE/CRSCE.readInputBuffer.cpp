/**
 * @file src/CRSCE/CRSCE.readInputBuffer.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"
#include <iostream>
#include <vector>
#include <cstring>
/**
 * @name readInputBuffer
 * @class CRSCE
 * @brief read the input file byte for byte
 * @protected
 * @param buffer FileBuffer
 * @return bool
 */
bool CRSCE::readInputBuffer(FileBuffer& buffer) {
    buffer.resize(INPUT_BUFFER_SIZE);
    inputStream.read(reinterpret_cast<char*>(buffer.data()), INPUT_BUFFER_SIZE);
    std::streamsize bytesRead = inputStream.gcount();
    buffer.resize(static_cast<size_t>(bytesRead));
    return bytesRead > 0;
}
