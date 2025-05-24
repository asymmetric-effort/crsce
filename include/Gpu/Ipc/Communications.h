// file: include/Gpu/Ipc/Communications.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <atomic>
#include <unistd.h>
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Ipc {

    /**
     * @name Gpu::Ipc::Communications
     * @brief Encapsulates bidirectional pipe communication between parent and child processes.
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     */
    class Communications {
    public:
        Communications(int parentToChild[2], int childToParent[2], bool isParentProcess);
        ~Communications();

        Result send(const Message& msg) const;
        Result send(const Response& res);

        Result recv(Message& msg) const;
        Result recv(Response& res);

        bool validateParentAccess() const;
        bool validateChildAccess() const;

        std::atomic<bool> shutdownFlag = false;

    private:
        int parentToChildFd[2];
        int childToParentFd[2];
        bool isParent = true;
    };

} // namespace Gpu::Ipc
