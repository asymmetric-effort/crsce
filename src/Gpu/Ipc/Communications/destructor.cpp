// file: src/Gpu/Ipc/Communications/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <chrono>
#include <thread>

namespace Gpu::Ipc {

    Communications::~Communications() {
        constexpr int kDrainWaitMillis = 5000;
        constexpr int CloseFd = -1;

        // Signal shutdown to prevent further sends
        shutdownFlag_.store(true, std::memory_order_release);

        // Allow time for communication pipes to drain.
        std::this_thread::sleep_for(std::chrono::milliseconds(kDrainWaitMillis));

        // Close active file descriptors
        if (toChildFd_ != CloseFd) {
            close(toChildFd_);
            toChildFd_ = CloseFd;
        }

        if (fromChildFd_ != CloseFd) {
            close(fromChildFd_);
            fromChildFd_ = CloseFd;
        }

        // Also close the raw pipe ends
        for (int& fd : toChild_) {
            if (fd != CloseFd) {
                close(fd);
                fd = CloseFd;
            }
        }

        for (int& fd : fromChild_) {
            if (fd != CloseFd) {
                close(fd);
                fd = CloseFd;
            }
        }
    }

} // namespace Gpu::Ipc
