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

/**
 * @class CRSCE
 * @brief Cross Sum Compression and Expansion top-level class which wraps compress and decompress functionality.
 */
class CRSCE {
public:
    /**
     * @name constructor
     * @brief Class Constructor opens the input and output files, then initializes the compression/decompression
     *        common assets
     * @param inputFile std::string
     * @param outputFile std::string
     */
    explicit CRSCE(const std::string &inputFile, const std::string &outputFile);
    /**
     * @name destructor
     * @class CRSCE
     * @brief close any open files.
     * @param inputFile std::string
     * @param outputFile std::string
     */
    ~CRSCE();
    /**
     * @name compress
     * @brief compress a given input
     */
    int compress();
    /**
     * @name decompress
     * @brief decompress a given input
     */
    int decompress();

    /**
     * @property INPUT_BUFFER_SIZE
     * @brief 1MB Input Buffer
     */
    static constexpr size_t INPUT_BUFFER_SIZE = 1024 * 1024; // 1 MiB

protected:
    /**
     * @name readInputBuffer
     * @protected
     * @brief read the input file byte for byte
     * @param buffer FileBuffer
     * @return bool
     */
    bool readInputBuffer(FileBuffer &buffer);

    /**
     * @name inputStream
     * @protected
     * @brief input data source
     */
    std::ifstream inputStream;
    /**
     * @name outputStream
     * @protected
     * @brief output data source
     */
    std::ofstream outputStream;
};

#endif // CRSCE_H
