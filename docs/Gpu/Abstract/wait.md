GPU Wait Semantics
==================

This document describes how `Interface::wait()` behaves across different GPU backends.

## Implementation of `wait()`

- **Emulator**: blocks until all IPC‐sent commands have been processed by the child process, but does _not_ terminate
  the child. Returns `0` on success.
- **CUDA**: wraps `cudaDeviceSynchronize()`, returning the CUDA error code.
- **OpenCL**: wraps `clFinish(queue)`, returning its error code.
- **Metal**: wraps each command buffer’s `waitUntilCompleted()` and checks for errors via callbacks or status.

<table>
    <thead>
        <tr>
            <th>Feature</th>
            <th>CUDA (`cudaDeviceSynchronize`)</th>
            <th>OpenCL (`clFinish`)</th>
            <th>Metal (`waitUntilCompleted`)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Purpose</td>
            <td>Waits for all previously issued work on the current device to complete.</td>
            <td>Blocks until all commands in a specific command queue finish.</td>
            <td>Blocks until a committed command buffer completes execution on the GPU.</td>
        </tr>
        <tr>
            <td>Context Lifetime</td>
            <td>Context remains valid; can launch more kernels and transfers afterward.</td>
            <td>Context and command queue remain valid for further use. </td>
            <td>`MTLDevice` and `MTLCommandQueue` remain active; can enqueue new buffers.</td>
        </tr>
        <tr>
            <td>Resource Retention</td>
            <td>Device memory and modules persist. </td>
            <td>Buffers and kernel objects persist.</td>
            <td>Buffers and pipeline states persist.</td>
        </tr>
        <tr>
            <td>Tear-down</td>
            <td>Separate call `cudaDeviceReset()` needed to destroy context. </td>
            <td>Release `cl_command_queue` / `cl_context` manually.</td>
            <td>Release or drop references to `MTLCommandQueue` / `MTLDevice` as needed.</td>
        </tr>
    </tbody>
</table>
