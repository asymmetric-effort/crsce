/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_increment.cpp
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

/**
 * @name operator++
 * @return CrossSumValue
 */
CrossSumValue& CrossSumValue::operator++() {
    *this = *this + 1;
    return *this;
}
/**
 * @name operator++
 * @return int
 */
CrossSumValue CrossSumValue::operator++(int) {
    const CrossSumValue temp = *this;
    *this = *this + 1;
    return temp;
}
