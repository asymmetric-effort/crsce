/**
 * @file include/CRSCE/CrossSumValue.h
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "CRSCE/constants/constants.h"
#include <bitset>
#include <cstdint>

/**
 * @name CrossSumValue
 * @brief A number representing a cross sum value of range (0,...,s)
 */
class CrossSumValue {
public:
    /**
     * @name default constructor
     * @brief default constructor
     */
    CrossSumValue() = default;

    /**
     * @name constructor with value
     * @brief A number representing a current cross sum value state
     * @param value uint16_t (0,...,s)
     */
    explicit CrossSumValue(uint16_t value);

    /**
     * @name to_uint16
     * @brief output the cross sum value as a 16-bit unsigned integer
     * @return uint16_t
     */
    [[nodiscard]] uint16_t to_uint16() const;

    /**
     * @name operator +
     * @brief add lhs to rhs and return the sum
     * @param lhs CrossSumValue
     * @param rhs uint16_t
     * @return CrossSumValue
     */
    friend CrossSumValue operator+(const CrossSumValue &lhs, uint16_t rhs);

    /**
     * @name operator +
     * @brief add lhs to rhs and return the sum
     * @param lhs CrossSumValue
     * @param rhs CrossSumValue
     * @return CrossSumValue
     */
    friend CrossSumValue operator+(const CrossSumValue &lhs, const CrossSumValue &rhs);

    /**
     * @name increment operator
     * @brief increment the cross sum value
     * @return CrossSumValue
     */
    CrossSumValue &operator++();

    /**
     * @name increment operator
     * @brief increment the cross sum value
     * @return CrossSumValue
     */
    CrossSumValue operator++(int);

private:
    /**
     * @name bits
     * @brief binary data representing a CrossSumValue of b-bit width.
     */
    // cppcheck-suppress unusedStructMember
    std::bitset<b> bits{};
};
