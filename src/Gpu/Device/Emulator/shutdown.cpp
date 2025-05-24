// file: src/Gpu/Device/Emulator/shutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <sys/wait.h>
#include <unistd.h>

namespace Gpu::Device {
    void Emulator::shutdown() {
        if (!initialized_) return;

        shutdown_ = true;
        Ipc::Message shutdownMsg;
        shutdownMsg.type = Ipc::CommandType::Shutdown;

        if (const auto result = ipc_->send(shutdownMsg);result != Ipc::Result::Success)
            throw Gpu::Exceptions::IpcSendFailed(result);

        waitpid(childPid_, nullptr, 0);
        ipc_.reset();
        childPid_ = 0;
        initialized_ = false;
    }
}
