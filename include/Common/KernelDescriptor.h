/**
 * @file: include/Gpu/Common/KernelDescriptor.h
 * @brief Create a struct to describe GPU-registered kernel objects.
 * @copyright: (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include <cstdint>
#include <array>
#include <stdexcept>

#include "Common/AbstractPtr.h"
#include "Common/Buffer8.h"

namespace Common {
    /**
     * @name KernelDescriptor
     * @brief describe a single kernel object registered with the GPU controller
     */
    struct KernelDescriptor {
        uint64_t kernel_id; ///< pseudo-random identifier
        size_t size; ///< kernel blob size
        AbstractPtr ptr; ///< starting address of kernel blob
        std::array<uint8_t, 32> hash; ///< kernel hash

        /// Exact byte-count emitted by serialize(): 8 + 8 + 8 + 32 = 56
        static constexpr size_t serialized_size =
            /* kernel_id */ 8
            + /* size      */ 8
            + /* ptr       */ 8
            + /* hash      */ 32;

        /**
         * @name serialize
         * @brief Serialize into little-endian bytes:
         *        [kernel_id:8][size:8][ptr:8][hash:32]
         * @return Buffer8
         */
        [[nodiscard]] Buffer8 serialize() const noexcept {
            Buffer8 buf;
            buf.reserve(serialized_size);

            auto append_u64 = [&](uint64_t v) {
                for (int i = 0; i < 8; ++i) {
                    buf.push_back(static_cast<uint8_t>((v >> (8 * i)) & 0xFFu));
                }
            };

            append_u64(kernel_id);
            append_u64(static_cast<uint64_t>(size));
            // reinterpret_cast ptr to preserve full pointer width
            append_u64(static_cast<uint64_t>(ptr));
            buf.insert(buf.end(), hash.begin(), hash.end());

            return buf;
        }

        /**
         * @name deserialize
         * @brief Deserialize from little-endian bytes back into fields.
         * @param buffer Buffer8
         * @throws std::runtime_error if buffer.size() < serialized_size.
         */
        void deserialize(const Buffer8& buffer) {
            if (buffer.size() < serialized_size) {
                throw std::runtime_error(
                    "KernelDescriptor::deserialize: buffer too small");
            }
            auto read_u64 = [&](const size_t offset) {
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
                constexpr size_t hashOffset = 24;
                hash[i] = buffer[hashOffset + i];
            }
        }
    }; // struct KernelDescriptor
} // namespace Common
