// file: src/Gpu/Device/childProcessLoop_handleRead.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    namespace Cpl {

        void handleRead(int fromChildFd_, const IpcHeader& hdr, PointerTracker& allocations) {
            void* src = reinterpret_cast<void*>(hdr.ptr);

            if (allocations.find(src) == allocations.end()) {
                std::cerr << "[Emulator] ReadBuffer failed: invalid or freed pointer\n";
                char error = 1;
                write(fromChildFd_, &error, 1);  // Send failure signal
                return;
            }

            std::vector<char> buf(hdr.size);
            std::memcpy(buf.data(), src, hdr.size);
            char success = 0;
            write(fromChildFd_, &success, 1);            // Send OK signal
            write(fromChildFd_, buf.data(), hdr.size);   // Send data
        }

    } // namespace Cpl

} // namespace Gpu
