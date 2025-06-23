/**
 * @file src/Gpu/ThreadRuntime/run.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRuntime.h"
#include <stdexcept>

#include "Gpu/Exceptions/InvalidKernelBlob.h"

namespace Gpu::Device {

    void ThreadRuntime::run() const {
        if (kernel_.size() < 16) {
            throw Exceptions::InvalidKernelBlob("Kernel name must not be empty");
        }

        // Placeholder: validate header, dispatch fake instruction execution
        if (const uint8_t magic = kernel_[0]; magic != 0xB1) {
            throw Exceptions::InvalidKernelBlob("Kernel name must not be empty");
        }

        // Actual kernel interpretation would be implemented here.
        // This is a stub to allow thread lifecycle and IPC testing.
    }

}
