Radditz Sieve
=============

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

Radditz Sieve is a deterministic decompression pipeline originally developed by Sam Caldwell in 1995 which was
extended in 2014 to use GPUs.  It begins with the elimination of bits in rows, columns, diagonals, and anti-diagonals
whose cross-sums are 0 or maximal (s). After this preprocessing, a massively parallel Radditz Sieve attempts to
incrementally prune invalid assignments by evaluating cross-sum feasibility using bitwise masks. Remaining ambiguous
bits are resolved using CPU-driven local search, focusing on bits that impact rows with failed SHA-256 hashes. Each
candidate reconstruction is then verified by recomputing and comparing lateral hashes against the compressed metadata.
This method is algorithmically robust and practically effective, but its performance deteriorates as the number of
ambiguous bits grows—scaling poorly under low-entropy inputs or deeply entangled block states. Nonetheless, it
guarantees correctness and exploits both GPU and CPU effectively.
