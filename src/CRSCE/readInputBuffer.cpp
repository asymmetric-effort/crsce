// file: src/CRSCE/readInputBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"
#include <iostream>
#include <vector>
#include <cstring>

// readInputBuffer - read the input file byte for byte
bool CRSCE::readInputBuffer(std::vector<uint8_t>& buffer) {
    buffer.resize(INPUT_BUFFER_SIZE);
    inputStream.read(reinterpret_cast<char*>(buffer.data()), INPUT_BUFFER_SIZE);
    std::streamsize bytesRead = inputStream.gcount();
    buffer.resize(static_cast<size_t>(bytesRead));
    return bytesRead > 0;
}
