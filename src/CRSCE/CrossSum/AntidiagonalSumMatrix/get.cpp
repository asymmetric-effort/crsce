/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/get.h
 * @brief Declares the CRSCE Antidiagonal Cross Sum Matrix (XSM) class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

/**
 * @name get
 * @class AntidiagonalSumMatrix
 * @brief This function returns the cross sum at position (r,c).
 * @memberof CrossSum
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @return CrossSumValue
 */
CrossSumValue AntidiagonalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
