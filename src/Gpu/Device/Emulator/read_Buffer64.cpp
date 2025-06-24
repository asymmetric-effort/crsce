// file: src/Gpu/Device/Emulator/read_Buffer64.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <bit>           // for std::bit_cast
#include <array>
#include <algorithm>
#include <cstdint>

namespace Gpu::Device {
    bool Emulator::read(Common::Buffer64& source, Common::AbstractPtr& dst) {
        // Use the byte-based read() to fetch raw bytes
        const size_t byteCount = source.size() * sizeof(uint64_t);
        Common::Buffer8 temp(byteCount);
        if (!read(temp, dst)) {
            return false;
        }

        // Convert each 8-byte chunk into uint64_t via std::bit_cast
        const size_t count = byteCount / sizeof(uint64_t);
        source.resize(count);
        for (size_t i = 0; i < count; ++i) {
            std::array<uint8_t, sizeof(uint64_t)> bytes;
            std::copy(
                temp.data() + i * sizeof(uint64_t),
                temp.data() + (i + 1) * sizeof(uint64_t),
                bytes.begin()
            );
            source[i] = std::bit_cast<uint64_t>(bytes);
        }

        return true;
    }
} // namespace Gpu::Device
