/**
 * @file src/Gpu/Device/Emulator/shutdown.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/IpcSendFailed.h"
#include <sys/wait.h>
#include <unistd.h>

namespace Gpu::Device {
    void Emulator::shutdown() {
        if (!initialized_) return;

        if (shutdown_) return;

        shutdown_ = true;

        Ipc::Message shutdownMsg;

        shutdownMsg.type(Ipc::MessageType::Shutdown);

        if (const auto result = ipc_->send(shutdownMsg); result != Ipc::Result::Success)
            throw Gpu::Exceptions::IpcSendFailed(result);

        waitpid(childPid_, nullptr, 0);

        ipc_.reset();

        childPid_ = 0;

        initialized_ = false;
    }
}
