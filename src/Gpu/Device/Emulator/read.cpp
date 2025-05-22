// file: src/Gpu/Device/Emulator/read.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

#include <cstring>

namespace Gpu::Device {

    bool Emulator::read(void *dst, void *const ptr, const std::size_t size) const {
        if (!comm_ || !initialized_ || !tracker_.contains(ptr) || !dst || size == 0) {
            return false;
        }

        Ipc::Message msg;
        msg.type     = 0x05; // CommandType::Read
        msg.kernelId = 0;
        msg.size     = static_cast<uint64_t>(size);
        msg.ptr      = reinterpret_cast<uint64_t>(ptr);

        if (comm_->parentSend(msg) != Ipc::Result::Success) {
            return false;
        }

        Ipc::Response resp;
        if (comm_->parentRecv(resp) != Ipc::Result::Success) {
            return false;
        }

        if (resp.status != 0 || resp.size != size || resp.data.size() != size) {
            return false;
        }

        std::memcpy(dst, resp.data.data(), size);
        return true;
    }

} // namespace Gpu::Device
