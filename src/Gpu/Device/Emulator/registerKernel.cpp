// file: src/Gpu/Device/Emulator/registerKernel.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Device {

    void Emulator::registerKernel(uint32_t kernelId, const std::vector<uint8_t>& binary) {
        if (!comm_ || !initialized_ || binary.empty()) return;

        Ipc::Message msg;
        msg.type     = 0x10; // Hypothetical: CommandType::RegisterKernel
        msg.kernelId = kernelId;
        msg.size     = static_cast<uint64_t>(binary.size());
        msg.ptr      = 0;

        if (comm_->parentSend(msg) != Ipc::Result::Success) return;
        comm_->parentSend(binary); // we ignore result for now — child should validate
    }

} // namespace Gpu::Device
