/**
 * @file include/Gpu/Ipc/Communications.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <atomic>
#include <unistd.h>
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"
#include "Gpu/Ipc/Handles.h"

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
         * @param isParentProcess
         */
        Communications();

        /**
         * @name destructor
         * @brief class destructor
         * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
         */
        ~Communications() = default;;

        claimLeft(){} //claim request sender / response receiver
        claimRight(){} //claim response sender / request receiver


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

        //Constants to use in read/write fd indexes
        static constexpr int readEndpoint = 0;
        static constexpr int writeEndpoint = 1;
        static constexpr int closed = -1;

    private:
        /**
         * @name requestPipe
         * @class Communications
         * @namespace Gpu::Ipc
         * @brief This is the IPC file handle pair for sending/receiving requests from parent to child process.
         */
        Handles requestPipe{};

        /**
         * @name responsePipe
         * @class Communications
         * @namespace Gpu::Ipc
         * @brief This is the IPC file handle pair for sending/receiving responses from child to parent.
         */
        Handles responsePipe{};
        bool isParent = true;
    };
} // namespace Gpu::Ipc
