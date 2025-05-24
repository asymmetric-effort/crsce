// file: src/Gpu/Ipc/Result/to_string.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Result.h"

const std::string to_string(const Result& result) {
    switch (result) {
        case Success: return "Success";
            break;
        case Closed: return "Closed";
            break;
        case IOError: return "IOError";
            break;
        case InvalidRole: return "InvalidRole";
            break;
        default:
            throw Gpu::Exceptions::InvalidIpcResult(result);
    }
}
