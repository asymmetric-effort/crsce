`Gpu::Device::Interface`
========================

## Purpose

The `Gpu::Device::Interface` provides a parent class in an inheritance tree. This abstract class is used to represent
the GPU Abstraction Layer through which the consuming application can determine which of the concreate GPU
implementations to use at runtime.

### Dependencies

* [`Gpu::Device::Emulator`](./Gpu-Emulator.md)
* [`Gpu::Device::Cuda`](./Gpu-Cuda.md)
* [`Gpu::Device::Roc`](./Gpu-AmdRoc.md)
* [`Gpu::Device::Metal`](./Gpu-AppleMetal.md)
* [`Gpu::Math::Matrix`](./Gpu-Math-Matrix.md)

#### Properties

| Property      | Type                                   | Description                                      |
|---------------|----------------------------------------|--------------------------------------------------|
| `childPid`    | `pid_t`                                | Process Id                                       |
| `ipcChannel`  | `std::unique_ptr<Ipc::Communications>` | IPC Communication channel                        |
| `tracker`     | `Gpu::Ipc::MemoryTracker`              | memory allocation tracker                        |
| `initialized` | `bool`                                 | indicates whether `Gpu::Emulator` is initialized |

### Constructor

* Initialize the target GPU.

### Destructor

* Safely shutdown and clean up GPU.

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
| `public` | `void registerKernel(KernelId id, const Common::Buffer8& binary);` | register a binary blob with a given GPU     |
| `public` | `bool launchTask(KernelId id, const Common::Buffer8& args = {});`  | launch a task using a pre-registered kernel |

### Notes:

* if any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

## Matrix Math & Vector Operations

| Scope    | Method                                                                                             | Description           |
|----------|----------------------------------------------------------------------------------------------------|-----------------------|
| `public` | `void dot(Common::Buffer64& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);`  | calculate dot product |
| `public` | `void addv(Common::Buffer64& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs+rhs      |
| `public` | `void subv(Common::Buffer64& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs-rhs      |
| `public` | `void mulm(Common::Buffer64& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs*rhs      |
| `public` | `void transpose(Common::Buffer64& result, const Gpu::Math::Matrix& mat);`                          | transpose mat         |
| `public` | `void reduce(Common::Buffer64& result, const Gpu::Math::Matrix& mat, bool rowwise);`               | reduce mat            |

### Notes:

* if any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

## Synchronization

| Scope    | Method                         | Description                                                                                                               |
|----------|--------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| `public` | `void barrier();`              | Ensures running GPU threads reach the same execution point before any can proceed.                                        |
| `public` | `void memfence();`             | Provide memory-ordering guarantees by flushing pending memory writes to global/shared memory before continuing execution. |
| `public` | `void yield();`                | This method hints to the runtime that the current kernel or task may yield control.                                       |
| `public` | `void wait(unsigned deadline)` | Block until all kernel tasks complete or the deadline (in milliseconds) is reached.                                       |                                                                     |

### Notes:

* if any of these methods are called after `shutdown()` or `reset()` or before `init()` an exception will be thrown
  using `Gpu::Exception::DeviceNotReady`.

### Factory Method

- Selects the concrete implementation based on the GPU_EMULATOR compile-time flag.
- Default: Returns an instance of Gpu::Emulator.

```c++
static std::unique_ptr<Interface> Interface::create();
```
