/**
 * @file src/CRSCE/CrossSum/CrossSumValue/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

// Default constructor
CrossSumValue::CrossSumValue() : bits(0) {}

// Constructor with safety check.
CrossSumValue::CrossSumValue(const uint16_t value) {
    if (value >= (1u << b)) {
        throw std::out_of_range("CrossSumValue exceeds allowed bit width");
    }
    bits = std::bitset<b>(value);
}
