// file: include/CRSCE/CrossSum.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_H
#define CRSCE_CROSSSUM_H

#include <vector>
#include <cstdint>
#include "utils/transformations/xsm.h"

class CrossSum {
public:
    explicit CrossSum(const CrossSumValue size,const CrossSumValue width): s(size);
    ~CrossSum();

    virtual CrossSumValue get(CrossSumValue r, CrossSumValue c) const;
    virtual void set(CrossSumValue r, CrossSumValue c, CrossSumValue value);
    virtual void increment(CrossSumValue r, CrossSumValue c);

private:
    const CrossSumValue s;
    std::vector<CrossSumValue> data;
};

#endif // CRSCE_CROSSSUM_H
