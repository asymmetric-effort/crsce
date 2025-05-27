/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix.h
 * @brief declare the Diagonal (dsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_DIAGONAL_SUM_MATRIX_H
#define CRSCE_DIAGONAL_SUM_MATRIX_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

/**
 * @class DiagonalSumMatrix
 * @memberof CrossSum
 * @brief Defines a diagonal sums matrix of s-elements, each containing b-bits.
 */
class DiagonalSumMatrix final : public CrossSum {
public:
    /**
     * @name constructor
     * @brief noop
     */
    explicit DiagonalSumMatrix();

    /**
     * @name destructor
     * @brief noop
     */
    ~DiagonalSumMatrix() override;

    /**
     * @name get
     * @brief get the value at position (r,c)
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @return CrossSumValue
     */
    [[nodiscard]] CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const override;
    /**
     * @name set
     * @brief set the value at position (r,c)
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param value CrossSumValue
     */
    void set(CrossSumIndex r, CrossSumIndex c, CrossSumValue value) override;
    /**
     * @name increment
     * @brief increment the value at position (r,c)
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     */
    void increment(CrossSumIndex r, CrossSumIndex c) override;
    /**
     * @name transform
     * @brief transform the 2D (r,c) coordinates to 1D 0,...,s-1
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     */
    static CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c);
};

#endif // CRSCE_DIAGONAL_SUM_MATRIX_H
