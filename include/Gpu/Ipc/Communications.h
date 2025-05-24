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
        /**
         * @name constructor
         * @brief class constructor enumerates two p2c and two c2p file descriptors.
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         * @param parentToChild
         * @param childToParent
         * @param isParentProcess
         */
        Communications(int parentToChild[2], int childToParent[2], bool isParentProcess);

        /**
         * @name destructor
         * @brief class destructor
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        ~Communications();

        /**
         * @name send (Message)
         * @brief send IPC Message from parent to child
         * @param msg
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result send(const Message& msg) const;

        /**
         * @name send (Response)
         * @brief send IPC Response from child to parent
         * @param res
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result send(const Response& res) const;

        /**
         * @name recv (Message)
         * @brief recv IPC Message from parent
         * @param msg
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result recv(Message& msg) const;

        /**
         * @name recv (Response)
         * @brief recv IPC Response from parent
         * @param res
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result recv(Response& res) const;

        /**
         * @name validateParentAccess
         * @brief validate the parent can send
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        bool validateParentAccess() const;

        /**
         * @name validateChildAccess
         * @brief validate the child can send
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        bool validateChildAccess() const;

        /**
         * @name isShutdown
         * @brief return whether or not the class instance is in shutdown
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         * @return
         */
        [[nodiscard]] bool isShutdown() const noexcept ;

        //Constants to use in read/write fd indexes
        static constexpr int readEndpoint=0;
        static constexpr int writeEndpoint=1;

    private:
        int parentToChildFd[2];
        int childToParentFd[2];
        bool isParent = true;
        std::atomic<bool> shutdownFlag = false;
    };

} // namespace Gpu::Ipc
