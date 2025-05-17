// file: include/Gpu/Device/IpcHeader.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>
#include <sys/types.h>

namespace Gpu {

#pragma pack(push,1)
    struct IpcHeader {
        CommandType type;
        uint32_t    kernelId;
        uint64_t    size;
        uint64_t    ptr;
    };
#pragma pack(pop)

}; //namespace Gpu
