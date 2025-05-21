// file: include/Gpu/Ipc/Response.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include <cstdint>
#include <vector>

namespace Gpu::Ipc {

    /**
     * @class Response
     * @brief Represents a response message sent from child to parent over IPC.
     *
     * Format:
     * [ status (1 byte) | size (8 bytes LE) | payload (size bytes) ]
     */
    class Response {
    public:
        static constexpr size_t kFixedHeaderSize = sizeof(uint8_t) + sizeof(uint64_t);

        uint8_t status = 1;             ///< 0 = success; non-zero = failure code
        uint64_t size = 0;              ///< Payload size in bytes
        std::vector<uint8_t> data;      ///< Optional payload buffer

        std::vector<uint8_t> serialize() const;
        static Response deserialize(const uint8_t* buffer, size_t length);
    };

} // namespace Gpu::Ipc
