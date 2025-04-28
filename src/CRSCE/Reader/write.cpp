// file: src/CRSCE/Reader/write.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/Reader.h"
#include <fstream>

void Reader::write(FileBuffer& buffer) {
    outputStream.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
}
