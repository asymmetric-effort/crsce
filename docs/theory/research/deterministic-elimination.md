Deterministic Elimination
=========================

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

Deterministic Elimination (DE) is the foundational first step in CRSCE decompression. It applies exact, algebraic
rules to infer bit values from the cross-sum constraints without any need for search or probability. The simplest
cases—where a row, column, diagonal, or anti-diagonal has a sum of 0 or s—immediately yield all-0 or all-1 assignments
for that line. However, DE becomes significantly more powerful when extended to include partial-line inference: for
example, if all but one bit in a constraint line are known, the final bit must take the value required to satisfy the
sum. Similarly, bits that participate in multiple nearly-complete constraints can often be resolved through
overdetermined consistency checks.

A full implementation of DE operates as a fixed-point propagator, iteratively applying all such inference rules until
no new bits can be determined. These include one-free-line resolution, two-bit feasibility cases, and elimination of
infeasible states from overlapping constraints. Each new bit inferred can trigger additional constraints to become
saturated, leading to further deductions. This cascaded propagation is extremely efficient—operating in linear time
over the constraint graph—and often solves a large majority of the matrix before any stochastic or search-based
methods are required.

Because it reduces the search space without error and without cost, DE is not only the first step but the most
critical preprocessing phase in any decompression pass. Every subsequent algorithm—belief propagation, sieve, sampling,
or annealing—depends on the clarity and compression of the solution space that DE enables.

## Step-by-Step: Deterministic Elimination

1. Initialize all bits as unknown. Begin with an empty 𝑠×𝑠 Cross Sum Matrix (CSM) where all bits are unset (unknown).
2. Scan LHASH for any hash value representing the 50% CSM patterns 01010... or 101010... and resolve them accordingly.
3. Scan each row, column, diagonal, and anti-diagonal For each line, retrieve its target sum from the compressed
   metadata (LSM, VSM, DSM, XSM).
4. Apply the trivial cases
   1. If a line’s sum is 0, set all its bits to 0.
   2. If a line’s sum is 𝑠, set all its bits to 1.
   (NOTE: These cases are exact and require no further inference.)
5. Apply 1-free-bit resolution
   1. If a line has exactly one unknown bit and the rest are known, solve for the missing bit by subtracting the
      known values from the target sum.
   2. Update all affected constraints. Every time a bit is filled, re-check all constraints that involve it (its row,
      column, diag, anti-diag).
6. Repeat until stable. Keep applying steps 3–5 until no new bits can be determined. This loop converges quickly in
   practice.
7. Check for inconsistencies. If at any point a constraint cannot be satisfied (e.g. remaining unknown bits cannot
   sum to the required value), mark the block as invalid.

## Result

After DE finishes, all bits that can be deduced with certainty are filled in. The remaining unknowns are those that
require search, inference, or probabilistic methods to resolve.
