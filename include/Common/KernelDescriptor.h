/**
* @file include/Gpu/Common/KernelDescriptor.h
 * @brief Define the KernelDescriptor used by Ipc and Gpu::Device
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Common/AbstractPtr.h"

namespace Common {
    /**
     * @name KernelDescriptor
     * @brief A struct that describes a single kernel object registered with the GPU controller
     */
    struct KernelDescriptor {
        uint64_t kernel_id; // pseudo-random identifier
        size_t size; // kernel blob size
        AbstractPtr ptr; // starting address of kernel blob
        std::array<uint8_t, 32> hash; // kernel hash

        /**
         * @brief Serialize the KernelDescriptor into little-endian bytes:
         *        [kernel_id:8][size:8][ptr:8][hash:32]
         */
        [[nodiscard]] Buffer8 serialize() const noexcept {
            Buffer8 buf;
            buf.reserve(8 + 8 + 8 + 32);

            // helper to append a 64-bit integer LE
            auto append_u64 = [&](uint64_t v) {
                for (int i = 0; i < 8; ++i) {
                    buf.push_back(static_cast<uint8_t>((v >> (8 * i)) & 0xFFu));
                }
            };

            append_u64(kernel_id);
            append_u64(static_cast<uint64_t>(size));
            append_u64(static_cast<uint64_t>(ptr));
            buf.insert(buf.end(), hash.begin(), hash.end());

            return buf;
        }

        /**
         * @name deserialize
         * @brief Deserialize from little-endian bytes back into fields.
         * @throws std::runtime_error if buffer.size() < 56.
         */
        void deserialize(const Buffer8& buffer) {
            constexpr size_t expect = 8 + 8 + 8 + 32;
            if (buffer.size() < expect) {
                throw std::runtime_error(
                    "KernelDescriptor::deserialize: buffer too small");
            }

            // helper to read a uint64_t LE from buffer[offset..offset+7]
            auto read_u64 = [&](size_t offset) {
                uint64_t v = 0;
                for (int i = 0; i < 8; ++i) {
                    v |= (static_cast<uint64_t>(buffer[offset + i]) << (8 * i));
                }
                return v;
            };

            kernel_id = read_u64(0);
            size = static_cast<size_t>(read_u64(8));
            ptr = AbstractPtr{read_u64(16)};

            // copy the 32-byte hash
            for (size_t i = 0; i < hash.size(); ++i) {
                hash[i] = buffer[24 + i];
            }
        }
    }; // KernelDescriptor
}
