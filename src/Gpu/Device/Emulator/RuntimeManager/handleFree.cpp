/**
 * @file src/Gpu/RuntimeManager/handleFree.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name handleFree
     * @class RuntimeManager
     * @public
     * @brief Handle a free request from IPC Message.
     * @param msg IPC message specifying which memory to free.
     * @return Response indicating success or failure of deallocation.
     */
    Ipc::Response RuntimeManager::handleFree(const Ipc::Message& msg) {
        const bool ok = memory_.free(msg.ptr);
        return {ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::InvalidPointer, 0, {}};
    }

}
