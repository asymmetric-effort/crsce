Path-Integral QMC on GPU
========================

<script type="text/javascript"
  src="https://asymmetric-effort.com/js/mathjax/2.7.0/MathJax.js?config=TeX-AMS_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    tex2jax: {
      inlineMath: [['$','$'], ['\\(','\\)']],
      processEscapes: true},
      jax: ["input/TeX","input/MathML","input/AsciiMath","output/CommonHTML"],
      extensions: ["tex2jax.js","mml2jax.js","asciimath2jax.js","MathMenu.js","MathZoom.js","AssistiveMML.js", "[Contrib]/a11y/accessibility-menu.js"],
      TeX: {
      extensions: ["AMSmath.js","AMSsymbols.js","noErrors.js","noUndefined.js"],
      equationNumbers: {
      autoNumber: "AMS"
      }
    }
  });
</script>

## Summary

Path-Integral Quantum Monte Carlo (`PI-QMC`) is a powerful simulation technique for approximating the behavior of 
quantum systems using classical computation. In the context of CRSCE decompression, PI-QMC provides a quantum-inspired
framework for navigating the exponentially large space of binary matrices $$\{0,1\}𝑠×𝑠$$ enabling efficient 
identification of the single valid configuration that satisfies all structural and hash constraints. The approach is 
rooted in statistical physics and leverages the Suzuki–Trotter transformation, which maps a quantum system into an 
equivalent classical system with an extra dimension—known as the “imaginary time” dimension—effectively creating a 
stack of coupled replicas of the original bit matrix.

In this mapping, each bit $$𝑥_{𝑟𝑐}$$ becomes a ring of `𝑝` “Trotter slices” $$(𝑥_{𝑟𝑐}^{1},𝑥_{𝑟𝑐}^{2},...,𝑥_{𝑟𝑐}^𝑝)$$
where each slice represents a possible configuration in one discrete time layer. These slices are coupled with strong 
ferromagnetic interactions that encourage coherence across the time dimension, while intra-slice interactions encode 
the original CRSCE constraints via Ising-model terms. The result is a 3D lattice of binary spins governed by a 
Boltzmann distribution that reflects both the structural cross-sums (as classical energy terms) and quantum tunneling 
effects (via transverse field dynamics).

To simulate this system, GPU kernels perform local Metropolis updates on the Trotterized spins: each thread proposes 
flipping a bit, computes the energy change across its neighbors and Trotter slices, and accepts or rejects the flip 
with a probability dictated by the effective temperature and quantum strength. Because each spin’s update is 
independent of others (modulo Trotter coupling), the algorithm maps extremely well to the SIMD architecture of GPUs, 
with one thread per spin and minimal synchronization overhead. Over multiple sweeps, the system converges to a 
configuration that reflects the global minimum of the original Hamiltonian—ideally, the exact bit-matrix encoded in 
the compressed CRSCE block.

`PI-QMC` is particularly compelling because it simulates quantum tunneling—effectively allowing the system to “jump 
over” local minima in the energy landscape that would trap classical algorithms. This property is crucial for CRSCE, 
where the combination of hard cryptographic constraints (SHA-256 lateral hashes) and soft algebraic ones (cross-sums) 
creates a rugged solution space. While the algorithm is approximate and stochastic in nature, it tends to concentrate
probability mass around valid configurations, and repeated trials rapidly isolate the true solution. When combined with
a hash check and local refinement step, PI-QMC stands as one of the most robust and theoretically grounded 
decompression methods available for structured binary compression tasks.
