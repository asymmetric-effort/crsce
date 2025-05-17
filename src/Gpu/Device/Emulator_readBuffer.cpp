// file: src/Gpu/Device/Emulator_readBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

bool Emulator::readBuffer(void* dst, const void* src, std::size_t bytes) {
    if (!dst || !src) return false;
    std::memcpy(dst, src, bytes);
    return true;
}


} // namespace Gpu
