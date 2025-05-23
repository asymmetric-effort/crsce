`Gpu::Device::Emulator`
=======================

## Purpose

A concrete implementation of `Gpu::Device::Interface` class. The `Gpu::Device::Emulator` class creates a mock GPU for
debugging and testing as well as development of GPU-enabled projects. The `Gpu::Device::Emulator` class instance
represents a front-end for a mock graphics processor unit.  This emulator spawns a child process which represents the
mock GPU (`Gpu::Device::MockGpu`).  Communication between `Gpu::Device::Emulator` and `Gpu::Device::MockGpu` is
facilitated by `Gpu::Ipc::Communications`.

## Dependencies

* [`Common::AbstractPtr](./Common-AbstractPtr.md)
* [`Gpu::Ipc::CommandType`](./Gpu-Ipc-CommandType.md)
* [`Gpu::Ipc::Result`](./Gpu-Ipc-Result.md)
* [`Gpu::Ipc::FailureCodes`](./Gpu-Ipc-FailureCodes.md)
* [`Common::Buffer8](./Common-Buffer8.md)
* [`Common::Buffer64](./Common-Buffer64.md)
* [`Gpu::Math::Matrix`](./Gpu-Math-Matrix.md)
* [`Gpu::KernelManager`](./Gpu-Kernel-Manager.md)

## Properties

| Property      | Type                                   | Description                                      |
|---------------|----------------------------------------|--------------------------------------------------|
| `childPid`    | `pid_t`                                | Process Id                                       |
| `ipcChannel`  | `std::unique_ptr<Ipc::Communications>` | IPC Communication channel                        |
| `tracker`     | `Gpu::Ipc::MemoryTracker`              | RAII compliant memory allocation tracker         |
| `initialized` | `bool`                                 | indicates whether `Gpu::Emulator` is initialized |

## Constructor

* Initialize the target GPU internal state. For the emulator this means launching the child process which
  emulates the hardware GPU.
* The constructor will detect the current process PID (parentPid) and launch a child process as the GPU emulator.
  These PIDs will be used to set up IPC Communications between parent and child.

## Destructor

* Safely shutdown and clean up GPU state. For the emulator this will terminate the child process clean.

## Parent/Child IPC Access Validation

| Scope     | Method                        | Description                                           |
|-----------|-------------------------------|-------------------------------------------------------|
| `private` | `bool validateParentAccess()` | verify send/recv permission based on parent/child pid |
| `private` | `bool validateChildAccess()`  | verify send/recv permission based on parent/child pid |

### Notes

* These methods return `true` if permission is granted or `false` if not.

## Lifecycle

| Scope    | Method             | Description                                                       |
|----------|--------------------|-------------------------------------------------------------------|
| `public` | `bool init();`     | re-initialize mock GPU state. returns true=success, false=failure |
| `public` | `void shutdown();` | reset the mock GPU state                                          |
| `public` | `void reset();`    | shutdown the mock GPU and all of its threads                      |

### Notes:

* If `shutdown()` is called before `init()`, no operation will be performed, no error will occur.
* If `reset()` is called before `init()`, no operation will be performed, no error will occur.
* If `init()` or `reset()` are called after `shutdown()` and exception will be thrown because `shutdown()` is final.
* If `init()` is called after `reset()` no error will occur as this is normal.
* The `init()` returns true for success or false on error.

## Memory Management

| Scope    | Method                                                           | Description                                              |
|----------|------------------------------------------------------------------|----------------------------------------------------------|
| `public` | `AbstractPtr alloc(std::size_t bytes);`                          | Allocate device memory in the MemoryTracker table        |
| `public` | `bool free(Common::AbstractPtr& ptr);`                           | Frees device memory previously allocated using `alloc()` |
| `public` | `bool write(Common::Buffer8& source,Common::AbstractPtr& dst);`  | write `source` buffer to the `destination`               |
| `public` | `bool write(Common::Buffer64& source,Common::AbstractPtr& dst);` | write `source` buffer to the `destination`               |
| `public` | `bool read(Common::Buffer8& source,Common::AbstractPtr& dst);`   | read the `source` from the `destination` reference       |
| `public` | `bool read(Common::Buffer64& source,Common::AbstractPtr& dst);`  | read the `source` from the `destination` reference       |

## Notes:

* If any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.
* The methods `free()`, `write()`, `read()` return true on success and false on error
* The `alloc()` returns `0` if no memory is allocated or non-zero referencing a memory object.

## Kernel Control

(`Gpu::KernelId` is a `uint64_t`)

| Scope    | Method                                                             | Description                                 |
|----------|--------------------------------------------------------------------|---------------------------------------------|
| `public` | `bool registerKernel(KernelId id, const Common::Buffer8& binary);` | register a binary blob with a given GPU     |
| `public` | `bool launchTask(KernelId id, const Common::Buffer8& args = {});`  | launch a task using a pre-registered kernel |

### Notes:

* Return true on success or false on error.
* If any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

## Matrix Math & Vector Operations

| Scope    | Method                                                                                             | Description           |
|----------|----------------------------------------------------------------------------------------------------|-----------------------|
| `public` | `bool dot(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | calculate dot product |
| `public` | `bool add(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs+rhs      |
| `public` | `bool sub(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs-rhs      |
| `public` | `bool mul(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs*rhs      |
| `public` | `bool transpose(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat);`                         | transpose mat         |
| `public` | `bool reduce(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat, bool rowwise);`              | reduce mat            |

### Notes:

* Return true on success or false on error.
* These math operations should transfer the `Gpu::Math::Matrix` to the GPU, perform the operation and return the result
* If any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

## Synchronization

| Scope    | Method                         | Description                                                                                                               |
|----------|--------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| `public` | `bool barrier();`              | Ensures running GPU threads reach the same execution point before any can proceed.                                        |
| `public` | `bool memfence();`             | Provide memory-ordering guarantees by flushing pending memory writes to global/shared memory before continuing execution. |
| `public` | `bool yield();`                | This method hints to the runtime that the current kernel or task may yield control.                                       |
| `public` | `bool wait(unsigned deadline)` | Block until all kernel tasks complete or the deadline (in milliseconds) is reached.                                       |                                                                     |

### Notes:

* Return true on success or false on error.
* If any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

