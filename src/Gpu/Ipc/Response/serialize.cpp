// file: src/Gpu/Ipc/Response/serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Response.h"
#include <cstring>

namespace Gpu::Ipc {

    Common::Buffer8 Response::serialize() const {
        Common::Buffer8 output;
        output.reserve(1 + 8 + data.size());
        output.push_back(static_cast<uint8_t>(status));

        for (int i = 0; i < 8; ++i)
            output.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));

        output.insert(output.end(), data.begin(), data.end());
        return output;
    }

}
