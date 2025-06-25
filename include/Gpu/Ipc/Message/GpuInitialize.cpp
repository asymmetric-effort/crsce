/**
* @file include/Gpu/Ipc/Message/GpuInitialize.h
 * @brief Define an IPC Message class representing the GPU-initialize message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message/Base.h"
#include "Gpu/Ipc/Message/MessageType.h"
#include "Common/Buffer8.h"

namespace Gpu::Ipc::Message {
    /**
     * @enum GpuType
     * @brief Enumerate the supported GPU types
     */
    enum class GpuType : uint8_t {
        Emulator = 0x00,
        Cuda = 0x01,
        AmdRoc = 0x02,
        AppleMetal = 0x03,
        MaxGpuType = AppleMetal,
    };

    /**
     * @class GpuInitialize
     * @brief This message is used by an application to signal the GPU controller to initialize the attached
     *        GPU.  It results in GpuInitializeResult.
     */
    class GpuInitialize final : public Base {
    public:
        /**
         * @name constructor
         * @brief create a GpuInitialize instance
         * @param gpu_type GpuType
         */
        explicit GpuInitialize(const GpuType gpu_type = GpuType::Emulator) : gpu_type_(gpu_type) {
            /*noop*/
        }

        /**
         * @name configure
         * @brief Configure the message with parameters
         * @param gpu_type GpuType
         */
        void configure(GpuType gpu_type = GpuType::Emulator) { gpu_type_ = gpu_type; }

        /**
         * @name serialize
         * @brief serialize the GpuInitialize message
         * @return Common::Buffer8
         */
        [[nodiscard]] Common::Buffer8 serialize() const override {
            auto v = Type::GpuInitialize;
            return Common::Buffer8{
                static_cast<uint8_t>(v),
                static_cast<uint8_t>(gpu_type_),
            };
        };

        /**
         * @name deserialize
         * @brief deserialize a Common::Buffer8 message into the GpuInitialize Message
         * @param buffer Common::Buffer8&
         */
        void deserialize(const Common::Buffer8& buffer) override {
            auto expected_type = Type::GpuInitialize;
            verify_message_type(buffer, expected_type);
            // deserialize GpuType (byte1)
            gpu_type_ = static_cast<GpuType>(buffer[1]);
        }

        /**
         * @name operator ==
         * @brief compare the equivalence of two GpuInitialize objects using their serialized forms
         * @param lhs GpuInitialize
         * @param rhs GpuInitialize
         * @return bool
         */
        friend bool operator==(const GpuInitialize& lhs, const GpuInitialize& rhs) {
            return (lhs.serialize() == rhs.serialize());
        };

        /**
         * @name operator !=
         * @brief compare two GpuInitialize objects using their serialized forms and return true of lhs != rhs
         * @param lhs GpuInitialize
         * @param rhs GpuInitialize
         * @return bool
         */
        friend bool operator!=(const GpuInitialize& lhs, const GpuInitialize& rhs) {
            return (lhs.serialize() != rhs.serialize());
        };

    private:
        /**
         * @name gpu_type
         * @brief The type of GPU to be intialized (e.g. Emulator
         */
        GpuType gpu_type_;
    };
}
