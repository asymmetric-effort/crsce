// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix_transform.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/AntidiagonalSumMatrix.h"

//Translate 2D coordinates(r,c) into 1D linear address (x)
CrossSumIndex AntidiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) const {
    return (r - c) % s
}
