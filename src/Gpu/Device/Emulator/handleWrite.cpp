// file: src/Gpu/Device/Emulator/handleWrite.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>
#include <vector>

namespace Gpu {
    void Emulator::handleWrite(const IpcHeader &hdr, const int fromChildFd, const int toChildFd, PointerTracker &allocations) {
        const auto dst = reinterpret_cast<void *>(hdr.ptr);
        if (!allocations.contains(dst)) {
            const IpcResponseMsg failResponse(1, nullptr, 0);
            const std::vector<uint8_t> buffer = failResponse.serialize();
            write(fromChildFd, buffer.data(), buffer.size());
            return;
        }

        std::vector<uint8_t> data(hdr.size);
        if (read(toChildFd, data.data(), hdr.size) != static_cast<ssize_t>(hdr.size)) {
            const IpcResponseMsg failResponse(2, nullptr, 0);
            const std::vector<uint8_t> buffer = failResponse.serialize();
            write(fromChildFd, buffer.data(), buffer.size());
            return;
        }

        std::memcpy(dst, data.data(), hdr.size);

        const IpcResponseMsg response(0, nullptr, 0); // write has no return payload
        const std::vector<uint8_t> buffer = response.serialize();
        write(fromChildFd, buffer.data(), buffer.size());
    }
} // namespace Gpu
