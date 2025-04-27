// file: include/CRSCE/CrossSum/LateralSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LATERAL_SUM_MATRIX_H
#define CRSCE_LATERAL_SUM_MATRIX_H

#include "CRSCE/CrossSum/CrossSum.h"

class LateralSumMatrix : public CrossSum {
public:
    explicit LateralSumMatrix(const CrossSumValue size);
    ~LateralSumMatrix() override;

    CrossSumValue get(CrossSumValue r, CrossSumValue _) const override;
    void set(CrossSumValue r, CrossSumValue _, CrossSumValue value) override;
    void increment(CrossSumValue r, CrossSumValue _) override;
};

#endif // CRSCE_LATERAL_SUM_MATRIX_H
