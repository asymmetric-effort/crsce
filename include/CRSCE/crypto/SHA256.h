/**
 * @file include/CRSCE/crypto/SHA256.h
 * @brief declare a class representing a SHA256 hash as a vector of uint8_t (byte) values.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_CRYPTO_SHA256_H
#define CRSCE_CRYPTO_SHA256_H

#include <cstdint>
#include <vector>

/**
 * @class SHA256
 * @brief a wrapper implementing SHA256 hashes.
 * @todo: Reimplement as a GPU-based SHA256 hash.
 * @todo: implement the entire hashing process using vector<uint8_t>
 */
class SHA256 {
public:
    /**
     * @property DIGEST_SIZE
     * @brief the size in bytes of the hash output
     */
    inline static constexpr size_t DIGEST_SIZE = 32; // SHA-256 output size in bytes
    /**
     * @name digest
     * @brief computes the hash of a given input.
     * @param data uint8_t*
     * @param length size_t
     * @return std::vector<uint8_t>
     */
    static std::vector<uint8_t> digest(const uint8_t* data, size_t length);
};

#endif // CRSCE_CRYPTO_SHA256_H
