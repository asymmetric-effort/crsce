// file: src/CRSCE/compress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include <iostream>
#include <stdexcept>

int CRSCE::compress() {
    try {
        std::cerr << "[CRSCE] Compression starting..." << std::endl;
        FileBuffer inputBuffer;

        LHashMatrix LHASH(BLOCK_SIZE);
        LateralSumMatrix LSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        VerticalSumMatrix VSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        DiagonalSumMatrix XSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        AntidiagonalSumMatrix DSM(BLOCK_SIZE, CROSS_SUM_WIDTH);

        uint32_t bit_index = 0;
        uint64_t block_count = 0;
        //Write the file header (HEADER_LENGTH bytes)
        outputStream.write(HEADER, HEADER_LENGTH);

        for(size_t sz=0;readInputBuffer(inputBuffer);sz+=inputBuffer.size()) {

            std::cout << "[CRSCE] Processing " << std::to_string(sz) << " bytes." << std::endl;

            for (const auto& word : inputBuffer) {
                for (int bit = FILE_BUFFER_WIDTH-1; bit >= 0; --bit) {
                    bool bit_value = (word >> bit) & 0x01;

                    std::cout << "bit index: " << bit_index << " value: " << std::to_string(bit_value) << std::endl;

                    CrossSumIndex r = bit_index / BLOCK_SIZE;
                    CrossSumIndex c = bit_index % BLOCK_SIZE;

                    if (bit_value) {
                        LHASH.push(r, c, bit_value);
                        LSM.increment(r, c);
                        VSM.increment(r, c);
                        XSM.increment(r, c);
                        DSM.increment(r, c);
                    }

                    ++bit_index;
                }
            }
            LHASH.serialize(outputStream);
            LSM.serialize(outputStream);
            VSM.serialize(outputStream);
            XSM.serialize(outputStream);
            DSM.serialize(outputStream);
            outputStream.flush();
            block_count++;
        }
        {
            //Write the 128-bit file footer, consisting of BLOCK_SIZE (e.g. s=512) and block_count
            uint64_t block_size_value = BLOCK_SIZE;
            uint64_t block_count_value = block_count;
            outputStream.write(reinterpret_cast<const char*>(&block_size_value), sizeof(block_size_value));
            outputStream.write(reinterpret_cast<const char*>(&block_count_value), sizeof(block_count_value));
            outputStream.flush();
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[CRSCE] Compression failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
