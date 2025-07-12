Cross Sums Compression and Expansion (CRSCE)
--------------------------------------------

A structural, lossless, and content-independent compression algorithm with 
predictable output sizes.

## ⚠️Disclaimer⚠️

<span style="color:red">
    This project is under active development.  
    It is not intended for production use.
</span>

## 🚀 Overview

CRSCE represents arbitrary binary input as a series of fixed-size s×s bit-matrices, 
computes four cross-sum projections (lateral, vertical, diagonal, anti-diagonal) plus 
a cryptographic hash chain, and packs them into a compact, verifiable format.

## Status
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=asymmetric-effort_crsce&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=asymmetric-effort_crsce)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=asymmetric-effort_crsce&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=asymmetric-effort_crsce)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=asymmetric-effort_crsce&metric=bugs)](https://sonarcloud.io/summary/new_code?id=asymmetric-effort_crsce)


## Features

* ***Predictable compression:*** Fixed, content-independent ratio (42.97% at s=511).
* ***Integrity-guaranteed:*** SHA-256 hash chain ensures exact reconstruction.

## ⚙️ Requirements

* C++20 compiler (e.g. g++, clang++)
* CMake ≥ 3.14 (`brew install cmake`)
* OpenSSL (for SHA-256)
* `make`
* `ninja`
* `ccache`

## 🔧 Building

```shell
git clone <repo-url>
cd crsce
make clean build test
```

This produces:

* `build/bin/compress`
* `build/bin/decompress`

## 💻 Usage

### Compress

#### Syntax

```shell
./crsce_compress <input.bin> <output.crsce>
```

### Decompress (coming soon)

#### Syntax

```shell
./crsce_decompress <input.crsce> <output.bin>
```

## ✅ Running Tests

```shell
make test
```

## 📄 Documentation

* [Cross Sums Compression: A Structural Approach to Predictable, Lossless Binary Compression](./docs/theory/CRSCE-2025-v1.docx)
* [Research: Decompression Options](./docs/theory/research/decompression-options.md)
* [Project History](./docs/HISTORY.md)
* [File structure](./docs/CRSCE_File_Structure.md)

---
© 1993-2025 Asymmetric Effort, LLC. All rights reserved.






