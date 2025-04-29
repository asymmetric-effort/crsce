// file: include/CRSCE/CrossSum/CrossSumIndex.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSS_SUM_INDEX_H
#define CRSCE_CROSS_SUM_INDEX_H

#include <cstdint>
#include <stdexcept>

// we should never have a cross sum index greater than s==512.
using CrossSumIndex = uint16_t;

void bounds_check(const CrossSumIndex index, const CrossSumIndex max_value);

#endif // CRSCE_CROSS_SUM_INDEX_H
