// file: src/Gpu/Device/childProcessLoop_handleLaunchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    namespace Cpl {

        void handleReset(PointerTracker& allocations) {
            for (void* ptr : allocations) {
                std::free(ptr);
            }
            allocations.clear();
            std::cerr << "[Emulator] All GPU buffers freed. Emulator reset.\n";
        }

    } // namespace Cpl

} // namespace Gpu
