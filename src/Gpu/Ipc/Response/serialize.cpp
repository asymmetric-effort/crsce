/**
 * @file src/Gpu/Ipc/Response/serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Response.h"
#include <cstring>
#include "utils/to_underlying.h"

namespace Gpu::Ipc {
    Common::Buffer8 Response::serialize() const {
        Common::Buffer8 output;
        output.reserve(1 + 8 + data_.size());
        output.push_back(std::to_underlying(status()));

        for (int i = 0; i < 8; ++i)
            output.push_back(static_cast<uint8_t>((payload_size_ >> (i * 8)) & 0xFF));

        output.insert(output.end(), data_.begin(), data_.end());
        return output;
    }
}
