`Gpu::RuntimeManager`
=====================

## Purpose

The `Gpu::RuntimeManager` class is responsible for executing all GPU emulation commands received by the child process (`Gpu::Device::MockGpu`). It implements the logic for memory allocation, kernel registration, task launching, and lifecycle control.

## Role in Architecture

- Owned exclusively by `Gpu::Device::MockGpu`.
- Acts as the command handler for `Gpu::Ipc::Message` instructions.
- Uses `Gpu::Ipc::MemoryTracker`, `Gpu::ThreadRegistry`, and `Gpu::KernelManager` to manage emulated GPU state.

## Dependencies

* [`Gpu::Ipc::MemoryTracker`](Gpu-Ipc-MemoryTracker.md)
* [`Gpu::ThreadRegistry`](Gpu-ThreadRegistry.md)
* [`Gpu::KernelManager`](Gpu-KernelManager.md)
* [`Gpu::Ipc::Message`](Gpu-Ipc-Message.md)
* [`Gpu::Ipc::Response`](Gpu-Ipc-Response.md)

## Properties

| Property       | Type                       | Description                               |
|----------------|----------------------------|-------------------------------------------|
| `memory`       | `Gpu::Ipc::MemoryTracker`   | Tracks all emulated GPU memory            |
| `threads`      | `Gpu::ThreadRegistry`       | Manages concurrent kernel threads         |
| `kernels`      | `Gpu::KernelManager`        | Stores and executes registered kernels    |
| `shutdownFlag` | `std::atomic<bool>`         | Indicates whether shutdown is in progress |

## Constructor

| Signature |
|-----------|
| `RuntimeManager();` |

Initializes internal state. All subsystems are constructed empty.

---

## Methods

### `Gpu::Ipc::Response handleAlloc(const Gpu::Ipc::Message&)`

Allocates memory of `msg.size` bytes.
- Returns `ptr` in response payload.
- Status: `Success` or `FailureCodes::OutOfMemory`.

---

### `Gpu::Ipc::Response handleFree(const Gpu::Ipc::Message&)`

Frees memory at `msg.ptr`.
- Returns status `Success` or `FailureCodes::InvalidPointer`.

---

### `Gpu::Ipc::Response handleWrite(const Gpu::Ipc::Message&, const std::vector<uint8_t>& payload)`

Copies `payload` bytes into device memory at `msg.ptr`.
- Fails if `payload.size() != msg.size`.
- Returns `Success` or `FailureCodes::WriteError`.

---

### `Gpu::Ipc::Response handleRead(const Gpu::Ipc::Message&)`

Reads `msg.size` bytes from `msg.ptr`.
- Returns `data[]` in response payload.
- Returns `Success` or `FailureCodes::ReadError`.

---

### `Gpu::Ipc::Response handleRegisterKernel(const Gpu::Ipc::Message&, const std::vector<uint8_t>& kernelBlob)`

Stores `kernelBlob` under `msg.kernelId`.
- Overwrites if already registered.
- Returns `Success` or `FailureCodes::KernelStorageError`.

---

### `Gpu::Ipc::Response handleLaunchTask(const Gpu::Ipc::Message&, const std::vector<uint8_t>& args = {})`

Creates a detached thread that:
- Looks up kernel by `msg.kernelId`.
- Invokes `Gpu::ThreadRuntime::run(kernelBlob, args)`.
- Registers the thread with `ThreadRegistry`.

Returns:
- `Success` if launched.
- `FailureCodes::KernelNotFound` or `ThreadLaunchFailure`.

---

### `Gpu::Ipc::Response handleReset()`

- Calls `ThreadRegistry::joinAll()`
- Clears `ThreadRegistry`, `MemoryTracker`, and `KernelManager`
- Leaves process running
- Returns `Success` or `FailureCodes::ResetFailure`

---

### `Gpu::Ipc::Response handleShutdown()`

- Sets `shutdownFlag = true`
- Calls `ThreadRegistry::joinAll()`
- Clears all internal state
- Returns `Success`

---

### `bool isShutdown() const`

Returns `true` if shutdown is in progress. Called by `MockGpu::run()`.

---

## Thread Safety

- All thread insertions and joins are done via `ThreadRegistry`.
- Payload buffers are assumed immutable once received.
- `shutdownFlag` is an `std::atomic<bool>` checked by external control flow.

---

## Failure Codes

All handler methods use `Gpu::Ipc::FailureCodes` to report:
- Memory errors
- Kernel lookup failures
- Thread start exceptions
- Pointer dereferencing violations

---

## Lifecycle Summary

| Phase     | Activity                                     |
|-----------|----------------------------------------------|
| Init      | Allocates internal state                     |
| Command   | Routes Message → handler                     |
| Launch    | Starts thread for registered kernel          |
| Reset     | Clears all memory and threads                |
| Shutdown  | Joins all threads, clears all state, exits   |
