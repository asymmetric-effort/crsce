/**
 * @file include/CRSCE/CrossSumValueVerticalSumMatrix.h
 * @brief declare the Vertical (VSM) Matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_VERTICAL_SUM_MATRIX_H
#define CRSCE_VERTICAL_SUM_MATRIX_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

/**
 * @class VeriticalSumMatrix
 * @memberof CrossSum
 * @brief Describes the sum of set-bit values in each column
 */
class VerticalSumMatrix final : public CrossSum {
public:
    /**
     * @name constructor
     * @brief noop
     */
    explicit VerticalSumMatrix();
    /**
     * @name destructor
     * @brief noop
     */
    ~VerticalSumMatrix() override;
    /**
     * @name get
     * @brief return the value at position c
     * @param _ CrossSumIndex
     * @param c CrossSumIndex
     * @return CrossSumValue
     */
    CrossSumValue get(CrossSumIndex _, CrossSumIndex c) const override;
    /**
     * @name set
     * @brief set the value at position c
     * @param _ CrossSumIndex
     * @param c CrossSumIndex
     * @param value CrossSumValue
     */
    void set(CrossSumIndex _, CrossSumIndex c, CrossSumValue value) override;

    /**
     * @name increment
     * @brief increment the VSM[c] value
     * @param _
     * @param c
     */
    void increment(CrossSumIndex _, CrossSumIndex c) override;
};

#endif // CRSCE_VERTICAL_SUM_MATRIX_H
