// file: src/Gpu/Device/receiveResponseMsg.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>
#include <vector>

namespace Gpu {

    IpcResponseMsg Emulator::receiveResponseMsg() const {
        if (!isChild_) {
            // First read the header
            uint8_t header[1 + sizeof(uint64_t)];
            if (ssize_t n = read(fromChildFd_, header, sizeof(header)); n != static_cast<ssize_t>(sizeof(header))) {
                throw std::runtime_error("Emulator::receiveResponseMsg: failed to read header");
            }

            uint64_t payloadSize = 0;
            std::memcpy(&payloadSize, header + 1, sizeof(uint64_t));

            // Allocate full buffer: header + payload
            std::vector<uint8_t> fullMsg(1 + sizeof(uint64_t) + payloadSize);
            std::memcpy(fullMsg.data(), header, sizeof(header));

            // Read payload
            if (read(fromChildFd_, fullMsg.data() + sizeof(header), payloadSize) != static_cast<ssize_t>(payloadSize)) {
                throw std::runtime_error("Emulator::receiveResponseMsg: failed to read payload");
            }

            return IpcResponseMsg::deserialize(fullMsg.data(), fullMsg.size());
        }
        throw std::logic_error("receiveResponseMsg() called from child");
    }

} // namespace Gpu
