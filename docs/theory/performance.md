Performance Estimate
====================

This document is a rough performance estimate based on an NVIDIA RTX 5090.  This is based on theory only.  It is a
pre-experiment exercise.

## Memory Transfer

| Operation                             | Time (µs)  |
|---------------------------------------|------------|
| Read 32KB from GPU memory at 1.8 TB/s | ~0.0182 µs |
| Write 32KB back                       | ~0.0182 µs |
| Total Memory time (R+W)               | ~0.0364 µs |

## Compute Work

| Operation                                                                        | Time (µs) |
|----------------------------------------------------------------------------------|-----------|
| Assume CRSCE does ~500 operations per byte -> 32KB x 500 = 16,384,000 ops        |           |
| Peak GPU throughput ~125 TFLOP/s -> ideal compute time = 16.384Mops/125e12 ops/s | 0.0131 µs |
| Realistically, if operating at ~10% of peak (inefficiency factor of 10)          | 1.2107 µs |

## Kernel Launch Overhead

| Operation                                     | Time (µs) |
|-----------------------------------------------|-----------|
| Typical CUDA kernel launch overhead ≈ 10-20µs | 15 µs     |

## End-to-End

| Operation       | Time (µs)  |
|-----------------|------------|
| Memory          | 00.0364 µs | 
| Compute         | 01.3107 µs | 
| Kernel Overhead | 15.0000 µs |
| =============== | ========== |
| Total           | 16.3471 µs |

So, for a single 32 KB block, you can expect roughly ≈ 16.3 µs end-to-end if you launch a separate kernel. 
If you batch many blocks in one kernel call, you can amortize that ~15 µs overhead across multiple blocks—pushing 
per-block time down toward ~1 µs in the best cases.

These are pre-experiment assumptions based on an RTX 5090 GPU.

## References
* [Any way to measure the latency of a kernel launch](https://forums.developer.nvidia.com/t/any-way-to-measure-the-latency-of-a-kernel-launch/221413)
* [NVIDIA RTX Blackwell GPU Architecture](https://images.nvidia.com/aem-dam/Solutions/geforce/blackwell/nvidia-rtx-blackwell-gpu-architecture.pdf?utm_source=chatgpt.com)
* [TechPowerUp: NVIDIA GeForce RTX 5090](https://www.techpowerup.com/gpu-specs/geforce-rtx-5090.c4216?utm_source=chatgpt.com)
