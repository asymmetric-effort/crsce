/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/increment.h
 * @brief Declares the CRSCE Antidiagonal Cross Sum Matrix (XSM) class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

/**
 * @name increment
 * @class AntidiagonalSumMatrix
 * @brief This function increments the element at (r,c)
 * @memberof CrossSum
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 */
void AntidiagonalSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) {
    data[transform(r,c)]++;
}
