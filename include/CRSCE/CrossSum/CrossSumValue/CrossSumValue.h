// file: include/CRSCE/CrossSumValue.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_VALUE_H
#define CRSCE_CROSSSUM_VALUE_H

#include "CRSCE/constants/constants.h"
#include <bitset>
#include <cstdint>
#include <stdexcept>

class CrossSumValue {
public:
    CrossSumValue();
    explicit CrossSumValue(uint16_t value);

    uint16_t to_uint16() const;

    CrossSumValue operator+(uint16_t rhs) const;
    CrossSumValue operator+(CrossSumValue rhs) const;
    CrossSumValue& operator++();
    CrossSumValue operator++(int);

private:
    std::bitset<b> bits;
};

#endif // CRSCE_CROSSSUM_VALUE_H
