// file: include/CRSCE/CrossSum.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_H
#define CRSCE_CROSSSUM_H

#include <vector>
#include <cstdint>
#include "utils/transformations/xsm.h"

class CrossSum {
public:
    explicit CrossSum(const unsigned int size): s(size);
    ~CrossSum();

    virtual unsigned int get(unsigned int r, unsigned int c) const;
    virtual void set(unsigned int r, unsigned int c, unsigned int value);
    virtual void increment(unsigned int r, unsigned int c);

private:
    const unsigned int s;
    std::vector<unsigned int> data;
};

#endif // CRSCE_CROSSSUM_H


// file: src/CRSCE/CrossSum.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum.h"

CrossSum::CrossSum(unsigned int size) : s(size), data(size, 0) {}

unsigned int CrossSum::get(unsigned int r, unsigned int c) const {
    return data[xsm(r, c, s)];
}

void CrossSum::set(unsigned int r, unsigned int c, unsigned int value) {
    data[xsm(r, c, s)] = value;
}

void CrossSum::increment(unsigned int r, unsigned int c) {
    ++data[xsm(r, c, s)];
}
