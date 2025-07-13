// file: src/Common/BitReader/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Common/BitReader.h"

BitReader::BitReader(std::istream& in)
    : stream(in), buffer(0), bitsRemaining(0) {}
