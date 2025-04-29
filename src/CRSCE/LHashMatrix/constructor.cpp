// file: src/CRSCE/LHashMatrix/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"

LHashMatrix::LHashMatrix()
    : block_size(s),
      row_buffers(s, std::vector<bool>(s, false)),
      row_hashes(s, "")
{
    /* noop */
}
