// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include "Gpu/Ipc/Communications.h"
#include "Gpu/common/PointerTracker.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <sys/types.h>

namespace Gpu::Device {

    /**
     * @class Emulator
     * @brief Front-end controller for a forked GPU emulator child process.
     *
     * This class owns and manages all IPC and memory tracking for the emulated GPU backend.
     * It launches a child process via fork() in `init()`, establishes IPC pipes, manages
     * memory via pointer tracking, and supports GPU task lifecycle operations.
     */
    class Emulator {
    public:
        /**
         * @name constructor
         * @brief default constructor
         */
        Emulator();

        /**
         * @name destructor
         * @brief The class destructor will ensure the class instance is properly shutdown.
         */
        ~Emulator();

        /**
         * @name init
         * @brief Initialize the emulator. Must be called before other methods.
         * This will fork the child process and establish IPC via Communications.
         */
        bool init();

        /**
         * @name shutdown
         * @brief Gracefully shut down the emulator and clean up resources.
         */
        void shutdown();

        /**
         * @name alloc
         * @brief Allocate a buffer on the emulated GPU.
         * @param bytes The number of bytes to allocate.
         * @return A valid device pointer on success, nullptr on failure.
         */
        void* alloc(std::size_t bytes);

        /**
         * @name free
         * @brief Free a previously allocated buffer.
         * @param ptr The device pointer to free.
         */
        void free(void* ptr);

        /**
         * @name write
         * @brief Write data to a device buffer.
         * @param ptr Device pointer.
         * @param src Source buffer.
         * @param size Number of bytes to copy.
         * @return true on success.
         */
        bool write(void* ptr, const void* src, std::size_t size);

        /**
         * @name read
         * @brief Read data from a device buffer.
         * @param dst Destination buffer.
         * @param ptr Device pointer.
         * @param size Number of bytes to copy.
         * @return true on success.
         */
        bool read(void *dst, void *ptr, std::size_t size) const;

        /**
         * @name registerKernel
         * @brief Register a kernel for future launch.
         * @param kernelId ID to assign to the kernel.
         * @param binary Kernel binary blob.
         */
        void registerKernel(uint32_t kernelId, const std::vector<uint8_t>& binary);

        /**
         * @name launchTask
         * @brief Launch a previously registered kernel task.
         * @param kernelId The kernel to launch.
         * @param args Optional argument payload.
         * @return true on success.
         */
        bool launchTask(uint32_t kernelId, const std::vector<uint8_t>& args = {});

        /**
         * @name reset
         * @brief Reset the device, clearing all allocations.
         */
        void reset();

    private:
        /**
         * @name childPid_
         * @brief child process id.
         * @type pid_t
         */
        pid_t childPid_ = -1;
        /**
         * @name com_
         * @brief IPC Communications channel manager reference
         * @type std::unique_ptr<Gpu::Ipc::Communications>
         */
        std::unique_ptr<Ipc::Communications> comm_;
        /**
         * @name tracker_
         * @brief memory allocation tracker
         * @type PointerTracker
         */
        PointerTracker tracker_;
        /**
         * @name initialized_
         * @brief indicates whether Gpu::Emulator is initialized.
         * @type bool
         */
        bool initialized_ = false;
    };

} // namespace Gpu::Device
