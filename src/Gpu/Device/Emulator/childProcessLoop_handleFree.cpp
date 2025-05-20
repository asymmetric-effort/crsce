// file: src/Gpu/Device/childProcessLoop_handleFree.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    namespace Cpl {
        void handleFree(const IpcHeader& hdr, Gpu::PointerTracker& allocations) {
            void* ptr = reinterpret_cast<void*>(hdr.ptr);
            auto it = allocations.find(ptr);
            if (it != allocations.end()) {
                std::free(ptr);
                allocations.erase(it);
            }
        }

    } // namespace Cpl

} // namespace Gpu
