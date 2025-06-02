/**
 * @file src/Gpu/Device/Emulator/write_Buffer8.cpp
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
     * @name write
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Write an 8-bit buffer to GPU memory.
     * @param source Data buffer to write.
     * @param dst Abstract pointer to destination GPU memory.
     * @return true if write succeeded, false otherwise.
     */
    bool Emulator::write(const Common::Buffer8 &source, Common::AbstractPtr &dst) {
        if (!initialized_)
            throw Exceptions::DeviceNotReady("Emulator::write(Buffer8) called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Write;
        msg.ptr = dst;
        msg.size = source.size();

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed(result);
        }

        // Payload trick
        if (const auto result = ipc_->send(Ipc::Response{Ipc::FailureCodes::Success, msg.size, source}); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed(result);
        }

        Ipc::Response res;
        if (const auto result = ipc_->recv(res); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcRecvFailed(result);
        }

        return res.status == Ipc::FailureCodes::Success;
    }

}
