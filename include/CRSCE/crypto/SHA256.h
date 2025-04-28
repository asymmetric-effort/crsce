// file: include/CRSCE/crypto/SHA256.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CRYPTO_SHA256_H
#define CRSCE_CRYPTO_SHA256_H

#include <cstdint>
#include <vector>

class SHA256 {
public:
    static std::vector<uint8_t> digest(const uint8_t* data, size_t length);
};

#endif // CRSCE_CRYPTO_SHA256_H
