/**
* @file include/Gpu/Ipc/Message/GpuInitializeResult.h
 * @brief Define an IPC Message class representing the GPU-initialize result.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class GpuInitializeResult
     * @brief This message is used by an application to signal the GPU controller to initialize the attached
     *        GPU.  It results in GpuInitializeResult.
     */
    class GpuInitializeResult final : public Base {
    public:
        /**
         * @name serialize
         * @brief serialize the GpuInitializeResult message
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            constexpr auto typeByte = Type::GpuInitializeResult;
            Common::Buffer8 buf;
            Common::serialize(buf, static_cast<uint8_t>(typeByte));
            return buf;
        };
        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the GpuInitializeResult Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::GpuInitializeResult;
            verify_message_type(buffer, expected_type);
        }
        /**
         * @name operator ==
         * @brief compare the equivalence of two GpuInitializeResult objects using their serialized forms
         * @param lhs GpuInitializeResult
         * @param rhs GpuInitializeResult
         * @return bool
         */
        friend bool operator==(const GpuInitializeResult& lhs, const GpuInitializeResult& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };
        /**
         * @name operator !=
         * @brief compare two GpuInitializeResult objects using their serialized forms and return true of lhs != rhs
         * @param lhs GpuInitializeResult
         * @param rhs GpuInitializeResult
         * @return bool
         */
        friend bool operator!=(const GpuInitializeResult& lhs, const GpuInitializeResult& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };
    };
}
