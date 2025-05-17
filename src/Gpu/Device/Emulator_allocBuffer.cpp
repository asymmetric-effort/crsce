// file: src/Gpu/Device/Emulator_allocBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

void* Emulator::allocBuffer(std::size_t bytes) {
    void* ptr = std::malloc(bytes);
    if (!ptr) {
        std::cerr << "[Emulator] allocBuffer failed to allocate " << bytes << " bytes\n";
    }
    return ptr;
}

} // namespace Gpu

