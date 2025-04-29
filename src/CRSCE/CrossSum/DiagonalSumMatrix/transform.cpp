// file: include/CRSCE/CrossSum/DiagonalSumMatrix/transform.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"

//Translate 2D coordinates(r,c) into 1D linear address (D)
CrossSumIndex DiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) const {
    bounds_check(r,s);
    bounds_check(c,s);
    return (r + c) % s;
}
