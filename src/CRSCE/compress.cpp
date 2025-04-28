// file: src/CRSCE/compress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include <iostream>
#include <stdexcept>

int CRSCE::compress() {
    try {
        std::cerr << "[CRSCE] Compression starting..." << std::endl;
        FileBuffer inputBuffer;

        LateralSumMatrix LSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        VerticalSumMatrix VSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        DiagonalSumMatrix XSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        AntidiagonalSumMatrix DSM(BLOCK_SIZE, CROSS_SUM_WIDTH);
        // ToDo: LHashMatrix LHASH(BLOCK_SIZE)

        uint64_t bit_index = 0;
        for(size_t sz=0;readInputBuffer(inputBuffer);sz+=inputBuffer.size()) {

            std::cout << "[CRSCE] Processing " << std::to_string(sz) << " bytes." << std::endl;

            for (const auto& word : inputBuffer) {
                for (int bit = FILE_BUFFER_WIDTH-1; bit >= 0; --bit) {
                    bool bit_value = (word >> bit) & 0x01;

                    std::cout << "bit index: " << bit_index << " value: " << std::to_string(bit_value) << std::endl;

                    uint32_t r = bit_index / BLOCK_SIZE;
                    uint32_t c = bit_index % BLOCK_SIZE;

                    if (bit_value) {
                        LSM.increment(r, c);
                        VSM.increment(r, c);
                        XSM.increment(r, c);
                        DSM.increment(r, c);
                        //This should push bits and generate hash when rows are complete.
                        //ToDo: LHASH.push(r,c,bit_value);
                    }

                    ++bit_index;
                }
            }
            LSM.serialize(outputStream);
            VSM.serialize(outputStream);
            XSM.serialize(outputStream);
            DSM.serialize(outputStream);
            //ToDo: LHASH.serialize(outputStream);
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[CRSCE] Compression failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
