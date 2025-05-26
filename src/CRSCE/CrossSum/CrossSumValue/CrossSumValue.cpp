/**
 * @file src/CRSCE/CrossSum/CrossSumValue/CrossSumValue.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

// Default constructor
CrossSumValue::CrossSumValue() : bits(0) {}

// Constructor with safety check.
CrossSumValue::CrossSumValue(uint16_t value) {
  if (value >= (1u << b)) {
    throw std::out_of_range("CrossSumValue exceeds allowed bit width");
  }
  bits = std::bitset<b>(value);
}

// return 16-bit unsigned integer representation of value state
uint16_t CrossSumValue::to_uint16() const {
  return static_cast<uint16_t>(bits.to_ulong());
}

CrossSumValue CrossSumValue::operator+(uint16_t rhs) const {
  uint16_t lhs = this->to_uint16();
  if (lhs > s || rhs > s || lhs + rhs > s) {
    throw std::overflow_error("Value out of bounds");
  }
  return CrossSumValue(lhs + rhs);
}

CrossSumValue CrossSumValue::operator+(CrossSumValue rhs) const {
  return *this + rhs.to_uint16();
}

CrossSumValue& CrossSumValue::operator++() {
  *this = *this + 1;
  return *this;
}

CrossSumValue CrossSumValue::operator++(int) {
  CrossSumValue temp = *this;
  *this = *this + 1;
  return temp;
}
