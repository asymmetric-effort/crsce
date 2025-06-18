Kernel Blob Binary Format
=========================

## Purpose

This document defines the on-wire binary format of a kernel "blob" used in `Gpu::Device::Emulator`. These blobs encode emulated GPU kernels, which are executed by `Gpu::ThreadRuntime` on detached threads within the mock GPU child process.

## Scope

- Defines layout, field types, and endianness
- Ensures deterministic, cross-platform decoding
- Enables consistent interpretation during `launchTask()`

---

## Overview

A kernel blob is a **binary program** sent during `registerKernel()` and later executed via `launchTask()`. It consists of:

1. A **fixed-size header**
2. One or more **instruction blocks**
3. An **optional metadata trailer** (e.g., checksum)

All fields are encoded in **little-endian** byte order and must be fully aligned (no padding).

---

## Binary Layout

### Blob Structure

```c++
[Header][Instruction Block 0][...][Instruction Block N][Trailer]
```


### Header (16 bytes)

| Offset | Field         | Type      | Size | Description                              |
|--------|---------------|-----------|------|------------------------------------------|
| 0x00   | `magic`       | `uint32_t`| 4 B  | Magic number: `0xB105B105`               |
| 0x04   | `version`     | `uint16_t`| 2 B  | Format version (currently `0x0001`)      |
| 0x06   | `flags`       | `uint16_t`| 2 B  | Reserved for future use (set to `0x0000`)|
| 0x08   | `entryOffset` | `uint32_t`| 4 B  | Byte offset to first instruction         |
| 0x0C   | `instCount`   | `uint32_t`| 4 B  | Number of instruction blocks             |

---

### Instruction Block (16 bytes each)

Each instruction encodes a single virtual operation for the mock GPU thread to execute.

| Offset | Field       | Type        | Size | Description                                |
|--------|-------------|-------------|------|--------------------------------------------|
| 0x00   | `opcode`    | `uint8_t`   | 1 B  | Operation type (see Opcode Table)          |
| 0x01   | `flags`     | `uint8_t`   | 1 B  | Reserved; may control behavior or mode     |
| 0x02   | `reserved`  | `uint16_t`  | 2 B  | Must be 0                                   |
| 0x04   | `arg0`      | `uint64_t`  | 8 B  | Generic argument (e.g., address, value)     |
| 0x0C   | `arg1`      | `uint32_t`  | 4 B  | Secondary argument                          |

All instructions are 16 bytes long and tightly packed.

---

### Trailer (optional)

If present, may include:

- CRC32 or checksum
- Padding to 16-byte alignment
- Custom metadata block

This section is implementation-defined and ignored by default.

---

## Opcode Table

| Opcode (hex) | Name       | Description                                |
|--------------|------------|--------------------------------------------|
| `0x01`       | `NOP`      | No operation                               |
| `0x02`       | `WRITE8`   | Write 1 byte to memory at `arg0`           |
| `0x03`       | `WRITE64`  | Write 8 bytes to memory at `arg0`          |
| `0x04`       | `READ8`    | Read 1 byte from memory at `arg0` (debug)  |
| `0x05`       | `READ64`   | Read 8 bytes from memory at `arg0`         |
| `0x06`       | `MEMSET`   | Set `arg1` bytes at address `arg0` to zero |
| `0x07`       | `SLEEP`    | Sleep `arg1` milliseconds                  |
| `0x08`       | `HALT`     | Terminate kernel execution thread          |

---

## Validation Requirements

- Blob must begin with valid `magic` and `version`
- `entryOffset` must point to valid 16-byte-aligned instruction
- Total blob size ≥ `entryOffset + (instCount × 16)`
- Extra trailing data (e.g., metadata) is ignored by default

---

## Notes

- This format enables deterministic testing without hardware execution.
- All field sizes and offsets are fixed and endian-safe.
- Blobs are expected to be registered via `registerKernel()` and remain immutable thereafter.

---

## Future Extensions

- Instruction flags may enable loops, branching, or arithmetic.
- Trailer may be formalized as a checksum or debug symbol block.

