// file: src/Gpu/Device/Emulator/free.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Device {

    void Emulator::free(void* ptr) {
        if (!comm_ || !initialized_ || !tracker_.contains(ptr)) return;

        Ipc::Message msg;
        msg.type     = 0x03; // CommandType::Free
        msg.kernelId = 0;
        msg.size     = 0;
        msg.ptr      = reinterpret_cast<uint64_t>(ptr);

        if (comm_->parentSend(msg) == Ipc::Result::Success) {
            tracker_.erase(ptr);
        }
    }

} // namespace Gpu::Device
