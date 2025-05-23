# GPU Abstraction Layer Unit Tests

All test programs reside in `/test/0100_` and use the `utils/test/Tester` harness. Each test case is implemented in its
own `.cpp` file for modularity and traceability.

---

## IPC Subsystem (0110)

| Test File                         | Description                                                           |
|-----------------------------------|-----------------------------------------------------------------------|
| `0110_message_roundtrip.cpp`      | `Gpu::Ipc::Message` serialize / deserialize round-trip                |
| `0110_response_roundtrip.cpp`     | `Gpu::Ipc::Response` serialize / deserialize round-trip               |
| `0110_comm_send_recv.cpp`         | Send/recv validation for `Message` and `Response`                     |
| `0110_comm_shutdown_behavior.cpp` | `recv()` after shutdown or pipe closure                               |
| `0110_comm_partial_recv.cpp`      | Simulated short read or truncated payload                             |
| `0110_comm_access_control.cpp`    | Validate role-based access enforcement (`isParent`, `isChild`)        |
| `0110_comm_lifecycle.cpp`         | Repeated init/shutdown cycles, dangling pipe behavior, `shutdownFlag` |
| `0110_failurecodes_enum.cpp`      | `FailureCodes` enum coverage                                          |
| `0110_result_enum.cpp`            | `Result` enum behavior and exhaustiveness                             |

---

## Memory and Kernel Management (0120)

| Test File                            | Description                                                              |
|--------------------------------------|--------------------------------------------------------------------------|
| `0120_memtracker_basic.cpp`          | `alloc()`, `free()`, `read()`, `write()` correctness                     |
| `0120_memtracker_invalid.cpp`        | Read/write/free with unknown or stale pointers                           |
| `0120_memtracker_clear.cpp`          | `clear()` purges all, including full overwrite of buffer contents        |
| `0120_memtracker_leak_check.cpp`     | Ensure no retained pointers or dangling maps after `clear()` or shutdown |
| `0120_kernelmanager_basic.cpp`       | `register`, `has`, `get`, `erase`, `clear()`                             |
| `0120_kernelmanager_missing.cpp`     | `get()` and `erase()` throw on missing kernel ID                         |
| `0120_threadregistry_basic.cpp`      | Single-thread insert and join                                            |
| `0120_threadregistry_concurrent.cpp` | Threaded stress test for `insert()` and `joinAll()`                      |
| `0120_threadruntime_valid.cpp`       | Run valid kernel blob                                                    |
| `0120_threadruntime_corrupt.cpp`     | Detect invalid header in binary blob                                     |

---

## Matrix and Math (0130)

| Test File                   | Description                                                             |
|-----------------------------|-------------------------------------------------------------------------|
| `0130_matrix_shape.cpp`     | Constructor, `rows()`, `cols()`                                         |
| `0130_matrix_at.cpp`        | `at()` value assignment, indexing, bounds checking                      |
| `0130_matrix_data.cpp`      | `data()` round-trip consistency                                         |
| `0130_matrix_device_io.cpp` | Matrix written to emulator and re-read correctly via `write()`/`read()` |

---

## Emulator Infrastructure (0140)

| Test File                          | Description                                                  |
|------------------------------------|--------------------------------------------------------------|
| `0140_emulator_lifecycle.cpp`      | `init()`, `shutdown()`, `reset()`, and safe reuse            |
| `0140_emulator_alloc_io.cpp`       | `alloc()`, `free()`, `read()`, `write()` verified end-to-end |
| `0140_emulator_kernel.cpp`         | Register kernel, launch task, validate IPC thread            |
| `0140_emulator_shutdown_guard.cpp` | `shutdown()` multiple times, or after `reset()`              |
| `0140_mockgpu_dispatch.cpp`        | Loop dispatch for known commands                             |
| `0140_mockgpu_invalid_command.cpp` | Unknown `CommandType` behavior                               |
| `0140_runtimemanager_dispatch.cpp` | Each handler tested with a valid message                     |
| `0140_runtimemanager_invalid.cpp`  | Missing kernel ID, allocation failure, etc.                  |

---

## Interface Compliance (0150)

| Test File                      | Description                                                      |
|--------------------------------|------------------------------------------------------------------|
| `0150_interface_typecheck.cpp` | Ensure `Emulator`, `Cuda`, `Roc`, `Metal` conform to `Interface` |
| `0150_cuda_stub.cpp`           | All operations return expected stub values                       |
| `0150_roc_stub.cpp`            | Stub method tests for AMD ROC backend                            |
| `0150_metal_stub.cpp`          | Stub method tests for Apple Metal backend                        |

---
