// file: src/Gpu/Device/Emulator/write.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Result.h"

#include <cstring>

namespace Gpu::Device {

    bool Emulator::write(void* ptr, const void* src, const std::size_t size) {
        if (!comm_ || !initialized_ || !tracker_.contains(ptr) || !src || size == 0) {
            return false;
        }

        Ipc::Message msg;
        msg.type     = 0x04; // CommandType::Write
        msg.kernelId = 0;
        msg.size     = static_cast<uint64_t>(size);
        msg.ptr      = reinterpret_cast<uint64_t>(ptr);

        if (comm_->parentSend(msg) != Ipc::Result::Success) {
            return false;
        }

        // Send payload directly after command
        const uint8_t* byteSrc = static_cast<const uint8_t*>(src);
        const std::vector<uint8_t> payload(byteSrc, byteSrc + size);
        return comm_->parentSend(payload) == Ipc::Result::Success;
    }

} // namespace Gpu::Device
