// file: src/Gpu/Device/Emulator/init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Device/Emulator/MockGpu.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace Gpu::Device {

    bool Emulator::init() {
        if (initialized_) return false;

        int ptc[2], ctp[2];
        if (pipe(ptc) < 0 || pipe(ctp) < 0) return false;

        pid_t pid = fork();
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
