GPU Abstraction Layer Checklist
===============================

## Phase 1 — Core Infrastructure

| Priority | Name                   | Description                                                        |
|----------|------------------------|--------------------------------------------------------------------|
| 1.       | Gpu::Exceptions        | Define exception types: DeviceNotReady, KernelNotFound, etc.       |
| 2.       | Gpu::Ipc::FailureCodes | Enum indicating specific failure modes in IPC or runtime handling. |
| 3.       | Common::AbstractPtr    | Typedef for uint64_t, used as pseudo-address in memory tracker.    |
| 4.       | Gpu::Ipc::CommandType  | Enum for IPC instructions (Alloc, Free, LaunchTask, etc.).         |
| 5.       | Gpu::Ipc::Result       | Enum for low-level IPC call success/failure semantics.             |

## Phase 2 — Buffers and IPC Memory

| Priority | Name                    | Description                                                           |
|----------|-------------------------|-----------------------------------------------------------------------|
| 1.       | Common::Buffer8         | Typedef for std::vector<uint8_t> (raw byte data).                     |
| 2.       | Common::Buffer64        | Typedef for std::vector<uint64_t> (aligned memory).                   |
| 3.       | Gpu::Ipc::MemoryTracker | Manages allocations via AbstractPtr, provides safe lookup/free/write. |

## Phase 3 — IPC Transport Layer

| Priority | Name                     | Description                                                              |
|----------|--------------------------|--------------------------------------------------------------------------|
| 1.       | Gpu::Ipc::Response       | Encapsulates binary response: `[status][size][data[]]`.                  |
| 2.       | Gpu::Ipc::Message        | Encapsulates commands: CommandType, kernelId, ptr, size.                 |
| 3.       | Gpu::Ipc::Communications | Manages bidirectional pipe communication; send/recv, process validation. |

## Phase 4 — Device Abstraction and Kernel Management

| Priority | Name                   | Description                                                                           |
|----------|------------------------|---------------------------------------------------------------------------------------|
| 1.       | Gpu::Device::Interface | Pure virtual interface for all GPU implementations.                                   |
| 2.       | Gpu::KernelManager     | Stores kernel blobs by KernelId, provides register, get, erase.                       |
| 3.       | Gpu::ThreadRegistry    | Tracks detached threads launched per kernel task.                                     |
| 4.       | Gpu::ThreadRuntime     | a binary blob (defined in Kernel-Binary-Blob-Format.md).                              |
| 5.       | Gpu::RuntimeManager    | Main command dispatcher in child; calls handlers: handleAlloc, handleLaunchTask, etc. |

## Phase 5 — Math + Execution Backends

| Priority | Name                  | Description                                                       |
|----------|-----------------------|-------------------------------------------------------------------|
| 1.       | Gpu::Math::Matrix     | High-level matrix API interfacing with underlying GPU logic.      |
| 2.       | Gpu::Device::MockGpu  | Child-side loop: receives messages, calls RuntimeManager.         |
| 3.       | Gpu::Device::Emulator | Parent-side device implementation using Gpu::Ipc::Communications. | 
| 4.       | Gpu::Device::Cuda     | Stub for future native CUDA backend (inherits Interface).         |         
| 5.       | Gpu::Device::Roc      | Stub for AMD ROCm backend.                                        |                                    
| 6.       | Gpu::Device::Metal    | Stub for Apple Metal backend.                                     |                                     
