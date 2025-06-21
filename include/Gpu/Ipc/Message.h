/**
 * @file include/Gpu/Ipc/Message.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"
#include "Gpu/Ipc/CommandType.h"
#include "Common/AbstractPtr.h"

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
        size_t size = 0;
        Common::AbstractPtr ptr = 0;

        /**
         * @name serialize
         * @brief Serialize this message to a binary payload (fixed 24 bytes).
         * @return Common::Buffer8
         */
        Common::Buffer8 serialize() const;

        /**
         * @name deserialize
         * @brief Deserialize a message from binary data (must be 24 bytes).
         * @throws Gpu::Exceptions::InvalidIpcMessage
         */
        void deserialize(const Common::Buffer8& buffer);
    };

} // namespace Gpu::Ipc
