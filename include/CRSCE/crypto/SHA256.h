/**
 * @file include/CRSCE/crypto/SHA256.h
 * @brief declare a class representing a SHA256 hash as a vector of uint8_t (byte) values.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <cstdint>
#include <vector>

class SHA256 {
public:
    inline static constexpr size_t DIGEST_SIZE = 32; // SHA-256 output size in bytes
    static std::vector<uint8_t> digest(const uint8_t* data, size_t length);
};
