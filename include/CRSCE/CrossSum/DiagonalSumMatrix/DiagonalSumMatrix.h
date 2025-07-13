/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix.h
 * @brief declare the Diagonal (dsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

class DiagonalSumMatrix final : public CrossSum {
public:

    explicit DiagonalSumMatrix();

    ~DiagonalSumMatrix() override =default;

    [[nodiscard]] CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const override;

    void set(CrossSumIndex r, CrossSumIndex c, const CrossSumValue &value) override;

    void increment(CrossSumIndex r, CrossSumIndex c) override;

    [[nodiscard]] CrossSumIndex transform(CrossSumIndex r, CrossSumIndex c) const;
};
