// file: src/Gpu/Ipc/Result/to_string.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Exceptions/InvalidIpcResult.h"
#include "Gpu/Ipc/Result.h"

const std::string to_string(const Gpu::Ipc::Result& result) {
    switch (result) {
        case Gpu::Ipc::Result::Success: return "Success";
            break;
        case Gpu::Ipc::Result::Closed: return "Closed";
            break;
        case Gpu::Ipc::Result::IOError: return "IOError";
            break;
        case Gpu::Ipc::Result::InvalidRole: return "InvalidRole";
            break;
        default:
            throw Gpu::Exceptions::InvalidIpcResult(result);
    }
}
