/**
 * @file include/Gpu/Ipc/Message/GpuShutdown.h
 * @brief Define an IPC Message class representing the GPU shutdown.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Gpu/Ipc/Message/GpuType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class GpuShutdown
     * @brief This message signals the Gpu controller to shutdown the Gpu and controller via IPC
     */
    class GpuShutdown final : public Base {
    public:
        /**
         * @name serialize
         * @brief serialize the GpuShutdown message
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            constexpr auto typeByte = Type::GpuShutdown;
            Common::Buffer8 buf;
            Common::serialize(buf, static_cast<uint8_t>(typeByte));
            return buf;
        };

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the GpuShutdown Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::GpuShutdown;
            verify_message_type(buffer, expected_type);
        }

        /**
         * @name operator ==
         * @brief compare the equivalence of two GpuShutdown objects using their serialized forms
         * @param lhs GpuShutdown
         * @param rhs GpuShutdown
         * @return bool
         */
        friend bool operator==(const GpuShutdown& lhs, const GpuShutdown& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two GpuShutdown objects using their serialized forms and return true of lhs != rhs
         * @param lhs GpuShutdown
         * @param rhs GpuShutdown
         * @return bool
         */
        friend bool operator!=(const GpuShutdown& lhs, const GpuShutdown& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };
    };
}
