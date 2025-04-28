// file: include/CRSCE/LHashMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LHASHMATRIX_H
#define CRSCE_LHASHMATRIX_H

#include "CRSCE/FileBuffer.h"
#include "CRSCE/crypto/SHA256.h"
#include <bitset>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

class LHashMatrix {
public:
    // class constructor.  Note default block_size represents CRSCE s-value BLOCK_SIZE (512).
    explicit LHashMatrix(size_t block_size);

    ~LHashMatrix();

    void push(uint32_t r, uint32_t c, bool bit_value);

    void serialize(std::ostream& os) const;

private:

    size_t block_size;

    std::vector<std::vector<bool>> row_buffers;   // Buffer for each row (before hash)

    std::vector<std::string> row_hashes;           // SHA256 hash result for each row

    void hash_and_store(uint32_t row_index);
};

#endif // CRSCE_LHASHMATRIX_H
