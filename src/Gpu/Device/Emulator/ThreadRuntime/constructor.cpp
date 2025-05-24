// file: src/Gpu/ThreadRuntime/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/ThreadRuntime.h"

namespace Gpu::Device {

    ThreadRuntime::ThreadRuntime(const Common::Buffer8& kernelBlob, const Common::Buffer8& args)
        : kernel_(kernelBlob), args_(args) {}

}
