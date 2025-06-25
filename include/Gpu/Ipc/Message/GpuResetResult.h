/**
 * @file include/Gpu/Ipc/Message/GpuResetResult.h
 * @brief Define an IPC Message class representing the GPU-reset result
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Gpu/Ipc/Message/GpuType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class GpuResetResult
     * @brief This message represents an IPC response from the GPU Controller
     */
    class GpuResetResult final : public Base {
    public:
        /**
         * @name serialize
         * @brief serialize the GpuResetResult message
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            auto v = Type::GpuResetResult;
            return Common::Buffer8{
                static_cast<uint8_t>(v),
            };
        };

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the GpuResetResult Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::GpuResetResult;
            verify_message_type(buffer, expected_type);
        }

        /**
         * @name operator ==
         * @brief compare the equivalence of two GpuResetResult objects using their serialized forms
         * @param lhs GpuResetResult
         * @param rhs GpuResetResult
         * @return bool
         */
        friend bool operator==(const GpuResetResult& lhs, const GpuResetResult& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two GpuResetResult objects using their serialized forms and return true of lhs != rhs
         * @param lhs GpuResetResult
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const GpuResetResult& lhs, const GpuResetResult& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };
    };
}
