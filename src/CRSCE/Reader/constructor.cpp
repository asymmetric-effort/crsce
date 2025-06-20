/**
 * @file include/CRSCE/Reader/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"

Reader::Reader(
        const std::string& inputFile,
        const std::string& outputFile
    ) {

    inputStream.open(inputFile, std::ifstream::in | std::ios::binary);

    if (!inputStream.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    outputStream.open(outputFile, std::ofstream::out | std::ios::binary);

    if (!outputStream.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

}
