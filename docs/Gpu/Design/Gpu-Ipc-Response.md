`Gpu::Ipc::Response`
====================

## Purpose

Represents the response by child to client via IPC.

## Properties

| Property | Type                     | Description                                           |
|----------|--------------------------|-------------------------------------------------------|
| `status` | `Gpu::Ipc::FailureCodes` | Response exit code indicating success or error state. |
| `size`   | `uint64_t`               | Payload size in bytes                                 | 
| `data`   | `std::vector<uint8_t>`   | Optional payload buffer                               |

### Notes
* Struct must not contain padding, and implementation must enforce correct alignment or use #pragma pack
  or static_assert(sizeof(...)) checks.
* Endianness must be explicitly little-endian in implementation, matching platform pipes and memory format.
* The properties are serialized as `status``size``data`.

## Methods

| Method        | Returns                | Arguments                        | Description                                   |
|---------------|------------------------|----------------------------------|-----------------------------------------------|
| `serialize`   | `std::vector<uint8_t>` | None                             | serialize class data to a binary blob         |
| `deserialize` | void                   | `uint8_t *buffer, size_t length` | deserialize binary buffer into internal state |

### Notes
* Must validate length >= 9 (1 byte status + 8 byte size) before accessing payload.
* Must then ensure length >= 9 + size to safely populate data.
