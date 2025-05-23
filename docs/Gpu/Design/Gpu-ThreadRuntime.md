`Gpu::ThreadRuntime`
====================

## Purpose

The `Gpu::ThreadRuntime` class provides the logic for executing an arbitrary binary blob that simulates a GPU kernel
execution. It is invoked by the `Gpu::RuntimeManager` within a detached thread created during `handleLaunchTask()`.

## Role in Architecture

- Instantiated inside a detached thread spawned during `Gpu::RuntimeManager::handleLaunchTask()`.
- Receives:
    - The kernel blob (raw bytes)
    - Optional arguments (e.g., buffer sizes, dispatch dimensions)
- Executes the kernel according to emulator semantics (deterministic and bounded).
- May interact with `Gpu::Ipc::MemoryTracker` for reads/writes during execution.

## Responsibilities

- Parse kernel binary and validate preamble
- Emulate computation as encoded in binary blob (no JIT or actual hardware execution)
- Return normally upon success or raise an error condition

## Dependencies

* `Common::Buffer8` (`std::vector<uint8_t>`)
* [`Kernel Binary Blob Format`](Kernel-Binary-Blob-Format.md)

## Properties

| Property     | Type                     | Description                            |
|--------------|--------------------------|----------------------------------------|
| `kernelBlob` | `const Common::Buffer8&` | The binary blob for kernel execution   |
| `args`       | `const Common::Buffer8&` | Optional arguments (opaque to runtime) |

---

## Constructor

| Signature                                                                             |
|---------------------------------------------------------------------------------------|
| `ThreadRuntime(const Common::Buffer8& kernelBlob, const Common::Buffer8& args = {});` |

Initializes the internal state. Stores references to the kernel code and its input arguments.

---

## Methods

### `void run()`

Executes the thread's work.

- Parses the binary blob header and dispatch block.
- Executes logic encoded in blob using deterministic simulation logic.
- Terminates cleanly on success or throws on failure.
- Handles timeouts, invalid opcodes, malformed blobs gracefully (per design constraints).
- Optional: may access `Gpu::Ipc::MemoryTracker` to simulate global memory effects.

#### Notes:

- This method is the **entry point for all mock kernel threads**.
- All thread-safe or shared state (e.g., memory tracker) must be accessed via RAII or lock guards.
- Does **not** return any result to the parent; all effects must be committed via memory tracker.

---

## Thread Safety

- `Gpu::ThreadRuntime` instances are **per-thread and not shared**.
- All operations are confined to local state unless explicitly passed shared references (e.g. memory tracker).
- Safe to run many `run()` instances concurrently from multiple detached threads.

---

## Kernel Blob Format (Abstract)

The kernel binary blob may include:

- **Header**: Version info, opcodes, dispatch dimensions
- **Program**: Encoded operations
- **Footer**: Checksum or padding (if required)

Binary interpretation logic is implemented in `run()`, and may be extended for structured execution (e.g., virtual
instruction set simulation).

---

## Failure Handling

- `run()` may throw:
    - `std::runtime_error` on malformed blob
    - Custom exceptions (if implemented) on opcode or memory violations
- All exceptions should be caught and logged by the parent thread wrapper if necessary

---

## Example Usage

```cpp
auto t = std::thread([] {
    Gpu::ThreadRuntime rt(kernelBlob, args);
    rt.run();
});
registry.insert(launchId, std::move(t));
```

## Lifecycle Summary

| Phase   | Activity                          |
|---------|-----------------------------------|
| Launch  | Constructed in detached thread    |
| Execute | `run()` processes kernel blob     |
| Exit    | Thread completes or fails cleanly |

