// file: src/Gpu/Device/childProcessLoop_handleFree.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {
    void Emulator::handleFree(const IpcHeader& hdr, PointerTracker& allocations) {
        const auto ptr = reinterpret_cast<void*>(hdr.ptr);
        if (const auto it = allocations.find(ptr); it != allocations.end()) {
            std::free(ptr);
            allocations.erase(it);
        }
    }
} // namespace Gpu
