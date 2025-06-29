/**
 * @file src/CRSCE/CRSCE.constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "CRSCE/CRSCE.h"
#include "utils/Exceptions/FileOpenFailed.h"
#include <iostream>
#include <stdexcept>


// Class Constructor opens the input and output files, then initializes the compression/decompression common assets
CRSCE::CRSCE(const std::string& inputFile,
             const std::string& outputFile,
             const size_t block_size,
             const size_t concurrency)
    : block_size(block_size), concurrency(concurrency) {
    /**
     * open the input file and catch any error.
     */
    inputStream.open(inputFile, std::ifstream::in | std::ios::binary);
    if (!inputStream.is_open()) {
        throw Exceptions::FileOpenFailed(inputFile);
    }
    /**
     * open the output file and catch any error
     */
    outputStream.open(outputFile, std::ofstream::out | std::ios::binary);
    if (!outputStream.is_open()) {
        throw Exceptions::FileOpenFailed(outputFile);
    }
}
