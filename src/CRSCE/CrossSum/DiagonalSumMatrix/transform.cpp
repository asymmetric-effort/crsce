/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/transform.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
/**
 * @name transform
 * @class DiagonalSumMatrix
 * @brief transform the 2D (r,c) coordinates to 1D 0,...,s-1
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 */
CrossSumIndex DiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) {
    bounds_check(r);
    bounds_check(c);
    return (r + c) % s;
}
