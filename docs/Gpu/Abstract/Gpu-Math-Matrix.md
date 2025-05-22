`Gpu::Math::Matrix`
===================

## Purpose

Purpose

`Gpu::Math::Matrix` defines a row-major, dense two-dimensional matrix abstraction used for GPU-accelerated linear
algebra and decompression workloads. It is the core data type used in vector and matrix operations invoked
by `Gpu::Interface` methods, including `dot()`, `add()`, `subtract()`, `multiply()`, `transpose()`, and `reduce()`.

This type also serves as the canonical memory layout for representing CRSCE decompression factors and row-column
solving matrices.

## Dependencies

N/A

#### Properties

| Name | Type             | Description                       |
|------|------------------|-----------------------------------|
| rows | `std::size_t`    | Number of matrix rows             |
| cols | `std::size_t`    | Number of matrix columns          |
| data | `std::vector<T>` | Row-major flattened matrix values |

### Constructor

| Scope    | Method                                                                                    | Description                 |
|----------|-------------------------------------------------------------------------------------------|-----------------------------|
| `public` | `Matrix(std::size_t rows, std::size_t cols);`                                             |                             |
| `public` | `Matrix(std::size_t rows, std::size_t cols, std::vector<uint64_t>& values);`              | size must equal rows × cols |
| `public` | `Matrix(std::size_t rows, std::size_t cols, std::vector<std::vector<uint64_t>>& values);` | size must equal rows × cols |
| `public` | `Matrix(std::size_t rows, std::size_t cols, std::vector<std::vector<int>>& values);`      | size must equal rows × cols |
| `public` | `Matrix(std::size_t rows, std::size_t cols, std::vector<std::vector<float>>& values);`    | size must equal rows × cols |
| `public` | `Matrix(std::size_t rows, std::size_t cols, std::vector<std::vector<double>>& values);`   | size must equal rows × cols |

## Destructor

Automatically releases matrix-owned memory (i.e., clears internal vector).

## Math Functions

| Scope    | Method                                                                                                  | Description           |
|----------|---------------------------------------------------------------------------------------------------------|-----------------------|
| `public` | `bool dot(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);`      | calculate dot product |
| `public` | `bool add(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);`      | result = lhs+rhs      |
| `public` | `bool subtract(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs-rhs      |
| `public` | `bool multiply(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs*rhs      |
| `public` | `bool transpose(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat);`                              | transpose mat         |
| `public` | `bool reduce(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat, bool rowwise);`                   | reduce mat            |

### Notes

* These methods return `true` on success and `false` on error.

## Operators

| Scope    | Operator                                     | Description      |
|----------|----------------------------------------------|------------------|
| `public` | `Matrix operator+(const Matrix& rhs) const;' | result = lhs+rhs |
| `public` | `Matrix operator-(const Matrix& rhs) const;' | result = lhs-rhs |
| `public` | `Matrix operator*(const Matrix& rhs) const;' | result = lhs*rhs |
| `public` | `bool operator==(const Matrix& rhs) const;'  | equality         |
| `public` | `bool operator!=(const Matrix& rhs) const;'  | inequality       |
