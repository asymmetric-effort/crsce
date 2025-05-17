// file: src/Gpu/Device/Emulator_childProcessLoop.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    void Emulator::childProcessLoop() {
        while (true) {
            IpcHeader hdr;
            ssize_t n = read(toChildFd_, &hdr, sizeof(hdr));
            if (n != sizeof(hdr)) break;
            switch (hdr.type) {
                case CommandType::Alloc: {
                    void* ptr = std::malloc(hdr.size);
                    // send back pointer value
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
                case CommandType::Shutdown:
                    return;
                default:
                    break;
            }
        }
    }

} //namespace Gpu
