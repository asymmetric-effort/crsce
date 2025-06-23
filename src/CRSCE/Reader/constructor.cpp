/**
 * @file include/CRSCE/Reader/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"
#include "utils/Exceptions/FileOpenFailed.h"

Reader::Reader(
        const std::string& inputFile,
        const std::string& outputFile
    ) {

    inputStream.open(inputFile, std::ifstream::in | std::ios::binary);

    if (!inputStream.is_open()) {
        throw Exceptions::FileOpenFailed(inputFile);
    }

    outputStream.open(outputFile, std::ofstream::out | std::ios::binary);

    if (!outputStream.is_open()) {
        throw Exceptions::FileOpenFailed(outputFile);
    }

}
