// file: src/Gpu/Device/init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/Kernel.h"
#include "Gpu/common/KernelRegistry.h"
#include "Gpu/Kernels/IncrementKernel.h"

namespace Gpu {


    bool Emulator::init() {
        // Register built-in kernels for this backend
        KernelRegistry::instance().registerKernel(KernelId::Increment, new IncrementKernel());

        int pipeToChild[2], pipeFromChild[2];

        if (pipe(pipeToChild) < 0) {
            return false;
        }

        if (pipe(pipeFromChild) < 0) {
            close(pipeToChild[0]);
            close(pipeToChild[1]);
            return false;
        }

        const pid_t pid = fork();
        if (pid < 0) {
            close(pipeToChild[0]); close(pipeToChild[1]);
            close(pipeFromChild[0]); close(pipeFromChild[1]);
            return false;
        }

        if (pid > 0) {
            // Parent process setup
            close(pipeToChild[0]);
            close(pipeFromChild[1]);
            toChildFd_   = pipeToChild[1];
            fromChildFd_ = pipeFromChild[0];
            emulatorPid_ = pid;
            isChild_     = false;
            childActive_ = true;

            IpcHeader initHdr{
                .type     = CommandType::Init,
                .kernelId = 0,
                .size     = 0,
                .ptr      = 0
            };

            if (!sendCommand(initHdr)) {
                return false;
            }

            try {
                const IpcResponseMsg msg = receiveResponseMsg();
                if (msg.status != 0) return false;
            } catch (...) {
                return false;
            }

            return true;
        }

        // Child process setup
        close(pipeToChild[1]);
        close(pipeFromChild[0]);

        toChildFd_   = pipeToChild[0];
        fromChildFd_ = pipeFromChild[1];
        isChild_     = true;
        childActive_ = true;

        childProcessLoop();
        _exit(EXIT_SUCCESS);
    }

} // namespace Gpu
