// file: include/CRSCE/constants/constants.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#ifndef CSRCE_CONSTANTS_H
#define CSRCE_CONSTANTS_H

#include <cstddef>

//Represents the CRSCE s-value.
//  512-1 = 511 is the maximum number of rows and columns allowed when b=9
//  This means our coordinates should always be 0...510 x 0...510.
//  our CSM uncompressed size is 511^2.
constexpr size_t s = 512-1; //511
constexpr size_t max_index = s-1; //510

//Represents the CRSCE b-value.  b=ciel(log2(s+1))
static constexpr size_t b = 9;

#endif //CSRCE_CONSTANTS_H
