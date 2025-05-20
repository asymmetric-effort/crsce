// file: src/Gpu/Device/receiveResponse.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>
#include <vector>

namespace Gpu {
    bool Emulator::receiveResponse(void *payload, const size_t size) const {
        if (!isChild_) {
            // Read fixed header size: 1 status byte + 8 size bytes
            uint8_t header[1 + sizeof(uint64_t)];
            if (const ssize_t n = read(fromChildFd_, header, sizeof(header)); n != static_cast<ssize_t>(sizeof(header)))
                return false;

            // Parse header
            const uint8_t status = header[0];
            uint64_t dataSize;
            std::memcpy(&dataSize, header + 1, sizeof(uint64_t));

            // Read payload
            std::vector<uint8_t> data(dataSize);
            if (read(fromChildFd_, data.data(), dataSize) != static_cast<ssize_t>(dataSize))
                return false;

            if (status != 0)
                return false;

            // Copy payload into caller buffer
            if (payload && size > 0) {
                if (dataSize < size)
                    return false;
                std::memcpy(payload, data.data(), size);
            }

            return true;
        }
        return false;
    }
} // namespace Gpu
