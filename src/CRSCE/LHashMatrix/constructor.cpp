// file: src/CRSCE/LHashMatrix/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"

LHashMatrix::LHashMatrix(size_t block_size)
    : block_size(block_size),
      row_buffers(block_size, std::vector<bool>(block_size, false)),
      row_hashes(block_size, "")
{
    /* noop */
}
