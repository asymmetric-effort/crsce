/**
 * @file include/Gpu/Ipc/Message/MemoryAllocResult.h
 * @brief Define an IPC Message class representing the memory allocation response to MemoryAlloc message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Common/AbstractPtr.h"
#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class MemoryAllocResult
     * @brief This message represents an IPC response from the GPU Controller
     */
    class MemoryAllocResult final : public Base {
    public:
        /**
         * @name constructor
         * @brief Response to MemoryAlloc which should identify the amount of allocated memory and AbstractPtr
         * @param size size_t : number of bytes requested.
         */
        explicit MemoryAllocResult(const Common::AbstractPtr ptr, const size_t size) : size_(size), ptr_(ptr) {
            /*noop*/
        };
        /**
         * @name serialize
         * @brief serialize the MemoryAllocResult message consisting of Message Type number of bytes requested (size_)
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const noexcept override {
            // first byte = message type
            constexpr uint8_t typeByte = static_cast<uint8_t>(Type::MemoryAllocResult);
            // next 8 bytes = little-endian size_t
            const uint64_t sz64 = size_;
            // next 8 bytes = little-endian Common::AbstractPtr
            const uint64_t p64 = static_cast<uint8_t>(typeByte);
            // serialize to byte vector
            return Common::Buffer8{
                typeByte,
                static_cast<uint8_t>(sz64 & 0xFFu),
                static_cast<uint8_t>((sz64 >> 8) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 16) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 24) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 32) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 40) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 48) & 0xFFu),
                static_cast<uint8_t>((sz64 >> 56) & 0xFFu),
                static_cast<uint8_t>((p64 >> 8) & 0xFFu),
                static_cast<uint8_t>((p64 >> 16) & 0xFFu),
                static_cast<uint8_t>((p64 >> 24) & 0xFFu),
                static_cast<uint8_t>((p64 >> 32) & 0xFFu),
                static_cast<uint8_t>((p64 >> 40) & 0xFFu),
                static_cast<uint8_t>((p64 >> 48) & 0xFFu),
                static_cast<uint8_t>((p64 >> 56) & 0xFFu),
            };
        }

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the MemoryAllocResult Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::MemoryAllocResult;
            verify_message_type(buffer, expected_type);
            if (buffer.size() < 9) {
                throw std::runtime_error("MemoryAllocResult::deserialize: buffer too small");
            }
            // (optional) verify buf[0] == Type::MemoryAllocResult
            size_ = static_cast<size_t>(buffer[1]) |
                (static_cast<size_t>(buffer[2]) << 8) |
                (static_cast<size_t>(buffer[3]) << 16) |
                (static_cast<size_t>(buffer[4]) << 24) |
                (static_cast<size_t>(buffer[5]) << 32) |
                (static_cast<size_t>(buffer[6]) << 40) |
                (static_cast<size_t>(buffer[7]) << 48) |
                (static_cast<size_t>(buffer[8]) << 56);

            ptr_ = static_cast<size_t>(buffer[9]) |
                (static_cast<size_t>(buffer[10]) << 8) |
                (static_cast<size_t>(buffer[11]) << 16) |
                (static_cast<size_t>(buffer[12]) << 24) |
                (static_cast<size_t>(buffer[13]) << 32) |
                (static_cast<size_t>(buffer[14]) << 40) |
                (static_cast<size_t>(buffer[15]) << 48) |
                (static_cast<size_t>(buffer[16]) << 56);
        }

        /**
         * @name size
         * @brief return the allocated memory size (in bytes)
         * @return size_t
         */
        size_t size() const { return size_; }

        /**
         * @name ptr
         * @brief return the Common::AbstractPtr reference to the MemoryTracker table.
         * @return Common::AbstractPtr
         */
        Common::AbstractPtr size() const { return ptr_; }

        /**
         * @name operator ==
         * @brief compare the equivalence of two MemoryAllocResult objects using their serialized forms
         * @param lhs MemoryAllocResult
         * @param rhs MemoryAllocResult
         * @return bool
         */
        friend bool operator==(const MemoryAllocResult& lhs, const MemoryAllocResult& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two MemoryAllocResult objects using their serialized forms and return true of lhs != rhs
         * @param lhs MemoryAllocResult
         * @param rhs GpuReset
         * @return bool
         */
        friend bool operator!=(const MemoryAllocResult& lhs, const MemoryAllocResult& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };

    private:
        /**
         * @name ptr_
         * @brief reference to allocated memory from the MemoryTracker table maintained by GPU controller
         */
        Common::AbstractPtr ptr_;
        /**
         * @name size_
         * @brief define the number of bytes allocated.
         */
        size_t size_;
    };
}
