Loopy Belief Propagation (Loopy BP)
===================================

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

Loopy Belief Propagation (Loopy BP) is a message-passing algorithm used to perform approximate inference on graphical
models with cycles. In the context of CRSCE decompression, it offers a highly parallelizable and probabilistically
grounded method for solving for unknown bit values within a large, densely constrained matrix. Each bit `𝑥_{𝑟𝑐}∈{0,1}`
in the Cross Sum Matrix (CSM) is treated as a variable node, and each constraint—row sum, column sum, diagonal sum,
and anti-diagonal sum—is modeled as a factor node in a bipartite factor graph. These factors enforce that subsets of
bits must sum to a fixed integer, based on the compressed block’s metadata.

The core idea of Loopy BP is to iteratively exchange “beliefs” (probability distributions) between variable and
factor nodes. Each belief captures the probability that a variable takes on a specific value, conditioned on the
rest of the system. Initially, all variables are assumed to be uniformly uncertain. In each round of message passing,
variable nodes update their beliefs based on messages received from connected factors, and factor nodes recompute
expectations based on the sum constraints and messages from variables. These messages are updated simultaneously in
parallel and refined over multiple iterations.

Although exact belief propagation is guaranteed to converge only in tree-structured graphs (without cycles), empirical
results over the past two decades have shown that Loopy BP often converges to useful—and often optimal—solutions even
in loopy graphs. For CRSCE, the structured nature of the constraints (uniform size, high connectivity, and
deterministic binary outputs) makes the factor graph highly regular and well-suited for convergence in practice.
Because each message-passing update is local and structurally identical, the algorithm is highly efficient to implement
on GPUs, allowing one to process entire CRSCE blocks in parallel across thousands of threads. Once convergence is
reached, variables with high-confidence beliefs can be fixed deterministically, and the solution can be verified
against the lateral hashes. If needed, low-confidence bits can be refined with local search or branch-and-bound
polishing.

Loopy BP offers an elegant compromise between brute-force search and deterministic algebraic solving: it uses global
probabilistic coherence to eliminate large swaths of the solution space, yet remains computationally tractable
through parallel approximation.







