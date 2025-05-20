// file: include/Gpu/Device/CommandType.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>
#include <sys/types.h>

namespace Gpu {

    //IpcCommand Message Types we send to a GPU
    enum class CommandType : uint32_t {
        Alloc       = 1,
        Free        = 2,
        Write       = 3,
        Read        = 4,
        LaunchTask  = 5,
        Reset       = 6,
        Wait        = 7,
        Shutdown    = 8
    };

}; //namespace Gpu
