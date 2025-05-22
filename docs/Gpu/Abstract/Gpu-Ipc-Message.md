`Gpu::Ipc::Message`
===================

## Purpose

Represents a message sent from parent to child via IPC.

## Properties

| Property   | Type                    | Description                                           |
|------------|-------------------------|-------------------------------------------------------|
| `type`     | `Gpu::Ipc::CommandType` | Command type (enum CommandType encoded as `uint32_t`) |
| `kernelId` | `uint32_t`              | Used only for LaunchTask                              |
| `size`     | `uint64_t`              | Size of buffer (for Alloc/Write/Read)                 |
| `ptr`      | `uint64_t`              | Device memory address or handle                       |

## Methods:

| Method        | Returns                | Arguments                        | Description                                     |
|---------------|------------------------|----------------------------------|-------------------------------------------------|
| `serialize`   | `std::vector<uint8_t>` | None                             | serialize class data to a binary blob           |
| `deserialize` | `Message`              | `uint8_t* data`, `size_t length` | deserialize a binary buffer into internal state |

