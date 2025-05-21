// file: src/Gpu/Device/Emulator/alloc.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

#include <cstring>

namespace Gpu::Device {

    void* Emulator::alloc(const std::size_t bytes) {
        if (!comm_ || !initialized_) return nullptr;

        Ipc::Message msg;
        msg.type     = 0x02; // CommandType::Alloc
        msg.kernelId = 0;
        msg.size     = static_cast<uint64_t>(bytes);
        msg.ptr      = 0;

        if (comm_->parentSend(msg) != Ipc::Result::Success) {
            return nullptr;
        }

        Ipc::Response resp;
        if (comm_->parentRecv(resp) != Ipc::Result::Success) {
            return nullptr;
        }

        if (resp.status != 0 || resp.size != sizeof(uint64_t) || resp.data.size() != sizeof(uint64_t)) {
            return nullptr;
        }

        uint64_t raw = 0;
        std::memcpy(&raw, resp.data.data(), sizeof(uint64_t));
        void* ptr = reinterpret_cast<void*>(raw);

        tracker_.insert(ptr);
        return ptr;
    }

} // namespace Gpu::Device
