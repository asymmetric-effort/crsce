`Gpu::KernelManager`
====================

## Purpose

The `Gpu::KernelManager` class manages the storage and retrieval of kernel binary blobs that have been pre-registered by
software using `Gpu::Device::Interface::registerKernel()`. It provides a consistent API to insert and look up kernels by
a unique kernel ID (`Gpu::KernelId`), supporting deferred execution via `launchTask()`.

## Role in Architecture

- **Owned by `Gpu::RuntimeManager`**
- Used during:
    - `registerKernel()` — stores a named kernel blob
    - `launchTask()` — retrieves and dispatches a kernel for execution

## Dependencies

* `Common::Buffer8` (`std::vector<uint8_t>`)
* `Gpu::KernelId` (`uint64_t`)
* `<unordered_map>`, `<mutex>`

## Properties

| Property  | Type                                            | Description                  |
|-----------|-------------------------------------------------|------------------------------|
| `kernels` | `std::unordered_map<KernelId, Common::Buffer8>` | Maps kernel ID → binary blob |
| `mutex`   | `std::mutex`                                    | Protects concurrent access   |

---

## Type Aliases

```cpp
using Gpu::KernelId = uint64_t;
```

## Methods

| Scope    | Method           | Return                   | Argument                                     | Description                                                            | 
|----------|------------------|--------------------------|----------------------------------------------|------------------------------------------------------------------------|
| `public` | `registerKernel` | `bool`                   | `KernelId id, const Common::Buffer8& binary` | Registers a kernel blob under a unique id.                             |
| `public` | `has`            | `bool`                   | `KernelId id`                                | Checks whether a given kernelId is present in the registry.            |
| `public` | `get`            | `const Common::Buffer8&` | `KernelId id`                                | Returns a readonly reference to the kernel blob associated with the id |
| `public` | `clear`          | `bool`                   | `void`                                       | Clear all registered kernel blobs.                                     |
| `public` | `erase`          | `bool`                   | `KernelId id`                                | erase a given registered blob                                          |

### Notes

* blob objects are immutable. This means the entire blob must be copied and each change overwrites the previous
  entirely. Overwrite is always allowed. The boolean return only reflects success/failure on insertion.
* All methods are thread safe. All access to the internal map is guarded by std::mutex.
* Unless otherwise implied or provided, a boolean response means true for success or false for error.
* `get()` and `erase()` throw `Gpu::Exceptions::KernelNotFound` if it does not exist.
* `erase()` and `clear()` will securely delete any blob by first overwriting the data with random bytes.

## Example Usage
```c++
Gpu::KernelManager km;
km.registerKernel(42, binaryBlob);

if (km.has(42)) {
    const auto& blob = km.get(42);
    Gpu::ThreadRuntime rt(blob);
    rt.run();
}
```
