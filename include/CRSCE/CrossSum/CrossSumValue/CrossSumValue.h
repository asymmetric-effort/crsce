// file: include/CRSCE/CrossSumValue.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_VALUE_H
#define CRSCE_CROSSSUM_VALUE_H

#include <bitset>
#include <cstdint>

class CrossSumValue {
public:
    CrossSumValue();
    explicit CrossSumValue(uint16_t value);

    uint16_t to_uint16() const;

    CrossSumValue operator+(uint16_t rhs) const;
    CrossSumValue operator+(CrossSumValue rhs) const;
    CrossSumValue& operator++();      // Prefix ++
    CrossSumValue operator++(int);     // Postfix ++

private:
    //b - cross sum element width
    static constexpr size_t b = 9;
    std::bitset<b> bits;
};

#endif // CRSCE_CROSSSUM_VALUE_H
