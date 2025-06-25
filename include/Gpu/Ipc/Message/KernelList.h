/**
 * @file include/Gpu/Ipc/Message/KernelList.h
 * @brief Define an IPC Message class representing the kernel list IPC message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class KernelList
     * @brief This message represents an IPC message from the GPU Controller
     */
    class KernelList final : public Base {
    public:
        /**
         * @name constructor
         * @brief Request the GPU controller to list the registered kernels.
         * @param offset uint16_t - paginated starting row number from the kernel registry table (default:0)
         * @param limit uint16_t - paginated number of records returned from the kernel registry(default:1000)
         */
        explicit KernelList(const uint16_t offset = 0, const uint16_t limit = 1000) : offset_(offset), limit_(limit) {
            /*noop*/
        };
        /**
         * @name serialize
         * @brief serialize the KernelList message consisting of Message Type number of bytes requested (size_)
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const noexcept override {
            // first byte = message type
            constexpr uint8_t typeByte = static_cast<uint8_t>(Type::KernelList);
            const uint16_t offset = static_cast<uint16_t>(offset_);
            const uint16_t limit = static_cast<uint16_t>(limit_);
            // serialize to byte vector
            return Common::Buffer8{
                typeByte,
                static_cast<uint8_t>(offset & 0xFFu),
                static_cast<uint8_t>(offset & 0xFF00u >> 8),
                static_cast<uint8_t>(limit & 0xFFu),
                static_cast<uint8_t>(limit & 0xFF00u >> 8)
            };
        }

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the KernelList Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::KernelList;
            verify_message_type(buffer, expected_type);
            if (buffer.size() < 5) throw std::runtime_error("KernelList::deserialize: buffer too small");
            // (optional) verify buf[0] == Type::KernelList
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
         * @brief compare the equivalence of two KernelList objects using their serialized forms
         * @param lhs KernelList
         * @param rhs KernelList
         * @return bool
         */
        friend bool operator==(const KernelList& lhs, const KernelList& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two KernelList objects using their serialized forms and return true of lhs != rhs
         * @param lhs KernelList
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const KernelList& lhs, const KernelList& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };

    private:
        uint16_t offset_;
        uint16_t limit_;
    };
}
