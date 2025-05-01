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

        // Write the file header (HEADER_LENGTH bytes)
        outputStream.write(HEADER, HEADER_LENGTH);

        uint64_t block_count = 0;
        for (size_t sz = 0; readInputBuffer(inputBuffer); sz += inputBuffer.size()) {

            std::cout << "[CRSCE] Processing " << std::to_string(sz) << " bytes." << std::endl;

            LHashMatrix LHASH;
            LateralSumMatrix LSM;
            VerticalSumMatrix VSM;
            DiagonalSumMatrix XSM;
            AntidiagonalSumMatrix DSM;

            uint32_t bit_index = 0;
            constexpr uint32_t block_limit = s * s; // limit on bit_index to avoid overflow.
            for (const auto& word : inputBuffer) {
                for (int bit = FILE_BUFFER_WIDTH - 1; bit >= 0; --bit) {

                    if (bit_index >= block_limit) break;

                    bool bit_value = (word >> bit) & 0x01;
                    CrossSumIndex r = bit_index / s;
                    CrossSumIndex c = bit_index % s;
                    std::cout << "bit index: " << bit_index << " ("
                              << std::to_string(r) << ","
                              << std::to_string(c) << ") "
                              << "value: " << std::to_string(bit_value)
                              << std::endl;

                    try{
                        if (bit_value) {
                            LSM.increment(r, c);
                            VSM.increment(r, c);
                            XSM.increment(r, c);
                            DSM.increment(r, c);
                        }
                        LHASH.push(r, c, bit_value);
                    }catch(std::exception& e){
                        std::cerr << "cross sum ::increment(r, c) error: " << e.what() << std::endl;
                        return EXIT_FAILURE;
                    }
                    ++bit_index;
                }
            }
            if (bit_index % s != 0) {
                std::cout << "[CRSCE] adding padding bits..." << std::endl;
                // Pad all remaining rows/cells in the block if EOF ends mid-block
                const CrossSumIndex start_r = bit_index / s;
                for (CrossSumIndex r = start_r; r < s; ++r) {
                    const CrossSumIndex start_c = (r == start_r ? bit_index % s : 0);
                    for (CrossSumIndex c = start_c; c < s; ++c) {
                        LHASH.push(r, c, false);
                    }
                }
                std::cout << "[CRSCE] ...padding complete." << std::endl;
            }
            LHASH.serialize(outputStream);
            LSM.serialize(outputStream);
            VSM.serialize(outputStream);
            XSM.serialize(outputStream);
            DSM.serialize(outputStream);
            outputStream.flush();
            block_count++;
        }

        // Write the 128-bit file footer
        {
            uint64_t block_size_value = s;
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
