// file: src/Gpu/Device/childProcessLoop.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void Emulator::childProcessLoop() {
        while (true) {
            IpcHeader hdr;
            if (const ssize_t n = read(toChildFd_, &hdr, sizeof(hdr)); n != sizeof(hdr))
                break;

            switch (hdr.type) {
                case CommandType::Init:
                    handleInit(fromChildFd_);
                    break;
                case CommandType::Alloc:
                    handleAlloc(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::Free:
                    handleFree(hdr, allocations_);
                    break;
                case CommandType::Write:
                    handleWrite(hdr, fromChildFd_, toChildFd_, allocations_);
                    break;
                case CommandType::Read:
                    handleRead(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::LaunchTask:
                    handleLaunchTask(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::Wait:
                    handleWait(fromChildFd_);
                    break;
                case CommandType::Reset:
                    handleReset(allocations_);
                    break;
                case CommandType::Shutdown:
                    handleReset(allocations_);
                    return;
                default:
                    break;
            }
        }
    }

} // namespace Gpu
