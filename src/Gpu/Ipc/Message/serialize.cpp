// file: src/Gpu/Ipc/Message/serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include <vector>

namespace Gpu::Ipc {

    std::vector<uint8_t> Message::serialize() const {
        std::vector<uint8_t> out;
        out.reserve(24);
        out.push_back(static_cast<uint8_t>(type));

        for (int i = 0; i < 4; ++i)
            out.push_back(static_cast<uint8_t>((kernelId >> (i * 8)) & 0xFF));

        for (int i = 0; i < 8; ++i)
            out.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));

        for (int i = 0; i < 8; ++i)
            out.push_back(static_cast<uint8_t>((ptr >> (i * 8)) & 0xFF));

        return out;
    }

}
