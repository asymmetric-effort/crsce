/**
 * @file include/Gpu/Ipc/Message/KernelListResult.h
 * @brief Define an IPC Message class representing the kernel list IPC message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/KernelDescriptor.h"
#include "Common/Buffer8.h"


namespace Gpu::Ipc::Message {
    /**
     * @class KernelListResult
     * @brief This message represents the response to KernelList
     */
    class KernelListResult final : public Base {
    public:
        /**
         * @name constructor
         * @brief Request the GPU controller to list the registered kernels.
         * @param list std::vector<Common::KernelDescriptor>
         */
        explicit KernelListResult(std::vector<Common::KernelDescriptor>& list): list_(list) {/*noop*/};
        /**
         * @name serialize
         * @brief serialize the KernelListResult message consisting of Message Type number of bytes requested (size_)
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            // 1) type byte
            Common::Buffer8 buf;
            buf.reserve(1 + 4 + list_.size() * Common::KernelDescriptor::serialized_size);
            buf.push_back(static_cast<uint8_t>(Type::KernelListResult));

            // 2) 32-bit little-endian count
            uint32_t count = static_cast<uint32_t>(list_.size());
            for (int i = 0; i < 4; ++i) {
                buf.push_back(static_cast<uint8_t>((count >> (8 * i)) & 0xFFu));
            }

            // 3) each KernelDescriptor
            for (auto const &desc : list_) {
                auto part = desc.serialize();
                buf.insert(buf.end(), part.begin(), part.end());
            }

            return buf;
        }


        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the KernelListResult Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::KernelListResult;
            verify_message_type(buffer, expected_type);
            if (buffer.size() < 5) throw std::runtime_error("KernelListResult::deserialize: buffer too small");
            // (optional) verify buf[0] == Type::KernelListResult
            offset_ = static_cast<uint16_t>(buffer[1]) | static_cast<uint16_t>(buffer[2]) << 8;
            limit_ = static_cast<uint16_t>(buffer[3]) | static_cast<uint16_t>(buffer[4]) << 24;
        }

        /**
         * @name offset
         * @brief return the row offset for the requested records
         * @return offset_
         */
        uint16_t offset() const { return offset_; }


        /**
         * @name limit
         * @brief return the row count requested in the recordset
         * @return limit_
         */
        uint16_t size() const { return limit_; }

        /**
         * @name operator ==
         * @brief compare the equivalence of two KernelListResult objects using their serialized forms
         * @param lhs KernelListResult
         * @param rhs KernelListResult
         * @return bool
         */
        friend bool operator==(const KernelListResult& lhs, const KernelListResult& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two KernelListResult objects using their serialized forms and return true of lhs != rhs
         * @param lhs KernelListResult
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const KernelListResult& lhs, const KernelListResult& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };

    private:
        std::vector<KernelDescriptorStruct> list_;
    };
}
