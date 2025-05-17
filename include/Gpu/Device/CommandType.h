// file: include/Gpu/Device/CommandType.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>
#include <sys/types.h>

namespace Gpu {

    enum class CommandType : uint32_t {
        Alloc       = 1,
        Free        = 2,
        Write       = 3,
        Read        = 4,
        LaunchTask  = 5, // IPC-driven kernel dispatch
        Shutdown    = 6
    };

}; //namespace Gpu
