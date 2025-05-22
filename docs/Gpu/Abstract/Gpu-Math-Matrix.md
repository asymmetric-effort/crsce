`Gpu::Math::Matrix`
===================

## Purpose

Purpose

`Gpu::Math::Matrix` defines a row-major, dense two-dimensional matrix abstraction used for GPU-accelerated linear
algebra and decompression workloads. It is the core data type used in vector and matrix operations invoked
by `Gpu::Interface` methods, including `dot()`, `add()`, `subtract()`, `multiply()`, `transpose()`, and `reduce()`.

## Dependencies

N/A

#### Properties

| Name | Type                  | Description                                              |
|------|-----------------------|----------------------------------------------------------|
| rows | `std::size_t`         | Number of matrix rows                                    |
| cols | `std::size_t`         | Number of matrix columns                                 |
| data | `Common::AbstractPtr` | Reference to the GPU memory where the matrix is located. |

### Constructor

| Scope    | Method                                                                                                         | Description                 |
|----------|----------------------------------------------------------------------------------------------------------------|-----------------------------|
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols);`                                             |                             |
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols, std::vector<uint64_t>& values);`              | size must equal rows × cols |
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols, std::vector<std::vector<uint64_t>>& values);` | size must equal rows × cols |
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols, std::vector<std::vector<int>>& values);`      | size must equal rows × cols |
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols, std::vector<std::vector<float>>& values);`    | size must equal rows × cols |
| `public` | `Matrix(Gpu::Interface& gpu, std::size_t rows, std::size_t cols, std::vector<std::vector<double>>& values);`   | size must equal rows × cols |

### Notes

* The constructor will use `Gpu::Interface` to invoke `alloc()` and `write()` to store the matrix on the GPU.

## Destructor

Automatically releases matrix-owned memory (i.e., clears internal vector).

## Math Functions

| Scope    | Method                                                                       | Description           |
|----------|------------------------------------------------------------------------------|-----------------------|
| `public` | `bool dot(const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);`      | calculate dot product |
| `public` | `bool add(const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);`      | result = lhs+rhs      |
| `public` | `bool subtract(const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs-rhs      |
| `public` | `bool multiply(const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs);` | result = lhs*rhs      |
| `public` | `bool transpose(const Gpu::Math::Matrix& mat);`                              | transpose mat         |
| `public` | `bool reduce(const Gpu::Math::Matrix& mat, const bool rowwise);`             | reduce mat            |

### Notes

* These methods return `true` on success and `false` on error.
* When a math operation between two matrices are performed--
  * The invoking matrix object represents the result (e.g., result = lhs + rhs)
  * The invoking matrix will obtain the opaque GPU memory references needed from the operad(s)
  * The invoking matrix will use `Gpu::Interface` go perform the math operation on the GPU.

## Operators

| Scope    | Operator                                     | Description      |
|----------|----------------------------------------------|------------------|
| `public` | `Matrix operator+(const Matrix& rhs) const;' | result = lhs+rhs |
| `public` | `Matrix operator-(const Matrix& rhs) const;' | result = lhs-rhs |
| `public` | `Matrix operator*(const Matrix& rhs) const;' | result = lhs*rhs |
| `public` | `bool operator==(const Matrix& rhs) const;'  | equality         |
| `public` | `bool operator!=(const Matrix& rhs) const;'  | inequality       |
