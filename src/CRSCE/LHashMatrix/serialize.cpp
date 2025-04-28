// file: src/CRSCE/LHashMatrix/serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LHashMatrix.h"

void LHashMatrix::serialize(std::ostream& os) const {
    for (const auto& hash : row_hashes) {
        // Each row_hash should already be a 32-byte binary string
        os.write(hash.data(), hash.size());
    }
}
