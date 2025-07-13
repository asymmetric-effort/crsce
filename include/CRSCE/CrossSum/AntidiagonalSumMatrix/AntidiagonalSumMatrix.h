/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix.h
 * @brief declare the Anti-diagonal (xsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "CRSCE/CrossSum/CrossSum.h"

/**
 * @name AntidiagonalSumMatrix
 * @brief The XSM CrossSum matrix class representing right-to-left, top-to-bottom.
 *        This is a one-dimensional matrix, and any (r,c) address references must be
 *        first translated to this one-dimensional space.
 */
class AntidiagonalSumMatrix final : public CrossSum {
public:
    /**
     * @name constructor
     * @brief initialize the matrix
     */
    explicit AntidiagonalSumMatrix();

    /**
     * @name default destructor
     * @brief default destructor..does nothing more than the base class
     */
    ~AntidiagonalSumMatrix() override =default;

    /**
     * @name get
     * @brief return a CrossSumValue at the transformed position (r,c).
     * @param r row index
     * @param c column index
     * @return CrossSumValue representing the sum at (r,c).
     */
    [[nodiscard]] CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const override;

    /**
     * @name set
     * @brief set the CrossSumValue at the transformed position (r,c).
     * @param r row index
     * @param c column index
     * @param value CrossSumValue
     */
    void set(CrossSumIndex r, CrossSumIndex c, const CrossSumValue &value) override;

    /**
     * @name increment
     * @brief increment the CrossSumValue at the transformed position (r,c).
     * @param r row index
     * @param c column index
     * @param value CrossSumValue
     */
    void increment(CrossSumIndex r, CrossSumIndex c) override;

    /**
     * @name transform
     * @brief transform a two-dimensional (r,c) address to a one-dimensional address.
     * @param r row index
     * @param c column index
     * @param value CrossSumValue
     */
    [[nodiscard]] static auto transform(CrossSumIndex r, CrossSumIndex c) -> CrossSumIndex;
};
