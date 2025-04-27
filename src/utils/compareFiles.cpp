// file: utils/compareFiles.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/compareFiles.h"

// compare two files at a byte level.
bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream ifs1(file1, std::ios::binary);
    std::ifstream ifs2(file2, std::ios::binary);

    if (!ifs1.is_open() || !ifs2.is_open()) {
        return false;
    }

    char buf1[4096];
    char buf2[4096];

    while (!ifs1.eof() && !ifs2.eof()) {
        ifs1.read(buf1, sizeof(buf1));
        ifs2.read(buf2, sizeof(buf2));

        std::streamsize bytesRead1 = ifs1.gcount();
        std::streamsize bytesRead2 = ifs2.gcount();

        if (bytesRead1 != bytesRead2 || std::memcmp(buf1, buf2, bytesRead1) != 0) {
            return false;
        }
    }

    return ifs1.eof() && ifs2.eof();
}
