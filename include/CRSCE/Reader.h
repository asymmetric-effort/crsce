/**
 * @file include/CRSCE/Reader.h
 * @brief Declare the CRSCE reader class which will read raw data into the CRSCE compressor.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_READER_H
#define CRSCE_READER_H

#include "CRSCE/CRSCE.h"

/**
 * @class Reader
 * @memberof CRSCE
 * @brief A reader class will read raw data into the CRSCE compressor
 */
class Reader : public CRSCE {
  public:
    /**
     * @name constructor
     * @class Reader
     * @memberof CRSCE
     * @param inputFile std::string filename
     * @param outputFile std::string filename
     * @brief initialize the class state
     */
    Reader(const std::string& inputFile, const std::string& outputFile);
    /**
     * @name destructor
     * @class Reader
     * @memberof CRSCE
     * @brief noop
     */
    ~Reader();
    /**
     * @name readFile
     * @class Reader
     * @memberof CRSCE
     * @param buffer FileBuffer
     * @return bool
     * @brief exposed readFile() function for testing.
     */
    bool readFile(FileBuffer& buffer);
    /**
     * @name write
     * @class Reader
     * @memberof CRSCE
     * @param buffer FileBuffer
     * @brief write the compressed content to the target file
     */
    void write(FileBuffer& buffer);
};

#endif //CRSCE_READER_H
