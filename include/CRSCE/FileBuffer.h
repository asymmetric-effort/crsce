// file: include/CRSCE/FileBuffer.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_FILE_BUFFER_H
#define CRSCE_FILE_BUFFER_H

#include <vector>

constexpr size_t FILE_BUFFER_WIDTH = 64;

using FileBuffer = std::vector<uint64_t>;

#endif //CRSCE_FILE_BUFFER_H
