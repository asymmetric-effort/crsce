// file: src/Gpu/Gpu_create.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Interface.h"
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    std::unique_ptr<Interface> Interface::create() {
        std::cout << "[Interface::create] Gpu::Interface::create()." << std::endl;
        return std::make_unique<Emulator>();
    }

} // namespace Gpu
