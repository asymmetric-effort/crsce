/**
 * @file include/CRSCE/Reader.h
 * @brief Declare the CRSCE reader class which will read raw data to support our tests.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "CRSCE/FileBuffer.h"
#include <fstream>
#include <string>

/**
 * @class Reader
 * @brief Simple file I/O helper for unit-test verification.
 *
 * This class provides readFile() and write() methods that
 * load an entire input file into memory and write it back out.
 *
 * @note This helper is only used by the test
 *       suite (e.g. 3000_file-readInputBuffer-verification)
 *       to verify basic file I/O; it is not part of the
 *       core CRSCE compress/decompress workflow.
 */
class Reader {
public:
    static constexpr size_t INPUT_BUFFER_SIZE = 1024 * 1024; // 1 MiB

    Reader(const std::string &inputFile,
                    const std::string &outputFile);
    ~Reader();

    /// Load the entire contents of inputFile into `buffer`.
    /// @returns true on success, false on I/O error.
    bool readFile(FileBuffer& buffer);

    /// Write the full `buffer` back out to outputFile.
    void write(const FileBuffer& buffer);

protected:
    bool readInputBuffer(FileBuffer& buffer);

private:
    std::ifstream inputStream;
    std::ofstream outputStream;
};
