/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/transform.h
 * @brief Declares the CRSCE Antidiagonal Cross Sum Matrix (XSM) class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

/**
 * @name set
 * @class AntidiagonalSumMatrix
 * @brief Translate 2D coordinates(r,c) into 1D linear address (x)
 * @memberof CrossSum
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @param v CrossSumValue
 */
CrossSumIndex AntidiagonalSumMatrix::transform(const CrossSumIndex r, const CrossSumIndex c) {
    bounds_check(r);
    bounds_check(c);
    return (s + (r - c)) % s;
}
