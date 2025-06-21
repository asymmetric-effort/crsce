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
                    using enum Ipc::CommandType;
                case Alloc:
                    res = runtime_.handleAlloc(msg);
                    break;
                case Free:
                    res = runtime_.handleFree(msg);
                    break;
                case Write: {
                    Ipc::Response err = {Ipc::FailureCodes::WriteError, 0, {}};
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case Read:
                    res = runtime_.handleRead(msg);
                    break;
                case RegisterKernel: {
                    Ipc::Response err = {Ipc::FailureCodes::KernelNotFound, 0, {}};
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case LaunchTask: {
                    Ipc::Response err = {Ipc::FailureCodes::ThreadLaunchFailure, 0, {}};
                    // Error: missing payload delivery mechanism.
                    res = err;
                    break;
                }
                case Reset:
                    res = runtime_.handleReset();
                    break;
                case Shutdown:
                    res = runtime_.handleShutdown();
                    break;
                default:
                    res = {Ipc::FailureCodes::UnknownError, 0, {}};
                    break;
            }
            if (Gpu::Ipc::Result result = ipc_.send(res); result != Ipc::Result::Success) {
                throw std::runtime_error("IPC send() failed with result: " + to_string(result));
            }
        }
    }
}
