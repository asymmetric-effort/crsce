/**
 * @file include/CRSCE/CrossSumValueVerticalSumMatrix.h
 * @brief declare the Diagonal (dsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

class VerticalSumMatrix final : public CrossSum {
public:

    explicit VerticalSumMatrix();

    ~VerticalSumMatrix() override =default;

    [[nodiscard]] CrossSumValue get(CrossSumIndex _, CrossSumIndex c) const override;

    void set(CrossSumIndex _, CrossSumIndex c, const CrossSumValue &value) override;

    void increment(CrossSumIndex _, CrossSumIndex c) override;

};
