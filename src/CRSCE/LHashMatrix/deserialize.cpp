/**
* @file src/CRSCE/LHashMatrix/deserialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/crypto/SHA256.h"
#include "utils/Exceptions/InvalidHashLength.h"

/**
 * @name deserialize
 * @class LHashMatrix
 * @brief This method deserializes the LHASH content from the input stream
 * @param is std::istream
 * @throws Exceptions::InvalidHashLength()
 */
void LHashMatrix::deserialize(std::istream& is) const {
    for (CrossSumIndex r = 0; r < s; ++r) {
        std::string hash(SHA256::DIGEST_SIZE, '\0');
        is.read(&hash[0], SHA256::DIGEST_SIZE);
        if (!is) {
            throw Exceptions::InvalidHashLength(0);
        }
        row_hash_data[r]=hash;
    }
}
