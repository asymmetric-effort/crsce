/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/set.h
 * @brief Declares the CRSCE Antidiagonal Cross Sum Matrix (XSM) class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

/**
 * @name set
 * @class AntidiagonalSumMatrix
 * @brief This function sets the CrossSumValue at position (r,c).
 * @memberof CrossSum
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @param v CrossSumValue
 */
void AntidiagonalSumMatrix::set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) {
    data[transform(r, c)] = v;
}
