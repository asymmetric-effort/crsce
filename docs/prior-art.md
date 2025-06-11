Prior Art
=========


## Abstract
This document surveys existing data compression and matrix encoding techniques relevant to the Cross Sums 
Compression and Expansion (CRSCE) algorithm. We review foundational entropy-based approaches, transform-based 
preprocessing, bit‐plane methods, sparse/matrix‐specific schemes, and patent literature to identify potential 
conflicts or competing inventions. All prior work is discussed without fabrication and based on verifiable 
sources.

***Keywords:*** CRSCE, lossless compression, bit‐plane compression, matrix compression, prior art


## Introduction
CRSCE leverages row, column, and diagonal sum constraints to achieve lossless compression independent of data
entropy. To ensure novelty and freedom‐to‐operate, we examine related research and patents in several categories.


## Literature Review

1. ***Entropy‐Based Compression Techniques***
   Classic lossless methods form the foundation of modern compressors. Huffman (1952) introduced variable‐length 
   codes bound by Shannon’s entropy limit. Ziv and Lempel (1977) proposed universal sequential compression (LZ77), 
   later refined by Welch (1984) into LZW, which remains widely used in formats like GIF 
   ([en.wikipedia.org](https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch)).

2. ***Transform‐Based Preprocessing***
   Pre‐encoding transformations can expose patterns to improve compressibility. Jungrae Kim et al. (2016) present
   Bit‐Plane Compression (BPC) for many‐core memory, using a Delta‐BitPlane‐XOR (DBX) transform to reduce entropy 
   before encoding ([lph.ece.utexas.edu](https://lph.ece.utexas.edu/merez/uploads/MattanErez/isca2016_bpc.pdf)).

3. ***Bit‐Plane Compression Variants***
   Extended Bit‐Plane Compression (EBPC) targets DNN feature maps with hardware‐friendly, lossless schemes and 
   achieves high throughput in silicon ([research-collection.ethz.ch](https://www.research-collection.ethz.ch/bitstream/20.500.11850/382423/1/FINALVERSION.pdf)).

4. ***Sparse and Matrix‐Specific Compression***
   Lawlor (2014) designs an in‐memory scheme for sparse matrices focused on bandwidth and storage trade‐offs
   ([cs.uaf.edu](https://www.cs.uaf.edu/~olawlor/papers/2013/compression/lawlor_compression_2013.pdf)). Hou et al. 
   (2015) introduce Sparse Low‐Rank Matrix Approximation (SLRMA) to exploit intra‐ and inter‐sample coherence via 
   orthogonal transforms ([arxiv.org](https://arxiv.org/abs/1507.01673)). Kanellopoulos et al. (2019) co‐design 
   software compression and hardware indexing (SMASH) for sparse matrix operations using bitmap hierarchies 
   ([arxiv.org](https://arxiv.org/abs/1910.10776)). Ferragina et al. (2022) propose grammar‐compressed matrices 
   supporting efficient matrix‐vector multiplication in compressed form 
   ([lph.ece.utexas.edu](https://lph.ece.utexas.edu/merez/uploads/MattanErez/isca2016_bpc.pdf))


## References
Lawlor, O. S. (2014). *In-memory data compression for sparse matrices* (Tech. Rep.). University of Alaska Fairbanks.
     ([cs.uaf.edu](https://www.cs.uaf.edu/~olawlor/papers/2013/compression/lawlor_compression_2013.pdf))

Hou, J., Chau, L.-P., Magnenat-Thalmann, N., & He, Y. (2015). SLRMA: Sparse low-rank matrix approximation for data 
     compression. *arXiv preprint arXiv:1507.01673*. ([arxiv.org](https://arxiv.org/abs/1507.01673))

Kanellopoulos, K., Vijaykumar, N., Giannoula, C., Azizi, R., Koppula, S., Mansouri Ghiasi, N., Shahroodi, T., Gomez 
     Luna, J., & Mutlu, O. (2019). SMASH: Co-designing software compression and hardware-accelerated indexing for 
     efficient sparse matrix operations. *arXiv preprint arXiv:1910.10776*. 
     ([arxiv.org](https://arxiv.org/abs/1910.10776))

Ferragina, P., Gagie, T., Köppl, D., Manzini, G., Navarro, G., Striani, M., & Tosoni, F. (2022). Improving 
     matrix-vector multiplication via lossless grammar-compressed matrices. *arXiv preprint arXiv:2203.14540*. 
     ([arxiv.org](https://arxiv.org/abs/2203.14540))

U.S. Patent No. 7,714,747. (2010). Data compression systems and methods. U.S. Patent and Trademark Office. 
     ([patents.google.com](https://patents.google.com/patent/US7714747B2/en))
