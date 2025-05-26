/**
 * @file src/Gpu/Device/Emulator/MockGpu/run.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/MockGpu.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"

namespace Gpu::Device {

    void MockGpu::run() {
        while (!runtime_.isShutdown()) {
            Ipc::Message msg;
            if (ipc_.recv(msg) != Ipc::Result::Success)
                continue;

            Ipc::Response res;
            switch (msg.type) {
                case Ipc::CommandType::Alloc:
                    res = runtime_.handleAlloc(msg);
                    break;
                case Ipc::CommandType::Free:
                    res = runtime_.handleFree(msg);
                    break;
                case Ipc::CommandType::Write: {
                    Ipc::Response err = { Ipc::FailureCodes::WriteError, 0, {} };
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case Ipc::CommandType::Read:
                    res = runtime_.handleRead(msg);
                    break;
                case Ipc::CommandType::RegisterKernel: {
                    Ipc::Response err = { Ipc::FailureCodes::KernelNotFound, 0, {} };
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case Ipc::CommandType::LaunchTask: {
                    Ipc::Response err = { Ipc::FailureCodes::ThreadLaunchFailure, 0, {} };
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case Ipc::CommandType::Reset:
                    res = runtime_.handleReset();
                    break;
                case Ipc::CommandType::Shutdown:
                    res = runtime_.handleShutdown();
                    break;
                default:
                    res = { Ipc::FailureCodes::UnknownError, 0, {} };
                    break;
            }
            ipc_.send(res);
        }
    }

}
