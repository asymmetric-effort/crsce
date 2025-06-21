/**
* @file include/Gpu/Ipc/Handles.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <array>

namespace Gpu::Ipc {

    /**
     * @name Handles
     * @brief Represents a unidirectional pipe (read/write) as a pair of file descriptors.
     */
    using Handles = std::array<int, 2>;

}
