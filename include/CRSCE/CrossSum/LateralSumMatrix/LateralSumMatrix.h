/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix.h
 * @brief declare the Lateral (lsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

class LateralSumMatrix final : public CrossSum {
public:

    explicit LateralSumMatrix();

    ~LateralSumMatrix() override =default;

    [[nodiscard]] CrossSumValue get(CrossSumIndex r, CrossSumIndex _) const override;

    void set(CrossSumIndex r, CrossSumIndex _, const CrossSumValue &value) override;

    void increment(CrossSumIndex r, CrossSumIndex _) override;

};
