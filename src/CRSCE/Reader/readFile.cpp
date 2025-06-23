/**
 * @file src/CRSCE/Reader/readFile.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"

// exposed readFile() function for testing.
bool Reader::readFile(FileBuffer& buffer) {
    return readInputBuffer(buffer);
}

// readInputBuffer - read the input file byte for byte
bool Reader::readInputBuffer(FileBuffer& buffer) {
    buffer.resize(INPUT_BUFFER_SIZE);
    inputStream.read(reinterpret_cast<char*>(buffer.data()), INPUT_BUFFER_SIZE);
    const std::streamsize bytesRead = inputStream.gcount();
    buffer.resize(static_cast<size_t>(bytesRead));
    return bytesRead > 0;
}
