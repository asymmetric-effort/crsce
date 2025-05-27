/**
 * @file src/CRSCE/Reader/write.cpp
 * @brief Declare the CRSCE reader class which will read raw data into the CRSCE compressor.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"
#include <fstream>

/**
 * @name write
 * @class Reader
 * @memberof CRSCE
 * @param buffer FileBuffer
 * @brief write the compressed content to the target file
 */
void Reader::write(FileBuffer& buffer) {
    outputStream.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
}
