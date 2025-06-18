`Gpu::Ipc::MemoryTracker`
=========================

## Purpose

Provides an abstract pointer reference in `Gpu::Ipc::MemoryTracker` map which maps `Common::AbstractPtr` to avoid
direct memory access. When a program interacts with an abstract GPU device, it may allocate, free and read/write
data to/from memory on that device.  `Gpu::Ipc::MemoryTracker` allows these operations to occur safely without
direct memory reference using pseudo-random "addresses" in the `Gpu::Ipc::MemoryTracker` table which map to actual
memory objects (address and size)

## Dependencies

* [`Common::AbstractPtr`](Common-AbstractPtr.md)

## Properties

| Property | Type                                                          | Description              |
|----------|---------------------------------------------------------------|--------------------------|
| `table`  | `std::unordered_map<Common::AbstractPtr, AllocationMetadata>` | Memory tracking table    |
| `lock`   | `std::mutex`                                                  | A lock for thread safety |

### Notes

* `AllocationMetadata` is defined internally as a struct containing the following fields:

  | Field   | Type   | Description                         |
  |---------|--------|-------------------------------------|
  | Address | void*  | Starting address of a memory object |
  | Size    | size_t | Size of the memory object           |

## Constructor

Initialize an internal random number generator

## Destructor

Cleanup any allocated resources.

## Methods

| Scope    | Method                                              | Description                                                              |
|----------|-----------------------------------------------------|--------------------------------------------------------------------------|
| `public` | `Common::AbstractPtr insert(void* ptr, size_t sz);` | insert an allocated memory object reference and return the reference id. |
| `public` | `bool erase(Common::AbstractPtr& ptr);`             | delete an allocated memory object reference.                             |
| `public` | `bool contains(Common::AbstractPtr& ptr);`          | return true if table contains the memory reference.                      |
| `public` | `size_t size(Common::AbstractPtr& ptr);`            | return the size of a memory reference.                                   |
| `public` | `void clear()`                                      | clear all internal state                                                 |

### Notes

* The `insert()` method should return `0` on null `ptr` or on error and a non-zero random memory reference index otherwise.
* The `erase()` and `contain()` methods returns `true` on success or `false` on error.
