// file: src/Gpu/Device/Emulator/handleAlloc.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>

namespace Gpu {

    void Emulator::handleAlloc(const IpcHeader& hdr, int fromChildFd, PointerTracker& allocations) {
        void* ptr = std::malloc(hdr.size);
        if (ptr) allocations.insert(ptr);

        const IpcResponseMsg response(0, &ptr, sizeof(ptr));
        const std::vector<uint8_t> buffer = response.serialize();
        write(fromChildFd, buffer.data(), buffer.size());
    }

} // namespace Gpu
