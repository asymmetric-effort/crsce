/**
 * @file include/Gpu/Ipc/Message/KernelListResult.h
 * @brief Define an IPC Message class representing the kernel list IPC message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include <utility>

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/KernelDescriptor.h"
#include "Common/KernelTable.h"
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
        explicit KernelListResult(Common::KernelTable list) : table_(std::move(list)) {
            /*noop*/
        };
        /**
         * @name serialize
         * @brief serialize the KernelListResult message consisting of Message Type number of bytes requested (size_)
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            constexpr auto typeByte = static_cast<uint8_t>(Type::KernelList);
            Common::Buffer8 buf;
            Common::serialize(buf, static_cast<uint8_t>(typeByte));
            Common::serialize(buf, table_);
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
            //Todo: implement deserialization of a KernelList
        }

        /**
         * @name kernel_list
         * @brief return the row offset for the requested records
         * @return table_ KernelList
         */
        [[nodiscard]] Common::KernelTable kernel_list() const { return table_; }

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
        /**
         * @name table_
         * @brief a table of GPU kernels
         */
        Common::KernelTable table_;
    };
}
