// file: src/Gpu/Device/Emulator/shutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Result.h"

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

namespace Gpu::Device {

    void Emulator::shutdown() {
        if (!initialized_ || !comm_) return;

        // Send shutdown message
        Ipc::Message msg;
        msg.type = 0x09;  // CommandType::Shutdown
        msg.kernelId = 0;
        msg.size = 0;
        msg.ptr = 0;

        const Ipc::Result result = comm_->parentSend(msg);
        if (result != Ipc::Result::Success) {
            std::cerr << "[Emulator::shutdown] Warning: failed to send shutdown message. Result: " << result << "\n";
        }

        // Wait for child to exit
        if (childPid_ > 0) {
            int status = 0;
            waitpid(childPid_, &status, 0);
        }

        comm_.reset();
        initialized_ = false;
        childPid_ = -1;
    }

} // namespace Gpu::Device
