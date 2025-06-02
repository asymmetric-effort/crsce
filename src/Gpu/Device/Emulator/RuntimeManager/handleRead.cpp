/**
 * @file src/Gpu/RuntimeManager/handleRead.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name handleRead
     * @class RuntimeManager
     * @public
     * @brief Handle a read request from IPC.
     * @param msg IPC message specifying source address and size.
     * @return Response containing requested data or error code.
     */
    Ipc::Response RuntimeManager::handleRead(const Ipc::Message& msg) const {
        Common::Buffer8 buffer(msg.size);
        const bool ok = memory_.read(msg.ptr, buffer);
        return {
            ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::ReadError,
            ok ? static_cast<uint64_t>(buffer.size()) : 0,
            ok ? std::move(buffer) : Common::Buffer8{}
        };
    }

}
