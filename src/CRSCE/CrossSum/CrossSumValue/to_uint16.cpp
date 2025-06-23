/**
 * @file src/CRSCE/CrossSum/CrossSumValue/to_uint16.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

// return 16-bit unsigned integer representation of value state
uint16_t CrossSumValue::to_uint16() const {
    return static_cast<uint16_t>(bits.to_ulong());
}
