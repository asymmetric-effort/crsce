/**
 * @file src/CRSCE/CrossSum.CRSCE.destructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>

/**
 * @name destructor
 * @class CRSCE
 * @brief close any open files.
 * @param inputFile std::string
 * @param outputFile std::string
 */
CRSCE::~CRSCE() {
    if (inputStream.is_open()) inputStream.close();
    if (outputStream.is_open()) outputStream.close();
}
