/**
 * @file src/CRSCE/LHashMatrix/constructor.cpp
 * @brief Define a one-dimensional matrix of row-aligned hashes.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"

/**
 * @name constructor
 * @class LHashMatrix
 * @brief initialize the values with zeroes
 */
LHashMatrix::LHashMatrix() {
    row_positions.fill(0);
}
