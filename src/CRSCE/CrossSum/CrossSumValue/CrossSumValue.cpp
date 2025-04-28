// file: src/CRSCE/CrossSum/CrossSumValue/CrossSumValue.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

CrossSumValue::CrossSumValue() : bits(0) {
  /* noop */
}

CrossSumValue::CrossSumValue(uint16_t value) : bits(value) {
  /* noop */
}

uint16_t CrossSumValue::to_uint16() const {
  return static_cast<uint16_t>(bits.to_ulong());
}

CrossSumValue CrossSumValue::operator+(uint16_t rhs) const {
  uint16_t lhs = this->to_uint16();
  if (lhs > max_value || rhs > max_value || lhs + rhs > max_value) {
    throw std::overflow_error("CrossSumValue overflow");
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
  ++(*this);
  return temp;
}
