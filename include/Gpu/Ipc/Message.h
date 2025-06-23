/**
 * @file include/Gpu/Ipc/Message.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"
#include "Gpu/Ipc/CommandType.h"
#include "Common/AbstractPtr.h"

namespace Gpu::Ipc
{
    /**
     * @brief Encapsulates an IPC command for the GPU emulator.
     * @ref docs/Gpu/Design/Gpu-Ipc-Message.md
     *
     * Serialized form: fixed 24-byte buffer containing:
     * - 4 bytes: CommandType (uint32_t little endian)
     * - 4 bytes: kernelId    (uint32_t little endian)
     * - 8 bytes: size        (size_t little endian)
     * - 8 bytes: ptr         (AbstractPtr little endian)
     */
    class Message
    {
    public:
        Message() = default;

        Message(CommandType type, uint32_t kernelId, size_t size, Common::AbstractPtr ptr) noexcept;

        ~Message() = default;

        [[nodiscard]] Common::Buffer8 serialize() const;
        void deserialize(const Common::Buffer8& buffer);

        [[nodiscard]] CommandType type() const noexcept { return type_; }
        void type(const CommandType t) noexcept { type_ = t; };

        [[nodiscard]] uint32_t kernelId() const noexcept { return kernelId_; }
        void kernelId(const uint32_t id) noexcept { kernelId_ = id; };

        [[nodiscard]] size_t size() const noexcept { return size_; }
        void size(const size_t sz) noexcept { size_ = sz; };

        [[nodiscard]] Common::AbstractPtr ptr() const noexcept { return ptr_; }
        void ptr(const Common::AbstractPtr p) noexcept { ptr_ = p; };

    private:
        CommandType type_ = CommandType::Init;
        uint32_t kernelId_{0};
        size_t size_{0};
        Common::AbstractPtr ptr_{0};
    };
} // namespace Gpu::Ipc
