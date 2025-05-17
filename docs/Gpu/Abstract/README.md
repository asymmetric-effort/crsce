GPU Abstraction Layer Functionality
===================================

This document describes the abstract functionality provided by the Gpu::Interface and its default Emulator
implementation. It serves as a reference for developers integrating GPU capabilities into the CRSCE project.

## Overview

The GPU abstraction layer isolates platform- and vendor-specific GPU APIs behind a minimal, consistent interface.
This allows:

- Pluggable backends: Swap between real GPU drivers and a mock emulator via compile-time flags.
- Simplified testing: Use the emulator to verify logic without requiring actual GPU hardware.
- Incremental development: Begin with basic memory and data-transfer operations, extending to kernel dispatch as needed.

## Interface Methods

All methods belong to the Gpu::Interface abstract base class:

| Method                                                          | Description                                                                                                    |
|-----------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------|
| bool init()                                                     | Initialize the GPU device or emulator. Should be called once before any other operations.                      | 
| void* allocBuffer(std::size_t bytes)                            | Allocate a contiguous block of bytes on the GPU (or emulator). Returns a device pointer or nullptr on failure. | 
| bool freeBuffer(void* ptr)                                      | Free memory previously allocated with allocBuffer. Returns true on success.                                    | 
| bool writeBuffer(void* dst, const void* src, std::size_t bytes) | Copy bytes from host memory (src) into device memory (dst).                                                    | 
| bool readBuffer(void* dst, const void* src, std::size_t bytes)  | Copy bytes from device memory (src) back into host memory (dst).                                               | 

## Factory Method
```c++
static std::unique_ptr<Interface> Interface::create();
```

- Selects the concrete implementation based on the GPU_EMULATOR compile-time flag.
- Default: Returns an instance of Gpu::Emulator.

## Emulator Implementation

The Emulator class in Gpu::Device provides an in-memory simulation of GPU behavior:

- Memory allocation: Uses std::malloc/std::free to simulate device memory.
- Data transfer: Implements writeBuffer and readBuffer via std::memcpy.
- Initialization: Logs a success message to stdout.

## Example: HelloWorld Round-Trip
The 0200_Gpu_HelloWorld.cpp test demonstrates minimal functionality:

1. Initialize the emulator (init()).
2. Allocate a buffer for the string "Hello, GPU!".
3. Write the string to emulator memory.
4. Read it back into a host buffer.
5. Free the emulator buffer.
6. Verify the returned string matches the original.

## Extension Points

Future GPU backends (e.g., NVIDIA CUDA, AMD ROCm, Apple Metal) should implement Gpu::Interface:

- Map allocBuffer/freeBuffer onto the respective API calls.
- Implement writeBuffer/readBuffer with the vendor’s host-device transfer routines.
- Add kernel dispatch methods, e.g., launchKernel(...), once basic memory operations are proven.

## File Locations
- Headers: include/Gpu/Interface.h, include/Gpu/Device/Emulator.h
- Source: src/Gpu/Gpu_create.cpp, src/Gpu/Device/Emulator.cpp
- Tests: test/0200_Gpu_HelloWorld.cpp

---
(c) 2025 Asymmetric Effort, LLC. scaldwell@asymmetric-effort.com

