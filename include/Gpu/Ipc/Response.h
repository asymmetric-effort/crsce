// file: include/Gpu/Ipc/Response.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <vector>
#include <cstdint>
#include "Gpu/Ipc/FailureCodes.h"
#include "Gpu/Common/Buffer8.h"

namespace Gpu::Ipc {

    /**
     * @name Gpu::Ipc::Response
     * @brief Represents the serialized response sent from child to parent via IPC.
     * @ref docs/Gpu/Design/Gpu-Ipc-Response.md
     *
     * The Response struct wraps a return status, optional payload size, and optional payload data
     * returned by an emulated GPU operation.
     */
    struct Response {
        FailureCodes status = FailureCodes::Success; ///< Result code
        uint64_t size = 0;                           ///< Payload length
        Common::Buffer8 data;                        ///< Optional binary result data

        /**
         * Serialize this Response into a binary buffer for IPC transport.
         */
        Common::Buffer8 serialize() const;

        /**
         * Deserialize binary data into a Response object.
         * Throws std::runtime_error on invalid or undersized input.
         */
        static Response deserialize(const uint8_t* buffer, std::size_t length);
    };

} // namespace Gpu::Ipc
