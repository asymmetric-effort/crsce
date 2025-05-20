// file: src/Gpu/Device/readBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {
    bool Emulator::readBuffer(void *dst, const void *src, std::size_t bytes) {
        const IpcHeader hdr{
            CommandType::Read,
            0, // kernelId unused for Read
            static_cast<uint64_t>(bytes),
            reinterpret_cast<uint64_t>(src)
        };

        if (!sendCommand(hdr)) return false;

        try {
            const IpcResponseMsg msg = receiveResponseMsg();

            if ((msg.status != 0) || (msg.size < bytes)) return false;

            std::memcpy(dst, msg.data.data(), bytes);
            return true;
        } catch (const std::exception &e) {
            // Optional: log e.what() to diagnostics stream
            return false;
        }
    }
} // namespace Gpu
