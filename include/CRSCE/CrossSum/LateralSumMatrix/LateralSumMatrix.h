/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix.h
 * @brief declare the Lateral (lsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_LATERAL_SUM_MATRIX_H
#define CRSCE_LATERAL_SUM_MATRIX_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

/**
 * @class LateralSumMatrix
 * @memberof CrossSum
 * @brief A lateral sums matrix which sums the set-bit count along rows.
 */
class LateralSumMatrix final : public CrossSum {
public:
    /**
     * @name constructor
     * @brief noop
     */
    explicit LateralSumMatrix();

    /**
     * @name destructor
     * @brief noop
     */
    ~LateralSumMatrix() override;

    /**
     * @name get
     * @memberof LateralSumMatrix
     * @brief return the value of row r
     * @param r CrossSumIndex
     * @return CrossSumValue
     */
    CrossSumValue get(CrossSumIndex r, CrossSumIndex _) const override;

    /**
     * @name set
     * @memberof LateralSumMatrix
     * @brief increment the value for row r
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param value CrossSumValue
     */
    void set(CrossSumIndex r, CrossSumIndex _, CrossSumValue value) override;

    /**
     * @name increment
     * @memberof LateralSumMatrix
     * @brief increment the value for row r
     * @param r CrossSumIndex
     */
    void increment(CrossSumIndex r, CrossSumIndex _) override;

};

#endif // CRSCE_LATERAL_SUM_MATRIX_H
