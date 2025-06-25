/**
 * @file include/Common/Buffer8.h
 * @ref docs/Gpu/Design/Common-Buffer8.md
 * @brief A byte buffer used for memory and IPC payloads within the GPU abstraction layer.
 *
 * Buffer8 is defined as a dynamic array of `uint8_t`. It is used to transmit or receive
 * opaque binary data in IPC channels and GPU memory functions.
 *
 * Typical use cases:
 * - Host-to-device memory transfer (`write`)
 * - Device-to-host memory readback (`read`)
 * - IPC payload encoding in Gpu::Ipc::Response
 *
 * @example
 *      Common::Buffer8 payload = {0x01, 0x02, 0x03};
 *      device.write(payload, abstractPtr);
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <vector>
#include <cstdint>

namespace Common {
    /**
     * @name Common::Buffer8
     * @typedef Common::Buffer8
     */
    using Buffer8 = std::vector<uint8_t>;

    /**
     * @name operator==
     * @brief compare two Buffer8 objects and return true if equal
     * @param lhs Buffer8
     * @param rhs Buffer8
     * @return bool
     */
    inline bool operator==(const Buffer8& lhs, const Buffer8& rhs) {
        return lhs.size() == rhs.size() &&
            std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    /**
     * @name operator!=
     * @brief compare two Buffer8 objects and return true if not equal
     * @param lhs Buffer8
     * @param rhs Buffer8
     * @return bool
     */
    inline bool operator!=(const Buffer8& lhs, const Buffer8& rhs) {
        return lhs.size() != rhs.size() ||
            !std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    /**
     * @name serialize (8bit)
     * @brief serialize a single byte input to a Buffer8
     * @param buf Buffer8
     * @param value uint8_t
     */
    inline void serialize(Buffer8& buf, const uint8_t& value) {
        buf.push_back(static_cast<uint8_t>(value));
    }
    /**
     * @name serialize (16bit)
     * @brief serialize a single 16-bit input to a Buffer8
     * @param buf Buffer8
     * @param value uint16_t
     */
    inline void serialize(Buffer8& buf, const uint16_t& value) {
        buf.push_back(static_cast<uint8_t>(value && 0x00FFu));
        buf.push_back(static_cast<uint8_t>(value && 0xFF00u) >> 8);
    }
    /**
     * @name serialize (32bit)
     * @brief serialize a single 32-bit input to a Buffer8
     * @param buf Buffer8
     * @param value uint32_t
     */
    inline void serialize(Buffer8& buf, const uint32_t& value) {
        for (int i = 0; i < sizeof(uint32_t); ++i) {
            buf.push_back(static_cast<uint8_t>((value >> (8 * i)) & 0xFFu));
        }
    }
    /**
     * @name serialize (64bit)
     * @brief serialize a single 64-bit input to a Buffer8
     * @param buf Buffer8
     * @param value uint64_t
     */
    inline void serialize(Buffer8& buf, const uint64_t& value) {
        for (int i = 0; i < sizeof(uint32_t); ++i) {
            buf.push_back(static_cast<uint8_t>((value >> (8 * i)) & 0xFFu));
        }
    }
} // namespace Common
