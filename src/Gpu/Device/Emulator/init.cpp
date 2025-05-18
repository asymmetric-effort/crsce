// file: src/Gpu/Device/init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/Kernel.h"
#include "Gpu/common/KernelRegistry.h"
#include "Gpu/Kernels/IncrementKernel.h"

namespace Gpu {

    bool Emulator::init() {
        // Register built-in kernels for this backend
        KernelRegistry::instance().registerKernel(KernelId::Increment,new IncrementKernel());
        // ToDo: Add more registration steps here.

        // Existing init logic: fork child, set up IPC, etc.
        int pipeToChild[2], pipeFromChild[2];
        if (pipe(pipeToChild) < 0 || pipe(pipeFromChild) < 0) {
            std::perror("[Emulator] pipe creation failed");
            return false;
        }
        pid_t pid = fork();
        if (pid < 0) {
            std::perror("[Emulator] fork failed in init");
            return false;
        }
        if (pid > 0) {
            // Parent setup
            close(pipeToChild[0]);
            close(pipeFromChild[1]);
            toChildFd_   = pipeToChild[1];
            fromChildFd_ = pipeFromChild[0];
            emulatorPid_ = pid;
            isChild_     = false;
            return true;
        }
        // Child setup
        close(pipeToChild[1]);
        close(pipeFromChild[0]);
        toChildFd_   = pipeToChild[0];
        fromChildFd_ = pipeFromChild[1];
        isChild_     = true;
        std::cout << "[Emulator] Child process started.\n";
        childProcessLoop();
        _exit(EXIT_SUCCESS);
    }

} // namespace Gpu
