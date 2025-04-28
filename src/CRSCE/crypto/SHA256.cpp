// file: src/CRSCE/crypto/SHA256.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/crypto/SHA256.h"
#include <vector>
#include <cstdint>

#if defined(__APPLE__)
#include <CommonCrypto/CommonDigest.h>
#else //Assumes non-apple will use openssl
#include <openssl/sha.h>
#endif

std::vector<uint8_t> SHA256::digest(const uint8_t* data, size_t length) {
    std::vector<uint8_t> hash(32);

#if defined(__APPLE__)
    CC_SHA256(data, static_cast<CC_LONG>(length), hash.data());
#else
    ::SHA256(data, length, hash.data());
#endif

    return hash;
}
