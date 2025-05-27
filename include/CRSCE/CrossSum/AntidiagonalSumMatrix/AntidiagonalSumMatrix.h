/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix.h
 * @brief declare the Anti-diagonal (xsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
#define CRSCE_ANTIDIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum/CrossSum.h"

/**
 * @class AntidiagonalSumMatrix
 * @memberof CrossSum
 * @brief The CRSCE Antidiagonal Cross Sum Matrix (XSM) class.  This is a 1D matrix of 1xs elements.
 */
class AntidiagonalSumMatrix final : public CrossSum {
public:
    /**
     * @name constructor
     * @class AntidiagonalSumMatrix
     * @memberof CrossSum
     * @brief noop
     */
    explicit AntidiagonalSumMatrix();
    /**
     * @name destructor
     * @class AntidiagonalSumMatrix
     * @memberof CrossSum
     * @brief noop
     */
    ~AntidiagonalSumMatrix() override;
    /**
     * @name get
     * @class AntidiagonalSumMatrix
     * @brief This function returns the cross sum at position (r,c).
     * @memberof CrossSum
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @return CrossSumValue
     */
    CrossSumValue get(const CrossSumIndex r, const CrossSumIndex c) const override;
    /**
     * @name set
     * @class AntidiagonalSumMatrix
     * @brief This function sets the CrossSumValue at position (r,c).
     * @memberof CrossSum
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param v CrossSumValue
     */
    void set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) override;
    /**
     * @name increment
     * @class AntidiagonalSumMatrix
     * @brief This function increments the element at (r,c)
     * @memberof CrossSum
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     */
    void increment(const CrossSumIndex r, const CrossSumIndex c) override;
    /**
     * @name set
     * @class AntidiagonalSumMatrix
     * @brief Translate 2D coordinates(r,c) into 1D linear address (x)
     * @memberof CrossSum
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param v CrossSumValue
     */
    CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c);
};

#endif // CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
