// file: include/CRSCE/CrossSum/VerticalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_VERTICAL_SUM_MATRIX_H
#define CRSCE_VERTICAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"

class VerticalSumMatrix : public CrossSum {
public:
    explicit VerticalSumMatrix(const unsigned int size);
    ~VerticalSumMatrix() override;

    unsigned int get(unsigned int r, unsigned int c) const override;
    void set(unsigned int r, unsigned int c, unsigned int value) override;
    void increment(unsigned int r, unsigned int c) override;
};

#endif // CRSCE_VERTICAL_SUM_MATRIX_H

