/**
 * @file src/Gpu/Ipc/Message/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"

namespace Gpu::Ipc
{
    /**
     * @name constructor
     * @class Message
     * @namespace Gpu::Ipc
     * @brief initialize the Message object
     * @param type  CommandType
     * @param kernelId  uint32_t
     * @param payload_size size_t
     * @param ptr Common::AbstractPtr
     */
    Message::Message(const CommandType type, const uint32_t kernelId,
                     const size_t payload_size,const Common::AbstractPtr ptr
    ) noexcept : type_(type), kernelId_(kernelId), payload_size_(payload_size), ptr_(ptr)
    {
        /* noop*/
    }
}
