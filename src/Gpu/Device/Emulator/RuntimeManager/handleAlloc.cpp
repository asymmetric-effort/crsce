/**
 * @file src/Gpu/RuntimeManager/handleAlloc.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name handleAlloc
     * @class RuntimeManager
     * @public
     * @brief Handle an allocation request from IPC Message.
     * @param msg IPC message containing allocation parameters.
     * @return Response indicating success or failure and any metadata.
     */
    Ipc::Response RuntimeManager::handleAlloc(const Ipc::Message& msg) {
        const auto ptr = memory_.alloc(static_cast<std::size_t>(msg.size));

        Ipc::Response res;

        res.status = (ptr != 0) ? Ipc::FailureCodes::Success : Ipc::FailureCodes::AllocationFailed;

        res.size = sizeof(Common::AbstractPtr);

        res.data.resize(sizeof(Common::AbstractPtr));

        for (int i = 0; i < 8; ++i)
            res.data[i] = static_cast<uint8_t>((ptr >> (i * 8)) & 0xFF);

        return res;

    }

}
