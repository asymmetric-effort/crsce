// file: src/CRSCE/CrossSum/CrossSumValue/operator_plusplus.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSumValue.h"

uint16_t CrossSumValue::to_uint16() const {
    return static_cast<uint16_t>(bits.to_ulong());
}
