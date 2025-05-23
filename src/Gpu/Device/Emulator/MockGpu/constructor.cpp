// file: src/Gpu/Device/Emulator/MockGpu/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/MockGpu.h"

namespace Gpu::Device {

    MockGpu::MockGpu(Ipc::Communications& comm)
        : ipc_(comm), runtime_() {}

}
