Decompression Options
=====================

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

<p>
<a href="deterministic-elimination.md">"Deterministic Elimination"</a> is a pretty obvious first step in the process. 
But Radditz Sieve and local search are inefficient, expensive (time and energy). We need better options.
</p>

Below is a table of options:
<table>
  <thead>
    <tr>
      <th>Option</th>
      <th>Description</th>
      <th>Algorithmic Fit</th>
      <th>GPU Maturity</th>
      <th>Convergence</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><a href="Radditz-Sieve.md">Radditz Sieve</a></td>
      <td>
        Deterministic elimination, massively parallel sieve on GPU, CPU-thread sift, and GPU SHA-256 verification 
        in one combined pipeline.  This is the original algorithm.
      </td>
      <td>95%</td>
      <td>90%</td>
      <td>90%</td>
    </tr>
    <tr>
      <td><a href="./LoopyBp.md">Loopy Belief Propagation</a></td>
      <td>
        Loopy BP on the factor graph of row/column/diagonal/anti-diagonal constraints, with messages updated in 
        parallel on the GPU. Applying loopy belief propagation to CRSCE had mixed but interesting results.
      </td>
      <td>80%</td>
      <td>85%</td>
      <td>70%</td>
    </tr>
    <tr>
      <td><a href="game-of-life-protocol.md">Game-of-Life Protocol</a></td>
      <td>Majority-vote cellular automaton where each cell flips or holds based on its four sum-residuals, iterating 
          until convergence. With GPU parallelism, GOLP was a weekend experiment that performed poorly at first. But
          it inspired some new thinking.
      </td>
      <td>85%</td>
      <td>85%</td>
      <td>80%</td>
    </tr>
    <tr>
      <td><a href="game-of-beliefs-protocol.md">Game of Beliefs Protocol</a></td>
      <td>
        The row-centric nature of Radditz Sieve, the probabilistic nature of Loopy Beliefs (pun intended) and the
        concurrent realism of GOLP were combined into a single hybrid protocol called Game of Beliefs Protocol (GOBP).
        This protocol uses a hierarchical row-based thread model to solve each row independently while sharing 
        knowledge among the rows from a single row-master thread.  This row-master then controls the solution of its 
        row asynchronously.
      </td>
      <td>85%</td>
      <td>90%</td>
      <td>80%</td>
    </tr>
    <tr>
      <td><a href="Path-Integral-QMC-on-GPU.md">Path-Integral QMC on GPU</a></td>
      <td>
        Suzuki–Trotter mapping of a transverse-field Ising QUBO, sampled via path-integral Monte Carlo 
        kernels on the GPU. This is a future opportunity to extend CRSCE into a quantum computing model.
      </td>
      <td>90%</td>
      <td>75%</td>
      <td>80%</td>
    </tr>
</tbody>
</table>
