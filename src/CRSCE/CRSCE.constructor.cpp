/**
 * @file src/CRSCE/CrossSum.CrossSumValue.cpp
 * @brief define the CRSCE main class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>

/**
 * @name constructor
 * @class CRSCE
 * @brief Class Constructor opens the input and output files, then initializes the compression/decompression
 *        common assets
 * @param inputFile std::string
 * @param outputFile std::string
 */
CRSCE::CRSCE(const std::string &inputFile, const std::string &outputFile) {
    inputStream.open(inputFile, std::ifstream::in | std::ios::binary);

    if (!inputStream.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    outputStream.open(outputFile, std::ofstream::out | std::ios::binary);

    if (!outputStream.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }
}
