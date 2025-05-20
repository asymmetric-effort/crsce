// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/common/KernelRegistry.h"
#include "Gpu/common/PointerTracker.h"
#include "Gpu/common/CommandType.h"
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
#include <unordered_set>
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

        void shutdown() override;

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
        bool    childActive_ = false;

        Gpu::PointerTracker allocations_;

        bool sendCommand(const IpcHeader& hdr, const void* payload = nullptr);
        bool receiveResponse(void* payload, size_t size);
        void childProcessLoop();

        // start: methods used by childProcessLoop
        static void handleAlloc(const IpcHeader& hdr, int fromChildFd, PointerTracker& allocations);
        static void handleFree(const IpcHeader& hdr, PointerTracker& allocations);
        static void handleWrite(int toChildFd_, int fromChildFd_, const IpcHeader& hdr, PointerTracker& allocations);
        static void handleRead(int fromChildFd_, const IpcHeader& hdr, PointerTracker& allocations);
        static void handleLaunchTask(const IpcHeader& hdr, int fromChildFd_, PointerTracker& allocations);
        static void handleWait(int fromChildFd_);
        static void handleReset(PointerTracker& allocations);
        // end: methods used by childProcessLoop


    }; // class Emulator

} // namespace Gpu
