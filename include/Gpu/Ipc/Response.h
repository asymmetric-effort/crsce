/**
 * @file include/Gpu/Ipc/Response.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <vector>
#include <cstdint>
#include "Gpu/Ipc/FailureCodes.h"
#include "Common/Buffer8.h"

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
        FailureCodes status = FailureCodes::IpcSuccess; ///< Result code
        uint64_t size = 0;                           ///< Payload length
        Common::Buffer8 data;                        ///< Optional binary result data

        /**
         * @name serialize
         * @brief Serialize this Response into a binary buffer for IPC transport.
         * @return Common::Buffer8
         */
        Common::Buffer8 serialize() const;

        /**
         * @name deserialize
         * @brief Deserialize binary data into a Response object.
         * @throws Gpu::Exceptions::InvalidIpcResponse
         */
        void deserialize(const Common::Buffer8& data);
    };

} // namespace Gpu::Ipc
