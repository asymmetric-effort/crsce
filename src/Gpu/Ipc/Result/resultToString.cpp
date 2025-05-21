// file: src/Gpu/Ipc/Result/resultToString.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Result.h"

namespace Gpu::Ipc {

    std::string resultToString(const Result r) {
        switch (r) {
            case Result::Success:  return "Success";
            case Result::Empty:    return "Empty";
            case Result::Blocked:  return "Blocked";
            case Result::Shutdown: return "Shutdown";
            case Result::Error:    return "Error";
            default:               return "Unknown";
        }
    }

} // namespace Gpu::Ipc
