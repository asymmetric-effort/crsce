// file: src/Gpu/Gpu_create.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Interface.h"
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    std::unique_ptr<Interface> Gpu::create() {
#ifdef GPU_EMULATOR
        return std::make_unique<Emulator::Mock::Emulator>();
#else
        // TODO: return real GPU implementation when available
        return nullptr;
#endif
    }

} // namespace Gpu
