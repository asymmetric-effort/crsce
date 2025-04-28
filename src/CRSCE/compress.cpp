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

        LateralSumMatrix LSM(BLOCK_SIZE);
        VerticalSumMatrix VSM(BLOCK_SIZE);
        DiagonalSumMatrix XSM(BLOCK_SIZE);
        AntidiagonalSumMatrix DSM(BLOCK_SIZE);
        // ToDo: LHASH later

        uint64_t bit_index = 0;
        for(size_t sz=0;readInputBuffer(inputBuffer);sz+=inputBuffer.size()) {
            while(const auto& bit_value = bit_serializer(inputBuffer)){
                std::cout << "bit index: " << bit_index << " value: " << std::to_string(bit_value) << std::endl;

                CrossSumIndex r = get_r(bit_index); // bit_index / BLOCK_SIZE;
                CrossSumIndex c = get_c(bit_index); // bit_index % BLOCK_SIZE;

                if (bit_value) {
                    LSM.increment(r, c);
                    VSM.increment(r, c);
                    XSM.increment(r, c);
                    DSM.increment(r, c);
                }

                ++i;
            }

            std::cout << "[CRSCE] Processing " << std::to_string(sz) << " bytes." << std::endl;

            // TODO: process inputBuffer block-by-block for actual compression logic
            // For now, write inputBuffer directly (bit-for-bit serialization)

            outputStream.write(reinterpret_cast<char*>(inputBuffer.data()), inputBuffer.size());
        }

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[CRSCE] Compression failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
