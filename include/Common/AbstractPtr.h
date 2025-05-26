/**
 * @file include/Common/AbstractPtr.h
 * @name Common::AbstractPtr
 * @ref docs/Gpu/Design/Common-AbstractPtr.md
 * @typedef Common::AbstractPtr
 * @brief Represents a pseudo-random 64-bit memory reference used by the GPU abstraction layer.
 *
 * AbstractPtr is an opaque, non-dereferenceable handle for tracking memory allocations on the emulated GPU.
 * It is used by Gpu::Ipc::MemoryTracker as a stable identifier for device memory blocks.
 *
 * Characteristics:
 * - `0` is always treated as null.
 * - All non-zero values are treated as valid abstract memory handles.
 * - Values must only be interpreted using the MemoryTracker API.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <cstdint>

namespace Common {

    using AbstractPtr = uint64_t;

} // namespace Common
