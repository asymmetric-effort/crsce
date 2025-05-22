`Gpu::Device::Emulator`
=======================

## Purpose

A concrete implementation of `Gpu::Device::Interface` class. The `Gpu::Device::Emulator` class creates a mock GPU for
debugging and testing as well as development of GPU-enabled projects.

### Dependencies

* [`Common::AbstractPtr](./Common-AbstractPtr.md)
* [`Gpu::Ipc::CommandType`](./Gpu-Ipc-CommandType.md)
* [`Gpu::Ipc::Result`](./Gpu-Ipc-Result.md)
* [`Gpu::Ipc::FailureCodes`](./Gpu-Ipc-FailureCodes.md)
* [`Common::Buffer8](./Common-Buffer8.md)
* [`Common::Buffer64](./Common-Buffer64.md)

#### Properties

| Property      | Type                                   | Description                                      |
|---------------|----------------------------------------|--------------------------------------------------|
| `childPid`    | `pid_t`                                | Process Id                                       |
| `ipcChannel`  | `std::unique_ptr<Ipc::Communications>` | IPC Communication channel                        |
| `tracker`     | `Gpu::Ipc::MemoryTracker`              | memory allocation tracker                        |
| `initialized` | `bool`                                 | indicates whether `Gpu::Emulator` is initialized |

### Constructor

* Initialize the target GPU internal state. For the emulator this means launching the child process which
  emulates the hardware GPU.
* The constructor will detect the current process PID (parentPid) and launch a child process as the GPU emulator.
  These PIDs will be used to setup IPC Communications between parent and child.

### Destructor

* Safely shutdown and clean up GPU state. For the emulator this will terminate the child process clean.

#### Parent/Child IPC Access Validation

| Scope     | Method                        | Description                                           |
|-----------|-------------------------------|-------------------------------------------------------|
| `private` | `bool validateParentAccess()` | verify send/recv permission based on parent/child pid |
| `private` | `bool validateChildAccess()`  | verify send/recv permission based on parent/child pid |

### Lifecycle

| Scope    | Method             | Description                                  |
|----------|--------------------|----------------------------------------------|
| `public` | `bool init();`     | re-initialize mock GPU state                 |
| `public` | `void shutdown();` | reset the mock GPU state                     |
| `public` | `void reset();`    | shutdown the mock GPU and all of its threads |

### Memory Management

| Scope    | Method                                                            | Description                                              |
|----------|-------------------------------------------------------------------|----------------------------------------------------------|
| `public` | `AbstractPtr* alloc(std::size_t bytes);`                          | Allocate device memory in the MemoryTracker table        |
| `public` | `bool free(Common::AbstractPtr& ptr);`                            | Frees device memory previously allocated using `alloc()` |
| `public` | `bool write(Common::AbstractPtr& dst, Common::Buffer8& source);`  | write `source` buffer to the `destination`               |
| `public` | `bool write(Common::AbstractPtr& dst, Common::Buffer64& source);` | write `source` buffer to the `destination`               |
| `public` | `bool read(Common::AbstractPtr& dst, Common::Buffer8& source);`   | read the `source` from teh `destination` reference       |
| `public` | `bool read(Common::AbstractPtr& dst, Common::Buffer64& source);`  | read the `source` from teh `destination` reference       |

### Kernel Control

(`Gpu::KernelId` is a `uint64_t`)

| Scope    | Method                                                             | Description                              |
|----------|--------------------------------------------------------------------|------------------------------------------|
| `public` | `void registerKernel(KernelId id, const Common::Buffer8& binary);` | register a binary blob with a given GPU  |
| `public` | `bool launchTask(KernelId id, const Common::Buffer8& args = {});`  | launch a task using a pre-registered GPU |

### Matrix Math & Vector Operations

ToDo: fix all this...

| Scope    | Method                                                                       | Description           |
|----------|------------------------------------------------------------------------------|-----------------------|
| `public` | `void dot(Common::Buffer64& result, const Matrix& lhs, const Matrix& rhs);`  | calculate dot product |
| `public` | `void addv(Common::Buffer64& result, const Matrix& lhs, const Matrix& rhs);` | result = lhs+rhs      |
| `public` | `void subv(Common::Buffer64& result, const Matrix& lhs, const Matrix& rhs);` | result = lhs-rhs      |
| `public` | `void mulm(Common::Buffer64& result, const Matrix& lhs, const Matrix& rhs);` | result = lhs*rhs      |
| `public` | `void transpose(Common::Buffer64& result, const Matrix& mat);`               | transpose mat         |
| `public` | `void reduce(Common::Buffer64& result, const Matrix& mat, bool rowwise);`    | reduce mat            |

### Synchronization

| Scope    | Method                     | Description                                                                                                               |
|----------|----------------------------|---------------------------------------------------------------------------------------------------------------------------|
| `public` | `virtual void barrier();`  | Ensures running GPU threads reach the same execution point before any can proceed.                                        |
| `public` | `virtual void memfence();` | Provide memory-ordering guarantees by flushing pending memory writes to global/shared memory before continuing execution. |
| `public` | `virtual void yield();`    | This method hints to the runtime that the current kernel or task may yield control.                                       |

