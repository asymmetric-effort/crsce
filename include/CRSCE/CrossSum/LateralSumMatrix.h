// file: include/CRSCE/CrossSum/LateralSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LATERAL_SUM_MATRIX_H
#define CRSCE_LATERAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"

class LateralSumMatrix : public CrossSum {
public:
    explicit LateralSumMatrix(const CrossSumValue size);
    ~LateralSumMatrix() override;

    CrossSumValue get(CrossSumValue r, CrossSumValue c) const override;
    void set(CrossSumValue r, CrossSumValue c, CrossSumValue value) override;
    void increment(CrossSumValue r, CrossSumValue c) override;
};

#endif // CRSCE_LATERAL_SUM_MATRIX_H
