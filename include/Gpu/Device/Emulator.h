// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Interface.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace Gpu {

    // IPC command types between parent and emulator child
    enum class CommandType : uint32_t {
        Alloc = 1,
        Free,
        Write,
        Read,
        LaunchTask,
        Shutdown
    };

#pragma pack(push,1)
    struct IpcHeader {
        CommandType type;
        uint64_t    size;  // payload size or allocation size
        uint64_t    ptr;   // pointer for Free/Write/Read
    };
#pragma pack(pop)

    class Emulator : public Interface {
    public:
        Emulator();
        virtual ~Emulator();

        bool init() override;
        void* allocBuffer(std::size_t bytes) override;
        bool freeBuffer(void* ptr) override;
        bool writeBuffer(void* dst, const void* src, std::size_t bytes) override;
        bool readBuffer(void* dst, const void* src, std::size_t bytes) override;

        bool sync() override;

    private:
        int     toChildFd_   = -1;       // write commands to child
        int     fromChildFd_ = -1;       // read responses from child
        pid_t   emulatorPid_ = -1;       // PID of emulator process
        bool    isChild_     = false;    // flag for child context

        bool sendCommand(const IpcHeader& hdr, const void* payload = nullptr);
        bool receiveResponse(void* payload, size_t size);
        void childProcessLoop();
    };

} // namespace Gpu
