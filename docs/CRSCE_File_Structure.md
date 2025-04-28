CRSCE File Structure
====================

File Structure:
---------------

Header
-------

| pos    | desc                          |
|--------|-------------------------------|
| [0x00] | 5 bytes: "CRSCE" magic header |

Blocks (1 or more)
------------------

| pos            | desc                                               |
|----------------|----------------------------------------------------|
| [0x00]         | 5 bytes: "CRSCE" magic header                      |
| [0x05]         | LHashMatrix block 0 (512 rows × 32 bytes = 16 KiB) |
| [0x05 + 16KiB] | LSM block 0 serialized                             |
| [LSM end]      | VSM block 0 serialized                             |
| [VSM end]      | XSM block 0 serialized                             |
| [XSM end]      | DSM block 0 serialized                             | 

File Footer
-----------

| pos        | desc                 |
|------------|----------------------|
| [EOF - 16] | uint64_t BLOCK_SIZE  |
| [EOF - 8]  | uint64_t block_count |


