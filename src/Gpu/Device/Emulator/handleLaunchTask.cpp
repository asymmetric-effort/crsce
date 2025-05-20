// file: src/Gpu/Device/childProcessLoop_handleLaunchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {
    void Emulator::handleLaunchTask(const IpcHeader& hdr, int fromChildFd_, PointerTracker& allocations) {
        void* buffer = reinterpret_cast<void*>(hdr.ptr);

        if (allocations.find(buffer) == allocations.end()) {
            std::cerr << "[Emulator] LaunchTask failed: invalid buffer pointer\n";
            char error = 1;
            write(fromChildFd_, &error, 1);
            return;
        }

        auto kernel = KernelRegistry::instance().get(static_cast<KernelId>(hdr.kernelId));
        if (!kernel || hdr.size == 0) {
            std::cerr << "[Emulator] LaunchTask failed: null kernel or zero size\n";
            char error = 1;
            write(fromChildFd_, &error, 1);
            return;
        }

        kernel->run(buffer, hdr.size);
        char success = 0;
        write(fromChildFd_, &success, 1);
    }
} // namespace Gpu
