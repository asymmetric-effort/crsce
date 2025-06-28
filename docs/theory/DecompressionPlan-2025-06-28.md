# CRSCE GPU Decompression Implementation Plan

## Summary of Decisions

| Item                      | Decision / Default                                                 |
| ------------------------- | ------------------------------------------------------------------ |
| **GPU Framework**         | CPU-only → Metal (macOS MVP)                                       |
| **Code Baseline**         | Implement CPU-only first                                           |
| **Performance Goal**      | ≤ 0.16 ms per 32 KB block single-threaded (200 MB/s), ≤ 1 ms worst |
| **Hashing Strategy**      | SHA-256 verification on CPU (CommonCrypto/OpenSSL)                 |
| **Concurrency Model**     | CPU: C++20 Parallel STL; GPU: threadgroups & grids in Metal/etc    |
| **Belief & CA Params**    | **T=16**, **R=100** (runtime-tunable via `CRSCEParams`)            |
| **Memory & Batching**     | Runtime-configurable `batchSize`, blocks processed independently   |
| **Integration & Testing** | Use existing `test/` directory, CMake targets, and GitHub CI/CD    |

## Proposed Work Plan (Dependency Order)

1. **API & Data Structures**

    * Define `CRSCEParams { s, T, R }` and `batchSize` in `crsce_cpu_decoder.h`
    * Add `decompressBlocks` API for batch processing

2. **Bit-Unpacking & Packing Module**

    * Implement routines to unpack compressed bytes into a bit-grid
    * Implement routines to pack the grid back into bytes
    * Unit tests for round-trip on fixed test vectors

3. **Deterministic Elimination (DE)**

    * Implement four-pass DE logic over rows, columns, diagonals, anti-diagonals
    * Parallelize using C++20 Parallel STL
    * Tests for DE on synthetic grids

4. **Game-of-Beliefs (GOBP)**

    * Initialize message buffers and variable/factor graph construct
    * Implement LBP for `T` iterations with parallel update
    * Tests validating convergence on small examples

5. **Cellular Automaton (CA)**

    * Implement `R` rounds of row-local CA bit-moves
    * Parallelize per-row via Parallel STL
    * Integration tests with GOBP to ensure combined correctness

6. **Row-Hash Verification**

    * Hook up CommonCrypto/OpenSSL SHA-256 per-row
    * Validate against stored hashes in compressed data
    * Tests for integrity-check failures and successes

7. **Benchmarking & Performance Measurement**

    * Benchmark single-block performance vs. gzip/bzip2/LZMA on CPU
    * Tune parameters or parallelization strategy to meet ≤0.16 ms target

8. **Metal Port Preparation**

    * Extract compute algorithms into portable functions
    * Sketch Metal parameter-driven kernels and threadgroup config
    * Prepare build pipeline (Xcode/SwiftPM) for `.metal` files

## Discussion

Throughout our discussion, we aligned on a dual-phase implementation strategy to balance development speed, 
correctness, and future-proofing:

* **CPU-First Reference**:
                           Establishes a correctness baseline and performance metrics without GPU debugging complexity.
                           By using C++20 Parallel STL, we achieve parallelism mirroring the GPU model with minimal 
                           code churn.

* **Metal for macOS MVP**: 
                           Offers native support on our hardware (AMD Radeon Pro 5500M or Apple M\*) and leverages 
                           Apple’s robust tooling. We consolidate GPU efforts into Metal first, then expand to other 
                           GPU platforms.

* **Parameter Exposure**: Exposing key algorithmic parameters (`s, T, R, batchSize`) at runtime ensures we can 
                          experiment and optimize actual performance rather than rely on theoretical defaults. 
                          Defaults of `T=16` and `R=100` balance convergence quality with compute overhead.

* **Performance Goals**: 
                         Targeting ≤0.16 ms per 32 KB block single-threaded aligns us with gzip-level throughput 
                         (200 MB/s). Multi-threaded CPU scaling aims to keep worst-case block times under 1 ms, 
                         positioning CRSCE as competitive with classic algorithms.

* **Scalability & Maintainability**: 
                         Treating blocks as independent units with a configurable batch size simplifies both CPU and 
                         GPU implementations. This design scales from single-block debugging to high-throughput 
                         pipelines without architectural changes.

By following this structured plan, we minimize risk, ensure correctness, and establish a clear path toward a 
performant GPU-based decompressor for CRSCE.
