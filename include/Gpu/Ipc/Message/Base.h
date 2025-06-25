/**
 * @file include/Gpu/Ipc/Message/Base.h
 * @brief Define IPC Pipe Message Base Class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @class Message
     * @namespace Gpu::Ipc
     * @brief IPC Pipe Message Class
     * @ref docs/Gpu/Design/Gpu-Ipc-Message.md
     */
    class Base {
    public:
        /**
         * @name constructor
         * @class Base
         * @namespace Gpu::Ipc
         * @brief initialize the Message object
         */
        Base() =default;

        virtual ~Base() = default;
        /**
         * @name serialize
         * @brief virtual serialize function.  This is a last resort.
         * @return Common::Buffer8
         */
        [[nodiscard]] virtual Common::Buffer8 serialize() const { return (Common::Buffer8){}; };
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
        friend bool operator==(const Base& a, const Base& b) { return (a.serialize() == b.serialize()); };
        /**
         * @name serialize
         * @brief virtual inequality operator (compares serialized state). True only if one is not empty.
         * @return bool
         */
        friend bool operator!=(const Base& a, const Base& b) { return (a.serialize() != b.serialize()); };
    };


} // namespace Gpu::Ipc
