`Gpu::ThreadRegistry`
=====================

## Purpose

The `Gpu::ThreadRegistry` class tracks the lifecycle of GPU kernel execution threads in the CRSCE emulator backend. It provides a thread-safe registry for inserting, joining, and clearing threads, enabling safe concurrent execution and orderly shutdown.

## Role in Architecture

- Owned by `Gpu::RuntimeManager`.
- Each call to `handleLaunchTask()` creates a detached thread to run a kernel.
- That thread is inserted into `ThreadRegistry` and can be joined later during `reset()` or `shutdown()`.

## Thread Lifecycle Responsibility

- **Insert:** Track newly launched threads by launch ID.
- **Join:** Wait for all active threads to complete execution.
- **Clear:** Empty registry after join or forced reset.

## Dependencies

* `<thread>`
* `<unordered_map>`
* `<mutex>`
* `<atomic>`

## Properties

| Property    | Type                                            | Description                              |
|-------------|--------------------------------------------------|------------------------------------------|
| `threads`   | `std::unordered_map<uint32_t, std::thread>`     | Map of launch ID → thread                |
| `mutex`     | `std::mutex`                                    | Guards all access to internal map        |

---

## Methods

### `void insert(uint32_t launchId, std::thread&& t)`

Inserts a new thread into the registry.
- Launch ID must be unique; overwriting is forbidden.
- Acquires mutex lock for map insertion.
- Thread must not be `joinable()` after this point (transfer of ownership).

#### Failure Mode:
- If `launchId` already exists, abort (or assert in debug builds).

---

### `void joinAll()`

Joins all registered threads.
- Acquires lock.
- For each thread: if `joinable()`, invoke `join()`.
- Clears `threads` map after all joins complete.

#### Notes:
- Safe to call multiple times.
- Must not be called concurrently with `insert()`.

---

### `void clear()`

Clears all entries from the map without joining.
- Used for emergency reset when thread state is no longer needed or safe to join.
- Assumes all threads are already joined (or discarded).

---

### `bool empty() const`

Returns `true` if no threads are currently registered.

---

## Thread Safety

- All methods are **fully mutex-guarded**.
- Safe to call `insert()` from multiple launching threads, but external serialization is recommended for kernel coordination.
- `joinAll()` and `clear()` must be called only once at shutdown/reset.

---

## Usage Pattern

```cpp
Gpu::ThreadRegistry registry;
registry.insert(42, std::thread(some_kernel));
...
registry.joinAll();
registry.clear();  // safe for reuse
