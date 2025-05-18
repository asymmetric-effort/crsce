// file: src/Gpu/Device/Emulator_childProcessLoop.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/KernelRegistry.h"
#include "Gpu/common/CommandType.h"
#include "Gpu/common/KernelId.h"
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

namespace Gpu {

void Emulator::childProcessLoop() {
    while (true) {
        IpcHeader hdr;
        ssize_t n = read(toChildFd_, &hdr, sizeof(hdr));
        if (n != sizeof(hdr)) break;
        switch (hdr.type) {
            case CommandType::Alloc: {
                void* ptr = std::malloc(hdr.size);
                write(fromChildFd_, &ptr, sizeof(ptr));
                break;
            }
            case CommandType::Free: {
                void* ptr = reinterpret_cast<void*>(hdr.ptr);
                std::free(ptr);
                break;
            }
            case CommandType::Write: {
                void* dst = reinterpret_cast<void*>(hdr.ptr);
                std::vector<char> buf(hdr.size);
                read(toChildFd_, buf.data(), hdr.size);
                std::memcpy(dst, buf.data(), hdr.size);
                break;
            }
            case CommandType::Read: {
                void* src = reinterpret_cast<void*>(hdr.ptr);
                std::vector<char> buf(hdr.size);
                std::memcpy(buf.data(), src, hdr.size);
                write(fromChildFd_, buf.data(), hdr.size);
                break;
            }
            case CommandType::LaunchTask: {
                // Dispatch via registry
                auto kernel = KernelRegistry::instance().get(
                    static_cast<KernelId>(hdr.ptr)
                );
                if (kernel && hdr.size > 0) {
                    void* buffer = reinterpret_cast<void*>(hdr.size);
                    kernel->run(buffer, hdr.ptr);
                }
                break;
            }
            case CommandType::Shutdown:
                return;
            default:
                std::cerr << "[Emulator] Unknown command " << static_cast<int>(hdr.type) << std::endl;
                break;
        }
    }
}

} // namespace Gpu
