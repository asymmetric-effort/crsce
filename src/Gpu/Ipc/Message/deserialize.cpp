// file: src/Gpu/Ipc/Message/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include <stdexcept>

namespace Gpu::Ipc {

    Message Message::deserialize(const uint8_t* data, std::size_t length) {
        if (length < 24)
            throw std::runtime_error("Gpu::Ipc::Message::deserialize(): insufficient input length");

        Message m;
        m.type = static_cast<CommandType>(data[0]);

        m.kernelId = 0;
        for (int i = 0; i < 4; ++i)
            m.kernelId |= static_cast<uint32_t>(data[1 + i]) << (i * 8);

        m.size = 0;
        for (int i = 0; i < 8; ++i)
            m.size |= static_cast<uint64_t>(data[5 + i]) << (i * 8);

        m.ptr = 0;
        for (int i = 0; i < 8; ++i)
            m.ptr |= static_cast<Common::AbstractPtr>(data[13 + i]) << (i * 8);

        return m;
    }

}
