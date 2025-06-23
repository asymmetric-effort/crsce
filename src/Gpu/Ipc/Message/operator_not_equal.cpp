/**
 * @file src/Gpu/Ipc/Message/operator_not_equal.cpp
 * @brief Test the IPC Message Serialize functionality
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"

namespace Gpu::Ipc
{
    bool operator!=(const Message& a, const Message& b) noexcept
    {
        return a.type() != b.type() ||
            a.kernelId() != b.kernelId() ||
            a.size() != b.size() ||
            a.ptr() != b.ptr();
    }
}
