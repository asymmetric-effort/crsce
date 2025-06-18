`Gpu::Ipc::Result`
==================

## Purpose

Represents the result of an IPC operation.

## Supporting Functions

* `<<` - ostream operator
* `std::string to_string()`

## Values

| Result     | Value | Description                           |
|------------|-------|---------------------------------------|
| `Success`  | 0     | Operation completed successfully      |
| `Empty`    | 1     | No message in queue to read           |
| `Blocked`  | 2     | Receiver is not ready or pipe is full |
| `Shutdown` | 3     | IPC channel is shut down              |
| `Error`    | 4     | System-level or internal error        |
