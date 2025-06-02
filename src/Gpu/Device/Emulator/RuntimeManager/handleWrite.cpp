/**
 * @file src/Gpu/RuntimeManager/handleWrite.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name handleWrite
     * @class RuntimeManager
     * @public
     * @brief Handle a write request with payload.
     * @param msg IPC message specifying destination address and size.
     * @param payload Buffer containing data to write.
     * @return Response indicating success or failure of write operation.
     */
    Ipc::Response RuntimeManager::handleWrite(const Ipc::Message& msg, const Common::Buffer8& payload) {
        const bool ok = memory_.write(msg.ptr, payload);
        return {ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::WriteError, 0, {}};
    }

}
