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
} // namespace Common
