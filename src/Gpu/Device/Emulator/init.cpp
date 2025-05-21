// file: src/Gpu/Device/Emulator/init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdexcept>
#include <iostream>

namespace Gpu::Device {

    bool Emulator::init() {
        if (initialized_) {
            return true;
        }

        pid_t forkResult = fork();
        if (forkResult < 0) {
            std::cerr << "[Emulator::init] fork() failed\n";
            return false;
        }

        childPid_ = forkResult;
        try {
            comm_ = std::make_unique<Ipc::Communications>(childPid_);
        } catch (const std::exception& e) {
            std::cerr << "[Emulator::init] Communications setup failed: " << e.what() << "\n";
            return false;
        }

        initialized_ = true;
        return true;
    }

} // namespace Gpu::Device
