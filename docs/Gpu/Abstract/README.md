GPU Abstraction Layer Functionality
===================================

This document describes the abstract functionality provided by the Gpu::Device::Interface and its default Emulator
implementation. It serves as a reference for developers integrating GPU capabilities into the CRSCE project.

![Class Diagram](Gpu_Device_Emulator_Class_Diagram.png)

## Overview

The GPU abstraction layer isolates platform- and vendor-specific GPU APIs behind a minimal, consistent interface.
This allows:

| Feature                 | Description                                                                                   |
|-------------------------|-----------------------------------------------------------------------------------------------|
| Pluggable backends      | Swap between real GPU drivers and a mock emulator via compile-time flags.                     |
| Simplified testing      | Use the emulator to verify logic without requiring actual GPU hardware.                       |
| Incremental development | Begin with basic memory and data-transfer operations, extending to kernel dispatch as needed. |

## Related Documents

* [`Gpu::Device::Interface`](./Gpu-Interface.md)
* [`Gpu::Device::Emulator`](./Gpu-Emulator.md)
* [`Gpu::Device::Cuda`](./Gpu-Cuda.md)
* [`Gpu::Device::Roc`](./Gpu-AmdRoc.md)
* [`Gpu::Device::Metal`](./Gpu-AppleMetal.md)

