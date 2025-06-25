/**
 * @file include/Gpu/Ipc/Message.h
 * @brief Define IPC Pipe Message Base Class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/AbstractPtr.h"
#include <cstring>

namespace Gpu::Ipc {
    /**
     * @class Message
     * @namespace Gpu::Ipc
     * @brief IPC Pipe Message Class
     * @ref docs/Gpu/Design/Gpu-Ipc-Message.md
     */
    class Message {
    public:
        /**
         * @name constructor
         * @class Message
         * @namespace Gpu::Ipc
         * @brief initialize the Message object
         */
        Message() =default;

        virtual ~Message() = default;
        /**
         * @name serialize
         * @brief virtual serialize function.  This is a last resort.
         * @return Common::Buffer8
         */
        virtual Common::Buffer8 serialize() const { return (Common::Buffer8){}; };
        /**
         * @name deserialize
         * @brief virtual deserialize function
         * @throws UndefinedMethod
         */
        virtual void deserialize(const Common::Buffer8& buffer) {throw std::runtime_error("undefined method");};
        /**
         * @name serialize
         * @brief virtual equality operator (compares serialized state).  True only if both are empty.
         * @return bool
         */
        friend bool operator==(const Message& a, const Message& b) { return (a.serialize() == b.serialize()); };
        /**
         * @name serialize
         * @brief virtual inequality operator (compares serialized state). True only if one is not empty.
         * @return bool
         */
        friend bool operator!=(const Message& a, const Message& b) { return (a.serialize() != b.serialize()); };
    };

    class InitializeGpuMessage final : public Message {
    public:
        Common::Buffer8 serialize() const override { throw std::runtime_error("undefined method"); };
        void deserialize(const Common::Buffer8& buffer) override { throw std::runtime_error("undefined method"); };
        friend bool operator==(const InitializeGpuMessage& a, const InitializeGpuMessage& b) {return false;}
        friend bool operator!=(const InitializeGpuMessage& a, const InitializeGpuMessage& b) {return false;}
    };
} // namespace Gpu::Ipc
