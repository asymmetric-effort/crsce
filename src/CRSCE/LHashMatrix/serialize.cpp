/**
 * @file src/CRSCE/LHashMatrix/serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include "utils/Exceptions/InvalidHashLength.h"
#include "CRSCE/crypto/SHA256.h"

/**
 * @name serialize
 * @class LHashMatrix
 * @brief This method serializes the LHASH content and writes it to an ostream
 * @param os std::ostream
 * @throws Exceptions::InvalidHashLength()
 */
void LHashMatrix::serialize(std::ostream &os) const {
    for (CrossSumIndex r = 0; r < s; ++r) {
        // Finalize hash if row is full and hash has not been computed
        if (row_positions()[r] == s && row_hashes()[r].empty()) {
            hash_and_store(r);  // no const_cast needed anymore
        }

        const auto &hash = row_hashes()[r];
        if (hash.size() != SHA256::DIGEST_SIZE) {
            throw Exceptions::InvalidHashLength(hash.size());
        }
        //write the hash (of a given size)...only the hash is written.
        os.write(hash.data(), static_cast<long>(hash.size()));
    }
}
