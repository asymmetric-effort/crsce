History of CRSCE
================

## 1993: Inception

* Inception by Sam Caldwell, as a proof-of-concept for using matrix projections to summarize binary data
  structure.
* Initial experiments focused on small block sizes (e.g. 32×32 bits) to validate compression potential via paired
  sum vectors.
* First Collisions discovered.

## 1995–2005: Algorithm Refinement

* Introduction of lateral/vertical/diagonal/anti-diagonal cross-sum matrices to capture two-dimensional
  dependencies. Collisions are still an issue. Computational complexity is the main obstacle and focus waned

## 2006–2014: Renewed Interest

* GPU/CUDA inspire new ideas for the decompression complexity problem.
* Collision issues continue.  Hash-Chain Integration: Early adoption of SHA-1-based chaining to guarantee
  integrity; collision-concerns motivated transition to SHA-256 later.
* Scalability Studies: Profiling on archival data revealed predictable compression rates but high decompression
  cost. Parallel processing prototypes on multicore and GPU systems began.

## 2015–2024: Final Stretch

* GPU Experimentation: First successful tests with CUDA shows promise. This culminates on tests against NVIDIA RTX3090.
* Collision problem is solved with SHA-256 hash chains.

## 2025: Roadmap Established

* Sam Caldwell completes course in Quantum Computing and realizes potential of QC for decompression.
* Experiments performed on AWS Braket confirm potential for QC and CRSCE decompression to solve the final complexity
  problems.
* Work begins on GPU lab to complete decompression work with future plans to extend to QC.

## Current Status

* **Compression**: Fully implemented and tested for multi-block inputs, with deterministic output sizes and
  cryptographic integrity.
* **Decompression**: Under development with iterative elimination, Radditz sieve, sift, and verification phases legacy
  processes planned for replacement with a new approach to solving for CSM.
