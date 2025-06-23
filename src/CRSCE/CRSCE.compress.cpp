/**
 * @file src/CRSCE/compress.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include <iostream>
#include <stdexcept>
#include <cstddef>

int CRSCE::compress() {
    try {
        std::cerr << "[CRSCE] Compression starting..." << std::endl;
        FileBuffer inputBuffer;

        // Write the file header (HEADER.length() bytes)
        outputStream.write(HEADER.c_str(), HEADER.length());

        uint64_t block_count = 0;

        // Load the entire input stream into inputBuffer (may contain multiple blocks)
        while (readInputBuffer(inputBuffer)) {
            // total_bits: actual number of bits read (one byte = 8 bits)
            const size_t total_bits = inputBuffer.size() * 8;
            std::cerr << "[CRSCE] Read " << inputBuffer.size()
                    << " words (" << total_bits << " bits) into inputBuffer." << std::endl;

            size_t buf_bit = 0; // current bit index in inputBuffer

            // Process as many s×s-bit blocks as fit in inputBuffer
            while (buf_bit < total_bits) {
                std::cerr << "[CRSCE] Starting block " << block_count << std::endl;

                // Initialize fresh matrices for this block
                LHashMatrix LHASH;
                LateralSumMatrix LSM;
                VerticalSumMatrix VSM;
                DiagonalSumMatrix XSM;
                AntidiagonalSumMatrix DSM;

                size_t block_bits = 0; // bits consumed in current block

                // Fill block with up to s*s bits from inputBuffer
                while (block_bits < s * s && buf_bit < total_bits) {
                    // Determine which word and bit to read
                    const size_t word_idx = buf_bit / FILE_BUFFER_WIDTH;
                    const int bit_pos = FILE_BUFFER_WIDTH - 1 - (buf_bit % FILE_BUFFER_WIDTH);
                    const bool bit_value = (inputBuffer[word_idx] >> bit_pos) & 0x01;

                    // Map flat bit index into row/col of the s×s matrix
                    const CrossSumIndex r = block_bits / s;
                    const CrossSumIndex c = block_bits % s;

                    // Update cross-sum matrices
                    increment_sums(bit_value, r, c, LSM, VSM, XSM, DSM, LHASH);

                    ++block_bits;
                    ++buf_bit;
                }

                LHASH.padRemainingBits(block_count, block_bits);

                // Serialize all five matrices for this block
                this->serialize_output(LSM,VSM,XSM,DSM,LHASH);

                std::cerr << "[CRSCE] Finished writing block " << block_count << std::endl;
                ++block_count;
            }
        }

        // Write the 128-bit file footer: block size and block count
        std::cerr << "[CRSCE] Writing footer. Total blocks: " << block_count << std::endl;
        constexpr uint64_t block_size_value = s;

        const auto size_bytes = reinterpret_cast<const std::byte*>(&block_size_value);
        const auto count_bytes = reinterpret_cast<const std::byte*>(&block_count);

        outputStream.write(reinterpret_cast<const char*>(size_bytes), sizeof(block_size_value));
        outputStream.write(reinterpret_cast<const char*>(count_bytes), sizeof(block_count));
        outputStream.flush();

        std::cerr << "[CRSCE] Compression finished successfully." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << "[CRSCE] Compression failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
