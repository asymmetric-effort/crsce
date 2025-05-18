// file: src/Gpu/Gpu_create.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Interface.h"

namespace Gpu {

    std::unique_ptr<Interface> Interface::create() {

        std::cout << "[Interface] Gpu::Interface::create()." << std::endl;

        return std::make_unique<Emulator>();

    }

} // namespace Gpu
