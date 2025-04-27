// file: include/CRSCE/CRSCE.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_H
#define CRSCE_H

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

class CRSCE {
public:
    CRSCE(const std::string& inputFile, const std::string& outputFile);
    ~CRSCE();

    int compress();
    int decompress();

private:
    std::ifstream inputStream;
    std::ofstream outputStream;

    static constexpr size_t BLOCK_SIZE = 512;
    static constexpr size_t INPUT_BUFFER_SIZE = 1024 * 1024; // 1 MiB

    bool readInputBuffer(std::vector<uint8_t>& buffer);
};

#endif // CRSCE_H
