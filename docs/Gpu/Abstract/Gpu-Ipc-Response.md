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

## Methods

| Method        | Returns                | Arguments                        | Description                                   |
|---------------|------------------------|----------------------------------|-----------------------------------------------|
| `serialize`   | `std::vector<uint8_t>` | None                             | serialize class data to a binary blob         |
| `deserialize` | void                   | `uint8_t *buffer, size_t length` | deserialize binary buffer into internal state |
