/**
 * @file src/CRSCE/CRSCE.readInputBuffer.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"
#include <iostream>
#include <vector>

// readInputBuffer - read the input file byte for byte
bool CRSCE::readInputBuffer(FileBuffer& buffer) {
    buffer.resize(INPUT_BUFFER_SIZE);
    inputStream.read(reinterpret_cast<char*>(buffer.data()), INPUT_BUFFER_SIZE);
    const std::streamsize bytesRead = inputStream.gcount();
    buffer.resize(static_cast<size_t>(bytesRead));
    return bytesRead > 0;
}
