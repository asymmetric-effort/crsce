// file: src/CRSCE/compress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>


int CRSCE::compress() {
    try {
        std::cerr << "[CRSCE] Compression starting..." << std::endl;
        std::vector<uint8_t> inputBuffer;

        for(size_t sz=0;readInputBuffer(inputBuffer);sz+=inputBuffer.size()) {

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
