`Gpu::Ipc::CommandType`
=======================

## Purpose

Represents an Interprocess Communication message type encoded as `uint32_t`

## Supporting Functions / Operators

* `<<` - ostream operator
* `std::string to_string()`

## Values

| `Gpu::Ipc::CommandType` | Description                                                                     |
|-------------------------|---------------------------------------------------------------------------------|
| `Noop`                  | No operation (passive state)                                                    |
| `Init`                  | Confirms successful launch of `Gpu::Device::MockGpu` child process.             |
| `Alloc`                 | Allocate memory inside the Mock GPU. Memory is zeroed on allocation.            |
| `Free`                  | Free memory previously allocated inside the Mock GPU. Memory is zeroed on free. |
| `Write`                 | Write data to previously allocated memory.                                      |
| `Read`                  | Read data from previously allocated memory.                                     |
| `RegisterKernel`        | Register a given binary blob as a kernel which can be executed.                 |
| `LaunchTask`            | Launch a task on the kernel as an asynchronous thread.                          |
| `Reset`                 | Reset the state of the `Gpu::Device::MockGpu`.                                  |
| `Shutdown`              | Shutdown the `Gpu::Device::MockGpu`.                                            |
