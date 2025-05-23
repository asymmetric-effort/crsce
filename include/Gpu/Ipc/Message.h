// file: include/Gpu/Ipc/Message.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <cstdint>
#include "Gpu/Ipc/CommandType.h"
#include "Gpu/Common/AbstractPtr.h"

namespace Gpu::Ipc {

    /**
     * @name Gpu::Ipc::Message
     * @brief Represents a command sent from the parent to the emulator GPU child.
     * @ref docs/Gpu/Design/Gpu-Ipc-Message.md
     *
     * The Message structure is serialized and written to the emulator's IPC input pipe.
     * It encodes the command, memory address, data size, and optional kernel ID.
     */
    struct Message {
        CommandType type = CommandType::Init;
        uint32_t kernelId = 0;
        uint64_t size = 0;
        Common::AbstractPtr ptr = 0;

        /**
         * Serialize this message to a binary payload (fixed 24 bytes).
         */
        std::vector<uint8_t> serialize() const;

        /**
         * Deserialize a message from binary data (must be 24 bytes).
         */
        static Message deserialize(const uint8_t* data, std::size_t length);
    };

} // namespace Gpu::Ipc
