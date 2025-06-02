/**
 * @file src/Gpu/ThreadRuntime/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRuntime.h"
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name constructor
     * @class ThreadRuntime
     * @brief initialize the class
     * @param kernelBlob Common::Buffer8 - kernel binary blob
     * @param args Common::Buffer8 - serialized binary arguments for binary
     */
    ThreadRuntime::ThreadRuntime(const Common::Buffer8& kernelBlob, const Common::Buffer8& args)
        : kernel_(kernelBlob), args_(args) {}

}
