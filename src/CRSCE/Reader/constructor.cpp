/**
 * @file include/CRSCE/Reader/CrossSumValue.cpp
 * @brief Declare the CRSCE reader class which will read raw data into the CRSCE compressor.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"

/**
 * @name constructor
 * @class Reader
 * @memberof CRSCE
 * @param inputFile std::string filename
 * @param outputFile std::string filename
 * @brief initialize the class state
 */
Reader::Reader(
        const std::string& inputFile,
        const std::string& outputFile
    ) : CRSCE(inputFile, outputFile) {/* noop */}
