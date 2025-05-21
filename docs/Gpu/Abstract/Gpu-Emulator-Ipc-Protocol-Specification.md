GPU Emulator IPC Protocol Specification
=======================================

## Overview

This protocol governs all message-based communication between the **parent process** (controller/test harness) and
the **child process** (`GPU::Emulator`) via **unidirectional Unix pipes** established at fork.

It defines:
- Message formats
- Command lifecycle
- Serialization protocol
- Expected handler behavior

## Class Implementation
This protocol is implemented in the GPU Abstraction Layer (`Gpu::Interface`) by the concrete GPU Implementations,
including `Gpu::Emulator` class.

## Pipe Setup

### During `Emulator::init()`

Two pipes are created (as properties of `Emulator` class):

| Pipe Array         | Direction      | Used By                             |
|--------------------|----------------|-------------------------------------|
| `pipeToChild[2]`   | Parent → Child | Command write pipe (`toChildFd_`)   |
| `pipeFromChild[2]` | Child → Parent | Response read pipe (`fromChildFd_`) |

These become:

- **In parent:**
  ```cpp
  toChildFd_   = pipeToChild[1];    // write-end
  fromChildFd_ = pipeFromChild[0];  // read-end

- **In child:**

```
toChildFd_   = pipeToChild[0];    // read-end
fromChildFd_ = pipeFromChild[1];  // write-end
```

## Message Flow

- Parent sends a serialized IpcHeader to toChildFd_.
- Child reads the IpcHeader, dispatches to the matching handler.
- Handler optionally sends an IpcResponseMsg to fromChildFd_.
- Parent reads and deserializes the IpcResponseMsg.

## Command Header Format (IpcHeader)

```c++
struct IpcHeader {
    CommandType type;   // Enum value (uint32_t)
    uint32_t kernelId;  // For LaunchTask
    uint64_t size;      // Allocation size or buffer size
    uint64_t ptr;       // Device memory pointer (from previous Alloc)
};
```

This structure is sent raw using `write(toChildFd_, &hdr, sizeof(hdr))`

## Response Format (IpcResponseMsg)

All responses use a strict binary format:

```c++
[ status (1 byte) | size (8 bytes LE) | payload (size bytes) ]
```

## Structure

```c++
class IpcResponseMsg {
public:
uint8_t status = 1;  // 0 = success, nonzero = error code
uint64_t size = 0;   // size of payload
std::vector<uint8_t> data;
    // IpcResponseMsg(uint8_t status, const void* payload, uint64_t size);
    std::vector<uint8_t> serialize() const;
    static IpcResponseMsg deserialize(const uint8_t* buffer, size_t length);
};
```

### Examples

* Init, Free, Reset: status = 0, size = 0, data = {}.
* Alloc: returns 64-bit pointer payload.
* Read: returns memory contents.

## Command Types (enum class CommandType : uint32_t)

| Name       | Value | Description                         |
|------------|-------|-------------------------------------|
| Init	      | 0x01  | Handshake with child after fork     |
| Alloc      | 0x02  | Allocate device memory              |
| Free	      | 0x03  | Free previously allocated pointer   |
| Write      | 0x04  | Copy data into device memory        |
| Read	      | 0x05  | Read back data from device memory   |
| LaunchTask | 0x06  | Launch a kernel task                |
| Reset      | 0x07  | Free all allocations                |
| Wait	      | 0x08  | Parent waits for child to terminate |
| Shutdown	  | 0x09  | Child shuts down gracefully         |

## Handler Requirements

Each handler:

* Reads from `hdr`
* Accesses or updates PointerTracker
* Sends a response via `toParentFd_` using `IpcResponseMsg::serialize()`

### Response Expectations by Command

| Command    | Response Required | Payload              |
|------------|-------------------|----------------------|
| `Init`     | Yes               | None                 |
| `Alloc`    | Yes               | `uint64_t` ptr       |
| `Free`     | Yes               | None                 |
| `Write`    | No                | N/A                  |
| `Read`     | Yes               | buffer data          |
| `Reset`    | Yes               | None                 |
| `Wait`     | Yes               | exit code or status  |
| `Shutdown` | Optional          | None (may be silent) |

## Error Handling
* Handlers return IpcResponseMsg(status=1, nullptr, 0) to indicate failure
* `receiveResponseMsg()` retries short reads and throws if deserialization fails

## Alignment with `PointerTracker`
All Alloc-managed memory must:
* Be tracked via `PointerTracker` (`std::unordered_set<void*>`)
* Be freed in `handleFree()` and `handleReset()`
* Be validated before Read/Write

## Guarantees
* IPC protocol is binary, lossless, and self-delimiting via the size field
* All commands are synchronous round-trips
* Every command (except Write) must trigger a reply
