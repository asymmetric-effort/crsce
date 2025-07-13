/**
 * @file include/CRSCE/CrossSumValue.h
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "CRSCE/constants/constants.h"
#include <bitset>
#include <cstdint>
#include <stdexcept>

class CrossSumValue {
public:
    CrossSumValue();
    explicit CrossSumValue(uint16_t value);

    [[nodiscard]] uint16_t to_uint16() const;

    friend CrossSumValue operator+(const CrossSumValue &lhs, uint16_t rhs);
    friend CrossSumValue operator+(const CrossSumValue &lhs, const CrossSumValue &rhs);
    CrossSumValue& operator++();
    CrossSumValue operator++(int);

private:
    // cppcheck-suppress unusedStructMember
    std::bitset<b> bits{};
};
