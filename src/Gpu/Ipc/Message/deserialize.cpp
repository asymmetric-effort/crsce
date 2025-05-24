// file: src/Gpu/Ipc/Message/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include <stdexcept>

#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/InvalidIpcMessage.h"

namespace Gpu::Ipc {

    void Message::deserialize(const Common::Buffer8& buffer) {
        if (buffer.size() != 24)
            throw Gpu::Exceptions::InvalidIpcMessage("deserialization expects 24-byte buffer");

        const uint8_t* data = buffer.data();
        type     = static_cast<CommandType>(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
        kernelId = *reinterpret_cast<const uint32_t*>(data + 4);
        size     = *reinterpret_cast<const uint64_t*>(data + 8);
        ptr      = *reinterpret_cast<const uint64_t*>(data + 16);
    }

}
