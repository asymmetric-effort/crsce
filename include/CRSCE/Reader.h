// file: include/CRSCE/Reader.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_READER_H
#define CRSCE_READER_H

#include "CRSCE/CRSCE.h"

class Reader : public CRSCE {
  public:
    Reader(const std::string& inputFile, const std::string& outputFile);
    ~Reader();
    bool readFile(FileBuffer& buffer);
    void write(FileBuffer& buffer);
};

#endif //CRSCE_READER_H