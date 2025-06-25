/**
 * @file include/Gpu/Ipc/Message/GpuReset.h
 * @brief Define an IPC Message class representing the GPU-reset message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Gpu/Ipc/Message/GpuType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class GpuReset
     * @brief This message represents an IPC reset signal to the GPU Controller
     */
    class GpuReset final : public Base {
    public:
        /**
         * @name serialize
         * @brief serialize the GpuInitialize message
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            auto v = Type::GpuReset;
            return Common::Buffer8{
                static_cast<uint8_t>(v),
            };
        };

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the GpuReset Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::GpuReset;
            verify_message_type(buffer, expected_type);
        }

        /**
         * @name operator ==
         * @brief compare the equivalence of two GpuReset objects using their serialized forms
         * @param lhs GpuReset
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator==(const GpuReset& lhs, const GpuReset& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two GpuReset objects using their serialized forms and return true of lhs != rhs
         * @param lhs GpuReset
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const GpuReset& lhs, const GpuReset& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };
    };
}
