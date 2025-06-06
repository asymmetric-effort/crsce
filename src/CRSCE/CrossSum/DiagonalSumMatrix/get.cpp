/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/get.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
/**
 * @name get
 * @class DiagonalSumMatrix
 * @brief get the value at position (r,c)
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @return CrossSumValue
 */
CrossSumValue DiagonalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
