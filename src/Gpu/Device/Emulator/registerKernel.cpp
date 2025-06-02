/**
 * @file src/Gpu/Device/Emulator/registerKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/IpcRecvFailed.h"
#include "Gpu/Exceptions/IpcSendFailed.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name registerKernel
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Register a kernel binary blob with the emulator.
     * @param id Unique kernel identifier.
     * @param binary Binary code blob for the kernel.
     * @return true if registration succeeded, false otherwise.
     */
    bool Emulator::registerKernel(const KernelId id, const Common::Buffer8& binary) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::registerKernel() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::RegisterKernel;
        msg.kernelId = static_cast<uint32_t>(id);
        msg.size = binary.size();

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed("Emulator::registerKernel() failed");
        }
        ipc_->send(Ipc::Response{Ipc::FailureCodes::Success, msg.size, binary});

        Ipc::Response res;
        if (const auto result = ipc_->recv(res); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcRecvFailed(result);
        }

        return res.status == Ipc::FailureCodes::Success;
    }

}
