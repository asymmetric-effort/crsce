// file: src/Gpu/Device/Emulator/handleRead.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>

namespace Gpu {

    void Emulator::handleRead(const IpcHeader& hdr, const int fromChildFd, const PointerTracker& allocations) {
        const auto src = reinterpret_cast<void*>(hdr.ptr);
        if (!allocations.contains(src)) {
            const IpcResponseMsg failResponse(1, nullptr, 0);
            const std::vector<uint8_t> buffer = failResponse.serialize();
            write(fromChildFd, buffer.data(), buffer.size());
            return;
        }

        const IpcResponseMsg response(0, src, hdr.size);
        const std::vector<uint8_t> buffer = response.serialize();
        write(fromChildFd, buffer.data(), buffer.size());
    }

} // namespace Gpu
