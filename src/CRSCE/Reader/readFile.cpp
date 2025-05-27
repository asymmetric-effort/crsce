/**
 * @file src/CRSCE/Reader/readFile.cpp
 * @brief Declare the CRSCE reader class which will read raw data into the CRSCE compressor.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"
/**
 * @name readFile
 * @class Reader
 * @memberof CRSCE
 * @param buffer FileBuffer
 * @return bool
 * @brief exposed readFile() function for testing.
 */
bool Reader::readFile(FileBuffer& buffer) {
    return CRSCE::readInputBuffer(buffer);
}
