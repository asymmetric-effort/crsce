/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_plus_CrossSumValue.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

CrossSumValue CrossSumValue::operator+(const CrossSumValue &rhs) const {
    return *this + rhs.to_uint16();
}
