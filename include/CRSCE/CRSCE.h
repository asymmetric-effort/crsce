// file: include/CRSCE/CRSCE.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_H
#define CRSCE_H

#include "CRSCE/FileBuffer.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include <string>
#include <fstream>
#include <cstdint>

class CRSCE {
public:
    CRSCE(const std::string& inputFile, const std::string& outputFile);
    ~CRSCE();

    int compress();
    int decompress();

protected:
    bool readInputBuffer(FileBuffer& buffer);

    std::ifstream inputStream;
    std::ofstream outputStream;

    static constexpr size_t BLOCK_SIZE = 512; //BLOCK_SIZE represents the CRSCE s-value.
    static constexpr size_t INPUT_BUFFER_SIZE = 1024 * 1024; // 1 MiB

    CrossSumIndex get_r(uint64_t bit_index) const;
    CrossSumIndex get_c(uint64_t bit_index) const;

    BitBuffer bit_serializer(FileBuffer inputBuffer);

};

#endif // CRSCE_H
