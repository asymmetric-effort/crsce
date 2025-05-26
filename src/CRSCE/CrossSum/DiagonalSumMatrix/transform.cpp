/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/transform.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"

//Translate 2D coordinates(r,c) into 1D linear address (D)
CrossSumIndex DiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) const {
    bounds_check(r);
    bounds_check(c);
    return (r + c) % s;
}
