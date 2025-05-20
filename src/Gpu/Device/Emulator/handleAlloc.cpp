// file: src/Gpu/Device/childProcessLoop_handleAlloc.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {
    void Emulator::handleAlloc(const IpcHeader& hdr, const int fromChildFd, PointerTracker& allocations) {
        void* ptr = std::malloc(hdr.size);
        if (ptr) allocations.insert(ptr);
        write(fromChildFd, &ptr, sizeof(ptr));  // Must send back pointer
    }
} // namespace Gpu
