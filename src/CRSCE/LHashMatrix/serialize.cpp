/**
 * @file src/CRSCE/LHashMatrix/serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"

void LHashMatrix::serialize(std::ostream &os) const {
    for (CrossSumIndex r = 0; r < s; ++r) {
        // Finalize hash if row is full and hash has not been computed
        if (row_positions[r] == s && row_hashes[r].empty()) {
            const_cast<LHashMatrix*>(this)->hash_and_store(r);
        }

        const auto& hash = row_hashes[r];
        if (hash.size() != SHA256::DIGEST_SIZE) {
            throw std::runtime_error(
                "LHashMatrix::serialize() - Invalid hash length: " + std::to_string(hash.size())
            );
        }
        //write the hash (of a given size)...only the hash is written.
        os.write(hash.data(), hash.size());
    }
}
