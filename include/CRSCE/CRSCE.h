/**
 * @file include/CRSCE/CRSCE.h
 * @brief declare the CRSCE compression algorithm as a unit (with compress()
 *        and decompress() features).  This is the top-level class we should
 *        expose as a library.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "CRSCE/constants/constants.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/LHashMatrix.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"
#include <string>
#include <fstream>
#include <cstdint>

class CRSCE {
public:
    /**
     * @name constructor
     * @param inputFile - file stream (source file)
     * @param outputFile - file stream (destination file)
     * @param block_size - the size of a block in bits along the edge
     * @param concurrency - the number of concurrent blocks to process
     */
    explicit CRSCE(const std::string &inputFile,
                   const std::string &outputFile,
                   size_t block_size,
                   size_t concurrency);

    /**
     * @name destructor
     */
    ~CRSCE();

    /**
     * @name compress
     * @brief compress the input stream and write to the output stream
     * @return exit_code
     */
    int compress();

    /**
     * @name decompress
     * @brief decompress the input stream and write the output stream
     * @return exit_code
     */
    int decompress();

    // cppcheck-suppress unusedStructMember
    static constexpr size_t INPUT_BUFFER_SIZE = 1048576; // 1 MiB = 1024^2

protected:
    bool readInputBuffer(FileBuffer &buffer);

private:
    std::ifstream inputStream;
    std::ofstream outputStream;
    size_t block_size;
    size_t concurrency;

    static void increment_sums(bool bit_value,
                               CrossSumIndex r,
                               CrossSumIndex c,
                               LateralSumMatrix &LSM,
                               VerticalSumMatrix &VSM,
                               DiagonalSumMatrix &XSM,
                               AntidiagonalSumMatrix &DSM,
                               LHashMatrix &LHASH);

    void serialize_output(const LateralSumMatrix &LSM,
                          const VerticalSumMatrix &VSM,
                          const DiagonalSumMatrix &XSM,
                          const AntidiagonalSumMatrix &DSM,
                          const LHashMatrix &LHASH);

    void deserialize_input(const LateralSumMatrix &LSM,
                           const VerticalSumMatrix &VSM,
                           const DiagonalSumMatrix &XSM,
                           const AntidiagonalSumMatrix &DSM,
                           const LHashMatrix &LHASH);
};
