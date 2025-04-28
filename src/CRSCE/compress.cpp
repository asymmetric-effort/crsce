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
        // ToDo: LHASH later

        uint64_t bit_index = 0;
        for(size_t sz=0;readInputBuffer(inputBuffer);sz+=inputBuffer.size()) {

            std::cout << "[CRSCE] Processing " << std::to_string(sz) << " bytes." << std::endl;

            for (const auto& byte : inputBuffer) {
                for (int bit = 7; bit >= 0; --bit) {
                    bool bit_value = (byte >> bit) & 0x01;

                    std::cout << "bit index: " << bit_index << " value: " << std::to_string(bit_value) << std::endl;

                    uint32_t r = bit_index / BLOCK_SIZE;
                    uint32_t c = bit_index % BLOCK_SIZE;

                    if (bit_value) {
                        LSM.increment(r, c);
                        VSM.increment(r, c);
                        XSM.increment(r, c);
                        DSM.increment(r, c);
                    }

                    ++bit_index;
                }
            }
            // This is here pending proper cross sum serialization
            // outputStream.write(reinterpret_cast<char*>(inputBuffer.data()), inputBuffer.size());
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[CRSCE] Compression failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
