// file: include/CRSCE/CrossSumValue.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_VALUE_H
#define CRSCE_CROSSSUM_VALUE_H

#include <bitset>

// Bit field where w = ceil(log2(512)) = 9.
using CrossSumValue = std::bitset<9>;

#endif // CRSCE_CROSSSUM_VALUE_H
