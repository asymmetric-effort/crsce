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
    class Response {
    public:
        Response() = default;
        /**
         * @name constructor
         * @class Response
         * @namespace Gpu::Ipc
         * @brief initialize the Response object
         * @param status FailureCodes::IpcSuccess
         * @param payload_size size_t
         * @param data Common::Buffer8
         */
        Response(const FailureCodes status, const size_t payload_size, const Common::Buffer8& data) noexcept
        : status_(status), payload_size_(payload_size), data_(data) { /*noop*/ };

        ~Response() = default;
        /**
         * @name serialize
         * @brief Serialize this Response into a binary buffer for IPC transport.
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const;

        /**
         * @name deserialize
         * @brief Deserialize binary data into a Response object.
         * @throws Gpu::Exceptions::InvalidIpcResponse
         */
        void deserialize(const Common::Buffer8& data);

        [[nodiscard]] FailureCodes status() const { return status_; };
        void status(const FailureCodes status) { status_ = status; };

        [[nodiscard]] size_t size() const noexcept { return payload_size_; };
        void size(const size_t payload_size) { payload_size_ = payload_size; };

        [[nodiscard]] Common::Buffer8& data() noexcept { return data_; };
        void data(const Common::Buffer8& data) { data_ = data; };

    private:
        FailureCodes status_ = FailureCodes::IpcSuccess;
        size_t payload_size_ = 0;
        Common::Buffer8 data_;
    };
} // namespace Gpu::Ipc
