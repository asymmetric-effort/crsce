// file: include/Gpu/Ipc/Communications.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include "Gpu/Ipc/Result.h"
#include <atomic>
#include <cstdint>
#include <unistd.h>

namespace Gpu::Ipc {

    class IpcMessage;
    class IpcResponse;

    /**
     * @class Communications
     * @brief Manages bidirectional IPC between parent and child processes.
     *
     * This class abstracts communication over Unix pipes between a controller
     * and a GPU emulator subprocess. All communication setup is internal,
     * and methods are access-controlled by comparing the caller's PID to the
     * stored child PID.
     */
    class Communications {
    public:
        /**
         * @brief Constructor.
         * @param childPid The PID returned from fork() in the parent, or 0 in the child.
         */
        explicit Communications(pid_t childPid);

        /**
         * @brief Destructor.
         *
         * Initiates shutdown sequence and blocks further sends. Waits a bounded
         * time to drain in-flight messages before releasing system resources.
         */
        ~Communications();

        Result parentSend(const IpcMessage& msg);
        Result parentRecv(IpcResponse& response);
        Result childSend(const IpcResponse& response);
        Result childRecv(IpcMessage& msg);

    private:

        // Bidirectional pipes: each pipe has [0]=read end, [1]=write end
        // toChild_: parent writes to [1], child reads from [0]
        // fromChild_: child writes to [1], parent reads from [0]
        int toChild_[2] = {-1, -1};     ///< Pipe from parent to child (read/write ends)
        int fromChild_[2] = {-1, -1};   ///< Pipe from child to parent (read/write ends)

        int toChildFd_ = -1;            ///< This process's local write or read FD
        int fromChildFd_ = -1;          ///< This process's local read or write FD

        pid_t parentPid_ = -1;          ///< PID of the parent process
        pid_t childPid_;                ///< PID of the child process (set from fork result)
        bool isParent_;                 ///< True if this instance is running in the parent
        std::atomic<bool> shutdownFlag_{false}; ///< Indicates whether shutdown is active

        bool validateParentAccess() const noexcept;
        bool validateChildAccess() const noexcept;
    };

} // namespace Gpu::Ipc
