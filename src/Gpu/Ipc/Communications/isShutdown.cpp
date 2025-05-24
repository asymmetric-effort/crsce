// file: src/Gpu/Ipc/Communications/send_Response.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"

namespace Gpu::Ipc {
    [[nodiscard]] bool Communications::isShutdown() const noexcept {
        return shutdownFlag.load();
    };
}
