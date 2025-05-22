`Gpu::Device::MockGpu`
======================

## Purpose

The `Gpu::Device::MockGpu` class serves as the child process entry point in the CRSCE GPU emulator architecture. It
receives and processes commands from the parent (`Gpu::Device::Emulator`) over IPC and emulates GPU behavior, including
memory management and concurrent kernel execution.

## Role in Architecture

- **Instantiated in the child process only** after `fork()`.
- Reads and decodes `Gpu::Ipc::Message` objects sent over `pipeToChild`.
- Responds to the parent using `Gpu::Ipc::Response` objects over `pipeFromChild`.
- Delegates all operation handling to `Gpu::RuntimeManager`.

## Dependencies

* [`Gpu::Ipc::Message`](./Gpu-Ipc-Message.md)
* [`Gpu::Ipc::Response`](./Gpu-Ipc-Response.md)
* [`Gpu::Ipc::Communications`](./Gpu-Ipc-Communications.md)
* [`Gpu::RuntimeManager`](./Gpu-RuntimeManager.md)

## Properties

| Property         | Type                        | Description                              |
|------------------|-----------------------------|------------------------------------------|
| `comm`           | `Gpu::Ipc::Communications&` | Reference to IPC communication channel   |
| `runtimeManager` | `Gpu::RuntimeManager`       | Handles all GPU emulation logic          |
| `shutdownFlag`   | `std::atomic<bool>`         | True once a shutdown command is received |

## Constructor

| Signature                                  |
|--------------------------------------------|
| `MockGpu(Gpu::Ipc::Communications& comm);` |

Initializes internal state and binds to the IPC communications channel.

## Methods

### `void run()`

Main execution loop. Repeatedly:

1. Receives a `Gpu::Ipc::Message` from the parent.
2. Switches on `CommandType` to dispatch to the appropriate handler.
3. Sends a corresponding `Gpu::Ipc::Response` after completing the command.
4. Terminates only after processing a valid `Shutdown` command.

### `bool isShutdown() const`

Returns `true` if the emulator has entered shutdown state. Used internally to exit the `run()` loop.

## Command Handlers

Each handler is defined in `Gpu::RuntimeManager` and invoked by `MockGpu`.

| Handler                  | Description                                                       |
|--------------------------|-------------------------------------------------------------------|
| `handleAlloc()`          | Allocates memory via `Gpu::Ipc::MemoryTracker`.                   |
| `handleFree()`           | Frees a memory region associated with an `AbstractPtr`.           |
| `handleWrite()`          | Writes host buffer to a device buffer.                            |
| `handleRead()`           | Reads device buffer into a host buffer.                           |
| `handleRegisterKernel()` | Stores a kernel binary blob indexed by `kernelId`.                |
| `handleLaunchTask()`     | Spawns a detached thread to run a kernel.                         |
| `handleReset()`          | Clears memory and joins all threads. Does **not** exit.           |
| `handleShutdown()`       | Joins all threads, clears memory, and sets `shutdownFlag = true`. |

Each of these functions:

- Constructs and returns a `Gpu::Ipc::Response`.
- Validates input and emits `Gpu::Ipc::FailureCodes` upon failure.
- Operates **only** on valid commands; otherwise a protocol violation is assumed.

## Shutdown Behavior

Upon receiving a `Shutdown` command:

1. `MockGpu::handleShutdown()` is invoked.
2. `shutdownFlag` is set.
3. `runtimeManager.shutdown()` is called.
    - Joins all threads in `ThreadRegistry`.
    - Clears all memory.
4. A `Gpu::Ipc::Response` with status = 0 is returned.
5. `run()` loop exits.

## Safety Guarantees

- The `run()` loop is guarded by `shutdownFlag`.
- No other thread is spawned inside `MockGpu`; all concurrency is managed via `RuntimeManager`.
- All IPC failures are translated to structured `Gpu::Ipc::Response` status codes.
- Lifetime of `comm` is externally managed by the `Gpu::Device::Emulator` parent before fork.

## Lifecycle Summary

| Phase        | Activity                                       |
|--------------|------------------------------------------------|
| Construction | Bound to communication channel                 |
| `run()`      | Starts reading commands from pipe              |
| Shutdown     | Joins all threads, clears state, exits process |

