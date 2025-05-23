`Common::AbstractPtr`
=====================

## Purpose
The `Common::AbstractPtr` type is a `uint64_t` numeric value representing one of many pseudo-random memory references
in the `Gpu::Ipc::MemoryTracker` table.

## Definition
`using Common::AbstractPtr = uint64_t;`

## Notes
* `0` represents `nullptr` (no memory reference).
* non-zero represents an address reference.
