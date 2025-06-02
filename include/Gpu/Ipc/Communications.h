/**
 * @file include/Gpu/Ipc/Communications.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <atomic>
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::Communications
     * @brief Encapsulates bidirectional pipe communication between parent and child processes.
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     */
    class Communications {
    public:
        /**
         * @property readEndpoint
         * @class Communications
         * @public
         * @brief constant used in read/write fd indexes
         */
        static constexpr int readEndpoint = 0;
        /**
         * @property writeEndpoint
         * @class Communications
         * @public
         * @brief constant used in read/write fd indexes
         */
        static constexpr int writeEndpoint = 1;
        /**
         * @property ipcPipeFdSz
         * @class Communications
         * @public
         * @brief constant ipc pipe file handle array size
         */
        static constexpr int ipcPipeFdSz = 2;

        /**
         * @name constructor
         * @class Communications
         * @public
         * @brief class constructor enumerates two p2c and two c2p file descriptors.
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         * @param parentToChild int file handle array
         * @param childToParent int file handle array
         * @param isParentProcess bool
         */
        Communications(const int parentToChild[ipcPipeFdSz], const int childToParent[ipcPipeFdSz],
                       const bool isParentProcess);

        /**
         * @name destructor
         * @class Communications
         * @public
         * @brief class destructor
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        ~Communications();

        /**
         * @name send (Message)
         * @class Communications
         * @public
         * @brief send IPC Message from parent to child
         * @param msg
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result send(const Message &msg) const;

        /**
         * @name send (Response)
         * @class Communications
         * @public
         * @brief send IPC Response from child to parent
         * @param res
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result send(const Response &res) const;

        /**
         * @name recv (Message)
         * @class Communications
         * @public
         * @brief recv IPC Message from parent
         * @param msg
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result recv(Message &msg) const;

        /**
         * @name recv (Response)
         * @class Communications
         * @public
         * @brief recv IPC Response from parent
         * @param res
         * @return Gpu::Ipc::Result
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        Result recv(Response &res) const;

        /**
         * @name validateParentAccess
         * @class Communications
         * @public
         * @brief validate the parent can send
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        bool validateParentAccess() const;

        /**
         * @name validateChildAccess
         * @class Communications
         * @public
         * @brief validate the child can send
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        bool validateChildAccess() const;

        /**
         * @name isShutdown
         * @class Communications
         * @public
         * @brief return whether or not the class instance is in shutdown
         * @return bool
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         * @return
         */
        [[nodiscard]] bool isShutdown() const noexcept;

    private:
        /**
         * @property parentToChildFd
         * @private
         * @brief array of parent to child Ipc pipe file descriptors
         */
        int parentToChildFd[ipcPipeFdSz];
        /**
         * @property childToParentFd
         * @private
         * @brief array of child to parent Ipc pipe file descriptors
         */
        int childToParentFd[ipcPipeFdSz];
        /**
         * @property isParent
         * @private
         * @brief boolean flag indicating whether process is the parent PID
         */
        bool isParent = true;
        /**
         * @property shutdownFlag
         * @private
         * @brief atomic boolean flag to indicate whether shutdown is in progress.
         */
        std::atomic<bool> shutdownFlag = false;
    };
} // namespace Gpu::Ipc
