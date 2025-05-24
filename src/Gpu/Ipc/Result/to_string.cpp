// file: src/Gpu/Ipc/Result/to_string.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Exceptions/InvalidIpcResult.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Ipc {
    std::string to_string(const Gpu::Ipc::Result result) {
        switch (result) {
            case Gpu::Ipc::Result::Success: return "Success";
            case Gpu::Ipc::Result::Closed: return "Closed";
            case Gpu::Ipc::Result::IOError: return "IOError";
            case Gpu::Ipc::Result::InvalidRole: return "InvalidRole";
            default:
                throw Gpu::Exceptions::InvalidIpcResult(result);
        }
    }
}
