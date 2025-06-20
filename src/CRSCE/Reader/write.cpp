/**
 * @file src/CRSCE/Reader/write.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"
#include <fstream>

void Reader::write(const FileBuffer& buffer) {
    outputStream.write(
        reinterpret_cast<const char*>(buffer.data()),
        static_cast<std::streamsize>(buffer.size() * sizeof(FileBuffer::value_type))
    );
}
