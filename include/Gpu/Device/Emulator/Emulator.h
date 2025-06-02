// file: include/Gpu/Device/Emulator/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file include/Gpu/Device/Emulator/Emulator.h
 * @brief Defines the GPU Emulator device class for mock GPU functionality via IPC and software threading.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include <memory>
#include <sys/types.h>
#include "Gpu/Ipc/Result.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Device/Interface.h"
#include "Gpu/Ipc/Communications.h"
#include "Common/KernelId.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @class Emulator
     * @brief Parent-side implementation of a mock GPU using forked IPC and software thread emulation.
     *
     * Emulates a GPU device by spawning a child process for the mock GPU, communicating via IPC messages.
     * Supports memory allocation, data transfer, kernel registration, task launching, and basic math operations.
     * @ref docs/Gpu/Design/Gpu-Emulator.md
     */
    class Emulator final : public Interface {
    public:
        /**
         * @name constructor
         * @public
         * @brief Default constructor (no operation).
         * @class Emulator
         * @memberof Interface
         * @brief noop
         */
        Emulator();

        /**
         * @name destructor
         * @public
         * @brief Destructor ensures proper shutdown.
         */
        ~Emulator() override;

        /**
         * @name init
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief initialize the GPU Emulator.  This will spawn a child process, setup IPC and manage the mock GPU as
         *        a child process of many threads.
         * @return bool (true=no error)
         */
        bool init() override;

        /**
         * @name shutdown
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Shutdown the GPU emulator: send shutdown message and clean up IPC.
         */
        void shutdown() override;

        /**
         * @name reset
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Reset the GPU emulator state and send reset command to child.
         */
        void reset() override;

        /**
         * @name alloc
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Allocate a memory buffer on the mock GPU.
         * @param bytes Number of bytes to allocate.
         * @return Abstract pointer representing the GPU buffer, or null on failure.
         */
        Common::AbstractPtr alloc(std::size_t bytes) override;

        /**
         * @name free
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Free a previously allocated GPU buffer.
         * @param ptr Reference to abstract pointer to free; set to null on success.
         * @return true if free succeeded, false otherwise.
         */
        bool free(Common::AbstractPtr &ptr) override;

        /**
         * @name write
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Write an 8-bit buffer to GPU memory.
         * @param source Data buffer to write.
         * @param dst Abstract pointer to destination GPU memory.
         * @return true if write succeeded, false otherwise.
         */
        bool write(const Common::Buffer8 &source, Common::AbstractPtr &dst) override;

        /**
         * @name write
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Write a 64-bit buffer to GPU memory.
         * @param source Data buffer to write.
         * @param dst Abstract pointer to destination GPU memory.
         * @return true if write succeeded, false otherwise.
         */
        bool write(const Common::Buffer64 &source, Common::AbstractPtr &dst) override;

        /**
         * @name read
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Read data from GPU memory into an 8-bit buffer.
         * @param source Abstract pointer to GPU memory source.
         * @param dst Data buffer to be populated with read bytes.
         * @return true if read succeeded, false otherwise.
         */
        bool read(Common::Buffer8 &source, Common::AbstractPtr &dst) override;

        /**
         * @name read
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Read data from GPU memory into a 64-bit buffer.
         * @param source Abstract pointer to GPU memory source.
         * @param dst Data buffer to be populated with read values.
         * @return true if read succeeded, false otherwise.
         */
        bool read(Common::Buffer64 &source, Common::AbstractPtr &dst) override;

        /**
         * @name registerKernel
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Register a kernel binary blob with the emulator.
         * @param id Unique kernel identifier.
         * @param binary Binary code blob for the kernel.
         * @return true if registration succeeded, false otherwise.
         */
        bool registerKernel(Common::KernelId id, const Common::Buffer8 &binary) override;

        /**
         * @name launchTask
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Launch a registered GPU kernel with provided arguments.
         * @param id Kernel identifier to launch.
         * @param args Argument buffer to pass to the kernel.
         * @return true if kernel launch succeeded, false otherwise.
         */
        bool launchTask(Common::KernelId id, const Common::Buffer8 &args) override;

        /**
         * @name add
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Perform element-wise addition of two matrices on the GPU emulator.
         * @param result Output matrix to store sum.
         * @param lhs Left-hand side matrix.
         * @param rhs Right-hand side matrix.
         * @return true if addition succeeded, false otherwise.
         */
        bool add(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
         * @name dot
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Perform matrix multiplication (dot product) on GPU emulator.
         * @param result Output matrix to store dot product.
         * @param lhs Left-hand side matrix.
         * @param rhs Right-hand side matrix.
         * @return true if dot product succeeded, false otherwise.
         */
        bool dot(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
         * @name mul
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Perform element-wise multiplication of two matrices.
         * @param result Output matrix to store product.
         * @param lhs Left-hand side matrix.
         * @param rhs Right-hand side matrix.
         * @return true if multiplication succeeded, false otherwise.
         */
        bool mul(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
         * @name sub
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Perform element-wise subtraction of two matrices.
         * @param result Output matrix to store difference.
         * @param lhs Left-hand side matrix.
         * @param rhs Right-hand side matrix.
         * @return true if subtraction succeeded, false otherwise.
         */
        bool sub(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
         * @name transpose
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Transpose a matrix.
         * @param result Output matrix to store transposed data.
         * @param mat Input matrix to transpose.
         * @return true if transpose succeeded, false otherwise.
         */
        bool transpose(Math::Matrix &result, const Math::Matrix &mat) override;

        /**
         * @name reduce
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Reduce a matrix along rows or columns.
         * @param result Output matrix to store reduced values.
         * @param mat Input matrix to reduce.
         * @param row_wise If true, reduce row-wise; otherwise, reduce column-wise.
         * @return true if reduction succeeded, false otherwise.
         */
        bool reduce(Math::Matrix &result, const Math::Matrix &mat, bool row_wise) override;

        /**
         * @name barrier
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Synchronize all outstanding GPU operations (barrier).
         * @return true if barrier succeeded, false otherwise.
         */
        bool barrier() override;

        /**
         * @name memfence
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Perform a memory fence on the GPU emulator.
         * @return true if memfence succeeded, false otherwise.
         */
        bool memfence() override;

        /**
         * @name yield
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Yield execution of the current GPU task.
         * @return true if yield succeeded, false otherwise.
         */
        bool yield() override;

        /**
         * @name wait
         * @class Emulator
         * @memberof Interface
         * @public
         * @brief Wait for GPU tasks to complete up to a deadline.
         * @param deadline Time in milliseconds to wait before timeout.
         * @return true if all tasks finished before deadline, false otherwise.
         */
        bool wait(unsigned deadline) override;

    private:
        /**
         * @property childPid_
         * @class Emulator
         * @memberof Interface
         * @private
         * @brief Process ID of the forked child emulator process.
         */
        pid_t childPid_ = 0;

        /**
         * @property ipc_
         * @class Emulator
         * @memberof Interface
         * @private
         * @brief IPC communications object for parent/child messaging.
         */
        std::unique_ptr<Ipc::Communications> ipc_;

        /**
         * @property initialized_
         * @class Emulator
         * @memberof Interface
         * @private
         * @brief True if the emulator has been initialized successfully.
         */
        bool initialized_ = false;

        /**
         * @property shutdown_
         * @private
         * @class Emulator
         * @memberof Interface
         * @brief True if the emulator has been shut down.
         */
        bool shutdown_ = false;
    };
} // namespace Gpu::Device
