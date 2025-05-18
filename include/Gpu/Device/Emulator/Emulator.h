// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Device/Interface.h"
#include "Gpu/common/IpcHeader.h"
#include "Gpu/common/KernelId.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace Gpu {

    class Emulator : public Interface {
    public:
        Emulator();
        virtual ~Emulator();

        bool init() override;

        void* allocBuffer(std::size_t bytes) override;

        bool freeBuffer(void* ptr) override;

        bool writeBuffer(void* dst, const void* src, std::size_t bytes) override;

        bool readBuffer(void* dst, const void* src, std::size_t bytes) override;

        bool launchKernel(KernelId id, void* buffer, std::size_t count) override;

        /**
         * @brief Block until all previously dispatched commands finish.
         * @see docs/Gpu/Abstract/wait.md
         * @return 0 on success, non-zero error code on failure.
         */
        int wait() override;

        /**
         * @brief Reset the device context, releasing all resources.
         * @see docs/Gpu/Abstract/reset.md for details on cross-backend behavior.
         */
        void reset() override;

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
