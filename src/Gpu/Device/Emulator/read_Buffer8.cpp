/**
 * @file src/Gpu/Device/Emulator/read_Buffer8.cpp
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
     * @name read
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Read data from GPU memory into an 8-bit buffer.
     * @param source Abstract pointer to GPU memory source.
     * @param dst Data buffer to be populated with read bytes.
     * @return true if read succeeded, false otherwise.
     */
    bool Emulator::read(Common::Buffer8& source, Common::AbstractPtr& dst) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::read(Buffer8) called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Read;
        msg.ptr = dst;
        msg.size = source.size();

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed(result);
        }

        Ipc::Response res;
        if (const auto result = ipc_->recv(res); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcRecvFailed(result);
        }

        if (res.status != Ipc::FailureCodes::Success || res.size != source.size())
            return false;

        source = res.data;
        return true;
    }

}
