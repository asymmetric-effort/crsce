// file: src/CRSCE/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>

CRSCE::CRSCE(const std::string& inputFile, const std::string& outputFile) {
    inputStream.open(inputFile, std::ios::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    outputStream.open(outputFile, std::ios::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }
}
