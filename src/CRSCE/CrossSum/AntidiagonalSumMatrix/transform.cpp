// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix/transform.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

//Translate 2D coordinates(r,c) into 1D linear address (x)
CrossSumIndex AntidiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) const {
    bounds_check(r);
    bounds_check(c);
    return (r - c) % s;
}
`