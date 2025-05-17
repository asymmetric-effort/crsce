// file: src/Gpu/Device/Emulator_launchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::launchTask(const std::function<void()>&) {
        // For now, no-op: tasks execution inside child occurs via commands
        return true;
    }

} // namespace Gpu
