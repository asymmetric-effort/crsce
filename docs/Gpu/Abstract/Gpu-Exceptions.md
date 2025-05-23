`Gpu::Exceptions`
=================

## Purpose

This module defines exception types used throughout the CRSCE GPU abstraction framework to enforce lifecycle guarantees,
safe memory access, and reliable runtime behavior.

## Exception Types

| Exception Name                    | Description                                                                                                |
|-----------------------------------|------------------------------------------------------------------------------------------------------------|
| `Gpu::Exceptions::DeviceNotReady` | Thrown when any GPU operation is invoked before `init()` or after `shutdown()`. Ensures correct lifecycle. |
| `Gpu::Exceptions::KernelNotFound` | Thrown when a kernel ID is not found in the `Gpu::KernelManager`. Prevents invalid task launches.          |

## Usage

All exceptions derive from `std::runtime_error` and include detailed diagnostic messages when thrown.

```cpp
throw Gpu::Exceptions::DeviceNotReady("called before init()");
throw Gpu::Exceptions::KernelNotFound("kernel ID not found");
```

## Notes

- Exception throwing is the **preferred error handling** method for all terminal API misuse.
- Transient errors (e.g., bad pointer or pipe state) may return `Gpu::Ipc::FailureCodes` instead of throwing.
