/**
 * @file include/CRSCE/CrossSum/CrossSumIndex.h
 * @brief Declare the 16-bit CrossSumIndex type and its bounds_check() function.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "CRSCE/constants/constants.h"
#include <stdexcept>
#include <cstdint>

// we should never have a cross sum index greater than s==512.
using CrossSumIndex = uint16_t;

void bounds_check(CrossSumIndex index);
