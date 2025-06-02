/**
 * @file src/Gpu/Device/Emulator/MockGpu/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/MockGpu.h"
/**
 * @namespace Gpu::Device
 */
namespace Gpu::Device {
    /**
     * @name constructor
     * @class MockGpu
     * @public
     * @brief initialize the mock GPU child process
     * @param comm - IPC Communication channel
     */
    MockGpu::MockGpu(Ipc::Communications &comm) : ipc_(comm), runtime_() {
    }
}
