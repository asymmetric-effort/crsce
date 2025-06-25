/**
 * @file include/Gpu/Ipc/Pipe.h
 * @brief Encapsulates bidirectional pipe communication between parent and child processes.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <cstdint>
#include <unistd.h>


namespace Gpu::Ipc {
    /**
     * @brief RAII bidirectional message channel.  Takes ownership of two FDs.
     */
    class Pipe {
    public:
        /**
         * @param readFd  FD to read from (takes ownership).
         * @param writeFd FD to write to (takes ownership).
         */
        Pipe(int readFd, int writeFd) noexcept;

        // Non-copyable
        Pipe(const Pipe&) = delete;
        Pipe& operator=(const Pipe&) = delete;

        // Movable
        Pipe(Pipe&&) noexcept;
        Pipe& operator=(Pipe&&) noexcept;

        ~Pipe() noexcept;

        /** Serialize & send a message. */
        bool send(const Message &msg);

        /** Read & deserialize into msg. */
        bool receive(Message &msg);

    private:
        int readFd_{-1};
        int writeFd_{-1};

        void closeFds() noexcept;
        bool writeAll(const void *data, size_t size);
        bool readAll(void *data, size_t size);
    };

} // namespace Gpu::Ipc
