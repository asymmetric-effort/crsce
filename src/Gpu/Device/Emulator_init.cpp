// file: src/Gpu/Device/Emulator_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::init() {
        std::cout <<"[Emulator::init] start";
        int pipeToChild[2], pipeFromChild[2];
        if (pipe(pipeToChild) < 0 || pipe(pipeFromChild) < 0) {
            std::perror("[Emulator::init] pipe creation failed");
            return false;
        }
        pid_t pid = fork();
        if (pid < 0) {
            std::perror("[Emulator::init] fork failed in init");
            return false;
        }
        if (pid > 0) {
            // Parent: setup fds
            close(pipeToChild[0]);
            close(pipeFromChild[1]);
            toChildFd_   = pipeToChild[1];
            fromChildFd_ = pipeFromChild[0];
            emulatorPid_ = pid;
            isChild_ = false;
            std::perror("[Emulator::init] done (return:true");
            return true;
        }
        // Child: setup fds and enter loop
        close(pipeToChild[1]);
        close(pipeFromChild[0]);
        toChildFd_   = pipeToChild[0];
        fromChildFd_ = pipeFromChild[1];
        isChild_ = true;
        std::cout << "[Emulator::init] Child process started.\n";
        childProcessLoop();
        _exit(EXIT_SUCCESS);
        std::cout << "[Emulator::init] Child process done.\n";

    }

} // namespace Gpu
