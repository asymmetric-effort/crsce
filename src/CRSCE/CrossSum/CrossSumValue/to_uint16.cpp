/**
 * @file src/CRSCE/CrossSum/CrossSumValue/to_uint16.cpp
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>


/**
 * @name to_uint16
 * @class CrossSumValue
 * @brief return the uint16 value representation of the internal state.
 */
uint16_t CrossSumValue::to_uint16() const {
    return static_cast<uint16_t>(bits.to_ulong());
}
