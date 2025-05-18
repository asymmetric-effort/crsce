// file: src/Gpu/Device/launchKernel.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/KernelId.h"

namespace Gpu {

    bool Emulator::launchKernel(KernelId id, void* buffer, std::size_t count) {
        if (isChild_) return false;
        IpcHeader hdr{
            CommandType::LaunchTask,
            static_cast<uint32_t>(id),         // kernelId
            static_cast<uint64_t>(count),      // size = element count
            reinterpret_cast<uint64_t>(buffer) // ptr = device address
        };
        return sendCommand(hdr);
    }

} // namespace Gpu
