// file: src/Gpu/Interface_create.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Interface.h"
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    std::unique_ptr<Interface> Interface::create() {
        return std::make_unique<Emulator>();
    }

} // namespace Gpu
