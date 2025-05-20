// file: src/Gpu/Device/Emulator/handleLaunchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include "Gpu/common/KernelRegistry.h"
#include <unistd.h>

namespace Gpu {

    void Emulator::handleLaunchTask(const IpcHeader& hdr, const int fromChildFd, const PointerTracker& allocations) {
        const auto buffer = reinterpret_cast<void*>(hdr.ptr);

        // Validate pointer
        if (!allocations.contains(buffer)) {
            const IpcResponseMsg failResponse(1, nullptr, 0);
            const auto buf = failResponse.serialize();
            write(fromChildFd, buf.data(), buf.size());
            return;
        }

        // Validate kernel
        const auto kernel = KernelRegistry::instance().get(static_cast<KernelId>(hdr.kernelId));
        if (!kernel || hdr.size == 0) {
            const IpcResponseMsg failResponse(2, nullptr, 0);
            const auto buf = failResponse.serialize();
            write(fromChildFd, buf.data(), buf.size());
            return;
        }

        // Execute kernel
        kernel->run(buffer, hdr.size);

        const IpcResponseMsg response(0, nullptr, 0);  // success, no payload
        const auto buf = response.serialize();
        write(fromChildFd, buf.data(), buf.size());
    }

} // namespace Gpu
