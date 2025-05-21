// file: include/Gpu/Ipc/Message.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include <cstdint>
#include <vector>

namespace Gpu::Ipc {

    /**
     * @class Message
     * @brief Represents a command sent from parent to child via IPC.
     *
     * This is the serialized header structure sent across pipes, encoding the command
     * type, an optional kernel ID, size field, and device memory pointer.
     */
    class Message {
    public:
        static constexpr size_t kFixedSize = sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint64_t);

        uint32_t type = 0;       ///< Command type (enum CommandType encoded as uint32_t)
        uint32_t kernelId = 0;   ///< Used only for LaunchTask
        uint64_t size = 0;       ///< Size of buffer (for Alloc/Write/Read)
        uint64_t ptr = 0;        ///< Device memory address or handle

        std::vector<uint8_t> serialize() const;
        static Message deserialize(const uint8_t* data, size_t length);
    };

} // namespace Gpu::Ipc
