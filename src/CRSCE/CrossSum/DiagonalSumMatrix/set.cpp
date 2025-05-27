/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/set.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
/**
 * @name set
 * @class DiagonalSumMatrix
 * @brief set the value at position (r,c)
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @param value CrossSumValue
 */
void DiagonalSumMatrix::set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) {
    data[transform(r,c)]=v;
}
