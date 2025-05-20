// file: src/Gpu/Device/childProcessLoop_handleWrite.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {
    void Emulator::handleWrite(int toChildFd_, int fromChildFd_, const IpcHeader& hdr, PointerTracker& allocations) {
        void* dst = reinterpret_cast<void*>(hdr.ptr);

        if (allocations.find(dst) == allocations.end()) {
            std::cerr << "[Emulator] WriteBuffer failed: invalid or freed pointer\n";
            char error = 1;
            write(fromChildFd_, &error, 1);
            return;
        }

        std::vector<char> buf(hdr.size);
        read(toChildFd_, buf.data(), hdr.size);
        std::memcpy(dst, buf.data(), hdr.size);
        char success = 0;
        write(fromChildFd_, &success, 1);
    }
} // namespace Gpu
