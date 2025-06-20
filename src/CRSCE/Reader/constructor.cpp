/**
 * @file include/CRSCE/Reader/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"

Reader::Reader(
        const std::string& inputFile,
        const std::string& outputFile
    ) : CRSCE(inputFile, outputFile) {/* noop */}
