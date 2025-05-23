`Gpu::Ipc::FailureCodes`
========================

## Purpose

Describes the response status code of an IPC operation encoded as uint8_t

## Supporting Functions

* `<<` - ostream operator
* `std::string to_string()`

## Values:

| Result            | Value | Description     |
|-------------------|-------|-----------------|
| `Success`         | 0     | No error        | 
| `Undefined Error` | 1     | Undefined error |
