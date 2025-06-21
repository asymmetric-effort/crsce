/**
 * @file src/Gpu/Device/Emulator/init.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Device/Emulator/MockGpu.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Gpu/Ipc/Handles.h"

namespace Gpu::Device {

    bool Emulator::init() {
        if (shutdown_) throw Gpu::Exceptions::DeviceNotReady("init() after shutdown");
        if (initialized_) return true;


        Ipc::Handles ptc{-1, -1};
        Ipc::Handles ctp{-1, -1};

        if (pipe(ptc.data()) < 0 || pipe(ctp.data()) < 0) return false;

        const pid_t pid = fork();
        if (pid < 0) return false;

        if (pid == 0) {
            // Child process
            close(ptc[1]); close(ctp[0]);
            Ipc::Communications comm{ptc, ctp, false};
            MockGpu gpu{comm};
            gpu.run();
            _exit(0);
        }

        // Parent process
        close(ptc[0]); close(ctp[1]);
        ipc_ = std::make_unique<Ipc::Communications>(ptc, ctp, true);
        childPid_ = pid;
        initialized_ = true;
        return true;
    }

}
