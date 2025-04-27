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

    uint16_t to_uint() const;

    CrossSumValue operator+(uint16_t rhs) const;
    CrossSumValue& operator++();      // Prefix ++
    CrossSumValue operator++(int);     // Postfix ++

private:
    static constexpr size_t WIDTH = 9;
    std::bitset<WIDTH> bits;
};

#endif // CRSCE_CROSSSUM_VALUE_H
