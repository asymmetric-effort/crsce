Game of Beliefs Protocol: Step-by-Step
======================================

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

This protocol reconstructs CRSCE compressed blocks by combining belief propagation with row-constrained, parallel
cellular automaton updates. Each row's bit-budget is fixed by its LSM entry, and the decompressor aims to distribute
these bits such that column, diagonal, and anti-diagonal constraints are satisfied—and each row hash (LHASH) matches its
SHA-256 value.

This version assumes execution on GPU hardware with warp-synchronous execution and thread-block partitioning.

## Phases

| Phase         | Description                                             |
|---------------|---------------------------------------------------------|
| DE            | Exact elimination of forced bits                        |
| Loopy BP      | Probabilistic initialization of cell likelihoods        |
| Row-Master CA | Fixed-budget row-local updates to enforce consistency   |
| SHA Checks    | Validate each row as solved; deactivate if successful   |
| Convergence   | Protocol ends when all rows are stable and hash-matched |

---

## Key Properties

- Fully parallelizable across rows and columns
- Efficient use of GPU shared memory (row-local)
- No need for global row-locking
- Highly deterministic; suitable for batch decompression



## Overview : Step-by-Step

### Step 1: Deterministic Elimination (DE)

Apply inference rules to reduce uncertainty in the CSM:

- Set all bits in rows/cols/diags where the sum is 0 or \( s \)
- Complete any line with exactly one unknown
- Propagate until convergence

**Result:** A partially filled CSM with reduced entropy

### Step 2: Initialize Belief Field (Loopy BP)

- Construct the factor graph of remaining unknowns and constraints
- Run Loopy Belief Propagation for a fixed number of iterations (e.g. 10–20)
- Store marginal beliefs \( p_{rc} \in [0,1] \) for each unknown bit

**Purpose:** Provide probabilistic guidance for where each bit is likely to be 1

### Step 3: Launch Row-Master Threadblocks

For each unsolved row \( r \):

- Spawn a **row-master thread** to supervise that row
- Spawn \( n < s \) **CA threads** under that master:
  - Each CA thread manages a slice of the row’s columns
  - Threads have access to:
    - Shared memory for row-local state
    - Global memory for VSM, XSM, DSM residuals

### Step 4: Initial Row Population (Fixed Budget)

Each row-master performs:

- Assign \( LSM[r] \) 1s to cells \( x_{rc} \in \{0,1\} \), where:
  - Available bits are not fixed by DE
  - Selected based on \( p_{rc} \): prefer high-belief cells
- Resulting bitfield must satisfy:
  - Row sum = \( LSM[r] \)
  - No SHA-256 match required yet

### Step 5: Iterative CA Updates (Belief-Guided)

CA threads perform synchronous updates in parallel:

- For each cell \( x_{rc} \):
  - Evaluate local residuals from column/diag/anti-diag constraints
  - If cell holds a 1 but is low-belief or redundant:
    - Attempt to **migrate** it to a neighbor column \( c' \) in row \( r \)
    - Target columns should have:
      - Underfilled VSM
      - Higher belief
      - Compatible XSM/DSM impact
- Each update preserves the **row bit budget**

CA threads synchronize within their row-block using shared memory

### Step 6: Check Row Hash (Early Exit)

Each row-master computes the SHA-256 hash of its row:

- If the row's bit configuration satisfies:
  - Row sum = \( LSM[r] \)
  - SHA-256(row) = \( LHASH[r] \)
- Then: **terminate** the row-master and its CA threads

This avoids the need for hash-lock flags—the row-master's termination is sufficient.

### Step 7: Repeat Until Convergence

- Repeat Steps 5–6 for active row blocks
- Convergence occurs when:
  - All row-masters have exited
  - Or a timeout limit (e.g. max 100 CA steps) is reached

If convergence fails:

- Optionally restart BP + CA phases with perturbed priors
- Or fall back to another decompression method (e.g., Radditz Sieve)

### Step 8: Final Validation

If all rows are hash-verified and cross-sum constraints are met:

- Declare decompression successful
- Emit bit matrix to downstream consumer
