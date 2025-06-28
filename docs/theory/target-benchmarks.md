Target Benchmarks
=================

The following table summarizes the compression rate and processing times per block on an 8‑core Intel i7 @ 3.5 GHz with
64 GB RAM (no memory‐capacity bottleneck assumed):

| **Block Size** $s$ | **Compression Rate** $C_r$ | **Compression Time (ms)** | **Decompression Time (ms)** |
|:------------------:|:--------------------------:|:-------------------------:|:---------------------------:|
|        512         |          42.97 %           |          0.00936          |            4.79             |
|        1024        |          73.12 %           |          0.0374           |            38.3             |
|        2048        |          90.54 %           |          0.1498           |            306.8            |
|        4096        |          92.58 %           |          0.5992           |            2455             |


## Mathematical Rigor and Derivations

1. **Compression Rate**:

   $$
   C_r = \Bigl(1 - \frac{4 s b + 256 s}{s^2}\Bigr) \times 100\%,
   $$

   where $b = \lceil \log_2 s \rceil$ is the cross‑sum bit‑width. This formula captures the ratio of payload bits to
   total bits per block.

2. **Throughput Assumption**:

    * CPU: 8 cores @ 3.5 GHz →
      $T = 8 \times 3.5\times10^9 = 28\times10^9\text{ ops/s}.$
    * Hence, one unit‐operation time = $1/T$s ≃ $3.57\times10^{-11}$s = $3.57\times10^{-8}$ms.

3. **Time Computations**:

    * **Compression** performs $s^2$ operations:

      $$
      T_{\mathrm{comp}} = \frac{s^2}{T}\times10^3\text{ ms}.
      $$
    * **Decompression** performs $s^3$ operations:

      $$
      T_{\mathrm{decomp}} = \frac{s^3}{T}\times10^3\text{ ms}.
      $$

All computations assume linear scaling of operations and full utilization across cores, with no I/O or memory‐bandwidth
bottlenecks.
