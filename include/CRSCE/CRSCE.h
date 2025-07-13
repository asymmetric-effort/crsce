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
    /**
     * @name readInputBuffer
     * @brief read the input file byte for byte
     * @param buffer
     * @return return true if bytes were read
     */
    bool readInputBuffer(FileBuffer &buffer);

private:
    // input file
    std::ifstream inputStream;
    // output file
    std::ofstream outputStream;
    // block size (s) representing a single edge length
    size_t block_size;
    // number of concurrent blocks to run.
    size_t concurrency;

    /**
     * @name increment_sums
     * @brief If CSM[r,c] is set, increment the corresponding cross sum values
     * @param bit_value - value of CSM[r,c]
     * @param r row index
     * @param c column index
     * @param LSM - lateral sums matrix
     * @param VSM - vertical sums matrix
     * @param XSM - antidiagonal sums matrix
     * @param DSM - diagonal sums matrix
     * @param LHASH - lateral hash matrix
     */
    static void increment_sums(bool bit_value,
                               CrossSumIndex r,
                               CrossSumIndex c,
                               LateralSumMatrix &LSM,
                               VerticalSumMatrix &VSM,
                               DiagonalSumMatrix &XSM,
                               AntidiagonalSumMatrix &DSM,
                               LHashMatrix &LHASH);

    /**
     * @name serialize_output
     * @brief Serialize the cross sum streams into the output stream.
     *        Each iteration serializes a single block.
     * @param LSM - lateral sums matrix
     * @param VSM - vertical sums matrix
     * @param XSM - antidiagonal sums matrix
     * @param DSM - diagonal sums matrix
     * @param LHASH - lateral hash matrix
     */
    void serialize_output(const LateralSumMatrix &LSM,
                          const VerticalSumMatrix &VSM,
                          const DiagonalSumMatrix &XSM,
                          const AntidiagonalSumMatrix &DSM,
                          const LHashMatrix &LHASH);

    /**
     * @name deserialize_input
     * @brief Deserialize the input stream into the cross sums for a single block.
     *        Each iteration deserializes a single block.
     * @param LSM - lateral sums matrix
     * @param VSM - vertical sums matrix
     * @param XSM - antidiagonal sums matrix
     * @param DSM - diagonal sums matrix
     * @param LHASH - lateral hash matrix
     */
    void deserialize_input(const LateralSumMatrix &LSM,
                           const VerticalSumMatrix &VSM,
                           const DiagonalSumMatrix &XSM,
                           const AntidiagonalSumMatrix &DSM,
                           const LHashMatrix &LHASH);
};
