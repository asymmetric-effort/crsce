/**
 * @file include/CRSCE/CRSCE.h
 * @brief declare the CRSCE compression algorithm as a unit (with compress() and decompress() features).  This is
 *        the top-level class we should expose as a library.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_H
#define CRSCE_H

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
    explicit CRSCE(const std::string& inputFile, const std::string& outputFile, const size_t block_size,
                   const size_t concurrency);

    ~CRSCE();

    int compress();

    static int decompress();

    // cppcheck-suppress unusedStructMember
    static constexpr size_t INPUT_BUFFER_SIZE = 1048576; // 1 MiB = 1024^2

protected:
    bool readInputBuffer(FileBuffer& buffer);

private:
    std::ifstream inputStream;
    std::ofstream outputStream;
    size_t block_size;
    size_t concurrency;

    static void increment_sums(bool bit_value, CrossSumIndex r, CrossSumIndex c,
                               LateralSumMatrix& LSM, VerticalSumMatrix& VSM, DiagonalSumMatrix& XSM,
                               AntidiagonalSumMatrix& DSM, LHashMatrix& LHASH);

    void serialize_output(const LateralSumMatrix& LSM, const VerticalSumMatrix& VSM, const DiagonalSumMatrix& XSM,
                          const AntidiagonalSumMatrix& DSM, const LHashMatrix& LHASH);
};

#endif // CRSCE_H
