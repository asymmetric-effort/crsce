/**
 * @file include/Gpu/Device/Emulator/Emulator.h
 * @brief Define a GPU Emulator Device Class
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
 */
namespace Gpu::Device {
    /**
     * @name Gpu::Device::Emulator
     * @brief Parent-side implementation of a mock GPU using forked IPC and software thread emulation.
     * @ref docs/Gpu/Design/Gpu-Emulator.md
     */
    class Emulator final : public Interface {
    public:
        /**
         * @name constructor
         * @brief noop
         */
        Emulator();

        /**
         * @name destructor
         * @brief noop
         */
        ~Emulator() override;

        /**
         * @name init
         * @brief initialize the GPU Emulator.  This will spawn a child process, setup IPC and manage the mock GPU as
         *        a child process of many threads.
         * @return bool (true=no error)
         */
        bool init() override;

        /**
         * @name shutdown
         * @brief
         */
        void shutdown() override;

        /**
        * @name reset
         * @brief
         */
        void reset() override;

        /**
         * @name alloc
         * @brief
         * @param bytes std::size_t
         * @return Common::AbstractPtr
         */
        Common::AbstractPtr alloc(std::size_t bytes) override;

        /**
         * @name free
         * @param ptr Common::AbstractPtr
         * @return bool
         * @brief Given an abstract pointer, free the assocated resources.
         */
        bool free(Common::AbstractPtr &ptr) override;

        /**
         * @name write
         * @param source Common::Buffer8
         * @param dst Common::AbstractPtr
         * @return bool
         * @brief write a source buffer to the dst AbstractPtr on the mock GPU side.
         */
        bool write(const Common::Buffer8 &source, Common::AbstractPtr &dst) override;

        /**
         * @name write
         * @param source Common::Buffer64
         * @param dst Common::AbstractPtr
         * @return bool
         * @brief write a source buffer to the dst AbstractPtr on the mock GPU side.
         */
        bool write(const Common::Buffer64 &source, Common::AbstractPtr &dst) override;

        /**
         * @name read
         * @param source Common::Buffer64
         * @param dst Common::AbstractPtr
         * @return bool
         * @brief write a source buffer to the dst AbstractPtr on the mock GPU side.
         */
        bool read(Common::Buffer8 &source, Common::AbstractPtr &dst) override;

        /**
         * @name read
         * @param source Common::Buffer64
         * @param dst Common::AbstractPtr
         * @return bool
         * @brief write a source buffer to the dst AbstractPtr on the mock GPU side.
         */
        bool read(Common::Buffer64 &source, Common::AbstractPtr &dst) override;

        /**
         * @name registerKernel
         * @param id Common::KernelId
         * @param binary Common::Buffer8
         * @return bool
         * @brief add a binary blob to register a new kernel
         */
        bool registerKernel(Common::KernelId id, const Common::Buffer8 &binary) override;

        /**
         * @name launchTask
         * @param id Common::KernelId
         * @param args Common::Buffer8
         * @return bool
         * @brief launch the GPU task.
         */
        bool launchTask(Common::KernelId id, const Common::Buffer8 &args) override;

        /**
          * @name add
          * @param result Math::Matrix
          * @param lhs Math::Matrix
          * @param rhs Math::Matrix
          * @return bool
          * @brief result = lhs + rhs
          */
        bool add(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
          * @name dot
          * @param result Math::Matrix
          * @param lhs Math::Matrix
          * @param rhs Math::Matrix
          * @return bool
          * @brief result = lhs \dot rhs
          */
        bool dot(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
          * @name mul
          * @param result Math::Matrix
          * @param lhs Math::Matrix
          * @param rhs Math::Matrix
          * @return bool
          * @brief result = lhs * rhs
          */
        bool mul(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
          * @name sub
          * @param result Math::Matrix
          * @param lhs Math::Matrix
          * @param rhs Math::Matrix
          * @return bool
          * @brief result = lhs - rhs
          */
        bool sub(Math::Matrix &result, const Math::Matrix &lhs, const Math::Matrix &rhs) override;

        /**
          * @name transpose
          * @param result Math::Matrix
          * @param mat Math::Matrix
          * @return bool
          * @brief transpose a matrix store the result.
          */
        bool transpose(Math::Matrix &result, const Math::Matrix &mat) override;

        /**
         * @name reduce
         * @param result Math::Matrix
         * @param mat Math::Matrix
         * @param row_wise bool
         * @return bool
         * @brief transpose a matrix store the result.
         */
        bool reduce(Math::Matrix &result, const Math::Matrix &mat, bool row_wise) override;

        /**
         * @name barrier
         * @return bool
         */
        bool barrier() override;

        /**
         *
         */
        bool memfence() override;

        /**
         *
         */
        bool yield() override;

        /**
         *
         */
        bool wait(unsigned deadline) override;

    private:
        /**
         *
         */
        pid_t childPid_ = 0;

        /**
         *
         */
        std::unique_ptr<Ipc::Communications> ipc_;

        /**
         *
         */
        bool initialized_ = false;

        /**
         *
         */
        bool shutdown_ = false;
    };
} // namespace Gpu::Device
