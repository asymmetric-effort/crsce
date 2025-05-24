`Gpu::Ipc::Message`
===================

## Purpose

Represents a message sent from parent to child via IPC. This type defines the serialized binary and deserialized
class format of the IPC Message along with methods to facilitate serialization and deserialization.

## Properties

| Property   | Type                    | Description                                           |
|------------|-------------------------|-------------------------------------------------------|
| `type`     | `Gpu::Ipc::CommandType` | Command type (enum CommandType encoded as `uint32_t`) |
| `kernelId` | `uint32_t`              | Used only for LaunchTask                              |
| `size`     | `uint64_t`              | Size of buffer (for Alloc/Write/Read)                 |
| `ptr`      | `uint64_t`              | Device memory address or handle                       |

### Notes

* Struct must not contain padding, and implementation must enforce correct alignment or use #pragma pack
  or static_assert(sizeof(...)) checks.
* Endianness must be explicitly little-endian in implementation, matching platform pipes and memory format.
* The properties are serialized as `type``kernelId``size``ptr`

## Methods:

| Method        | Returns           | Arguments               | Description                                     |
|---------------|-------------------|-------------------------|-------------------------------------------------|
| `serialize`   | `Common::Buffer8` | None                    | serialize class data to a binary blob           |
| `deserialize` | `void`            | `Common::Buffer8& data` | deserialize a binary buffer into internal state |

