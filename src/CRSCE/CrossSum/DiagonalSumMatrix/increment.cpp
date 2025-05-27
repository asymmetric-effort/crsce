/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/increment.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
/**
 * @name increment
 * @class DiagonalSumMatrix
 * @brief increment the value at position (r,c)
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 */
void DiagonalSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) {
    ++data[transform(r,c)];
}
