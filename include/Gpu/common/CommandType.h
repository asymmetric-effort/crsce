// file: include/Gpu/Device/CommandType.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>
#include <sys/types.h>

namespace Gpu {

    //IpcCommand Message Types we send to a GPU
    enum class CommandType : uint32_t {
        Init        = 0x01,
        Alloc       = 0x02,
        Free        = 0x03,
        Write       = 0x04,
        Read        = 0x05,
        LaunchTask  = 0x06,
        Reset       = 0x07,
        Wait        = 0x08,
        Shutdown    = 0x09
    };

}; //namespace Gpu
