// file: src/Gpu/Device/childProcessLoop.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void Emulator::childProcessLoop() {

        while (true) {
            IpcHeader hdr;
            ssize_t n = read(toChildFd_, &hdr, sizeof(hdr));
            if (n != sizeof(hdr)) break;

            switch (hdr.type) {
                case CommandType::Alloc:
                    Cpl::handleAlloc(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::Free:
                    Cpl::handleFree(hdr, allocations_);
                    break;
                case CommandType::Write:
                    Cpl::handleWrite(toChildFd_, fromChildFd_, hdr, allocations_);
                    break;
                case CommandType::Read:
                    Cpl::handleRead(fromChildFd_, hdr, allocations_);
                    break;
                case CommandType::LaunchTask:
                    Cpl::handleLaunchTask(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::Wait:
                    Cpl::handleWait(fromChildFd_);
                    break;
                case CommandType::Reset:
                    Cpl::handleReset(allocations_);
                    break;
                case CommandType::Shutdown:
                    Cpl::handleReset(allocations_);
                    std::cerr << "[Emulator] Shutdown received. Exiting.\n";
                    return;
                default:
                    std::cerr << "[Emulator] Unknown command " << static_cast<int>(hdr.type) << std::endl;
                    break;
            }
        }
    }

} // namespace Gpu
