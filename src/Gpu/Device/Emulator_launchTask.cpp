// file: src/Gpu/Device/Emulator_launchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

bool Emulator::launchTask(const std::function<void()>& task) {
    pid_t pid = fork();
    if (pid < 0) {
        std::perror("[Emulator] fork failed");
        return false;
    }
    if (pid == 0) {
        // Child process: execute task and exit
        task();
        _exit(EXIT_SUCCESS);
    }
    // Parent process: record child PID
    childPids_.push_back(pid);
    return true;
}

} // namespace Gpu
