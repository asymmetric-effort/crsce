/**
 * @file include/Gpu/Ipc/Message/MemoryAlloc.h
 * @brief Define an IPC Message class representing the memory allocation request for the GPU
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class MemoryAlloc
     * @brief This message represents an IPC message to allocate GPU memory
     */
    class MemoryAlloc final : public Base {
    public:
        /**
         * @name constructor
         * @brief Request allocation of GPU memory
         * @param size size_t : number of bytes requested.
         */
        explicit MemoryAlloc(const size_t size) : size_(size) {
            /*noop*/
        };
        /**
         * @name serialize
         * @brief serialize the MemoryAlloc message consisting of Message Type number of bytes requested (size_)
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const noexcept override {
            // first byte = message type
            constexpr uint8_t typeByte = static_cast<uint8_t>(Type::MemoryAlloc);
            // next 8 bytes = little-endian size_t
            const uint64_t n = size_;
            // serialize to byte vector
            return Common::Buffer8{
                typeByte,
                static_cast<uint8_t>(n & 0xFFu),
                static_cast<uint8_t>((n >> 8) & 0xFFu),
                static_cast<uint8_t>((n >> 16) & 0xFFu),
                static_cast<uint8_t>((n >> 24) & 0xFFu),
                static_cast<uint8_t>((n >> 32) & 0xFFu),
                static_cast<uint8_t>((n >> 40) & 0xFFu),
                static_cast<uint8_t>((n >> 48) & 0xFFu),
                static_cast<uint8_t>((n >> 56) & 0xFFu),
            };
        }

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the MemoryAlloc Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::MemoryAlloc;
            verify_message_type(buffer, expected_type);
            if (buffer.size() < 9) {
                throw std::runtime_error("MemoryAlloc::deserialize: buffer too small");
            }
            // (optional) verify buf[0] == Type::MemoryAlloc
            size_ = static_cast<size_t>(buffer[1]) |
                (static_cast<size_t>(buffer[2]) << 8) |
                (static_cast<size_t>(buffer[3]) << 16) |
                (static_cast<size_t>(buffer[4]) << 24) |
                (static_cast<size_t>(buffer[5]) << 32) |
                (static_cast<size_t>(buffer[6]) << 40) |
                (static_cast<size_t>(buffer[7]) << 48) |
                (static_cast<size_t>(buffer[8]) << 56);
        }

        /**
         * @name size
         * @brief return the requested memory allocation
         * @return size_t
         */
        size_t size() const { return size_; }

        /**
         * @name operator ==
         * @brief compare the equivalence of two MemoryAlloc objects using their serialized forms
         * @param lhs MemoryAlloc
         * @param rhs MemoryAlloc
         * @return bool
         */
        friend bool operator==(const MemoryAlloc& lhs, const MemoryAlloc& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two MemoryAlloc objects using their serialized forms and return true of lhs != rhs
         * @param lhs MemoryAlloc
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const MemoryAlloc& lhs, const MemoryAlloc& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };

    private:
        size_t size_;
    };
}
