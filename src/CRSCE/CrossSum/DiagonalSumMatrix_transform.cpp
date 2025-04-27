// file: include/CRSCE/CrossSum/DiagonalSumMatrix_transform.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/DiagonalSumsMatrix.h"

//Translate 2D coordinates(r,c) into 1D linear address (D)
CrossSumIndex DiagonalSumsMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) const {
    return (r + c) % s
}
