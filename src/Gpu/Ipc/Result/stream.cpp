// file: src/Gpu/Ipc/Result/stream.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Result.h"
#include <ostream>

namespace Gpu::Ipc {

    std::ostream& operator<<(std::ostream& os, const Result r) {
        return os << resultToString(r);
    }

} // namespace Gpu::Ipc
