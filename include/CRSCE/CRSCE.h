// file: include/CRSCE.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#ifndef CRSCE_H
#define CRSCE_H

#include <string>
#include <fstream>

class CRSCE {
public:
    CRSCE(const std::string& inputFile, const std::string& outputFile);
    ~CRSCE();

    int compress();
    int decompress();

private:
    std::ifstream inputStream;
    std::ofstream outputStream;
};

#endif // CRSCE_H
