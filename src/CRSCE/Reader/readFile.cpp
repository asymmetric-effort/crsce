// file: src/CRSCE/Reader/readFile.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/Reader.h"

// exposed readFile() function for testing.
bool Reader::readFile(ByteBuffer& buffer) {
    return CRSCE::readInputBuffer(buffer);
}
