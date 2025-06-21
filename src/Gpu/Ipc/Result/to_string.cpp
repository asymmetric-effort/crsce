/**
 * @file src/Gpu/Ipc/Result/to_string.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Exceptions/InvalidIpcResult.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Ipc {
    std::string to_string(const Gpu::Ipc::Result result) {
        switch (result) {
            using enum Result;
            case Success: return "Success";
            case Closed: return "Closed";
            case IOError: return "IOError";
            case InvalidRole: return "InvalidRole";
            default:
                throw Exceptions::InvalidIpcResult(result);
        }
    }
}
