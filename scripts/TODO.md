# Vector API

## 1. Core API

| Function                           | Purpose                         | Status |
| ---------------------------------- | ------------------------------- |--------|
| `Vector()`                         | Default zero-initialized vector | ✅      |
| `Vector(std::initializer_list<T>)` | Construct from list of values   | ✅      |
| `operator()(size_t i)` / `const`   | Index-based access              | ✅      |
| `operator[](size_t i)` / `const`   | Optional array-style access     | ✅      |
| `Vector& operator=(const Vector&)` | Copy assignment                 | ✅      |

## 2. Arithmetic operators

| Operator                                  | Notes              | Status |
| ----------------------------------------- | ------------------ | ------ |
| `operator+(const Vector&, const Vector&)` | Vector addition    | ✅      |
| `operator-(const Vector&, const Vector&)` | Vector subtraction | ✅      |
| `operator-(const Vector&)`                | Unary negation     | ✅      |
| `operator*(T, const Vector&)`             | Scalar \* vector   | ✅      |
| `operator*(const Vector&, T)`             | Vector \* scalar   | ✅      |
| `operator/(const Vector&, T)`             | Vector / scalar    | ✅      |

## 3. In-place arithmetic operators

| Operator                    | Description                    | Satus |
| --------------------------- | ------------------------------ |-------|
| `operator+=(const Vector&)` | In-place addition              | ✅     |
| `operator-=(const Vector&)` | In-place subtraction           | ✅     |
| `operator*=(T)`             | In-place scalar multiplication | ✅     |
| `operator/=(T)`             | In-place scalar division       | ✅     |

## 4. Vector properties and norms

| Function                                | Description                              | Status |
|-----------------------------------------| ---------------------------------------- |--------|
| `dot(const Vector&, const Vector&)`     | Dot product                              | ✅      |
| `cross(const Vector&)`                  | Perpendicular (2D) or cross product (3D) | ✅      |
| `norm(const Vector&)`                   | Euclidean norm                           | ✅      |
| `rnorm(const Vector&)`                  | Regularized norm: `sqrt(dot + eps²)`     | ✅      |
| `normalize(const Vector&)` *(optional)* | Unit-length version                      | ✅      |
| `rnormalize(T scalar)` *(optional)*     | Guarded division                         | ✅      |

## 5. Interpolation

| Function                                   | Description                                | Status |
| ------------------------------------------ | ------------------------------------------ |--------|
| `lerp(const Vector&, const Vector&, T t)`  | Linear interpolation                       | ❌      |
| `slerp(const Vector&, const Vector&, T t)` | Spherical interpolation (for unit vectors) | ❌      |

## 6. Comparison

| Function                                   | Description                    | Status |
| ------------------------------------------ | ------------------------------ |--------|
| `approx_equal(const Vector&, T tol = eps)` | Tolerance-based equality check | ❌      |

## 7. Internal constants

| Member        | Description                                                             | Status |
| ------------- | ----------------------------------------------------------------------- |--------|
| `eps`         | Regularization parameter from `RegularizationEps<T, REG_PREC>::value()` | ✅      | 
| `eps_squared` | `eps * eps`, reused in regularized norms                                | ✅      |

## 8. Input/output

| Function                                   | Notes                           | Status |
| ------------------------------------------ | ------------------------------- |--------|
| `operator<<(std::ostream&, const Vector&)` | `(x, y, ..., n)`-style printing | ✅      |


# Matrix API

## 1. Core API

| Function                                                  | Notes                     | Status |
| --------------------------------------------------------- | ------------------------- | ------ |
| `Matrix()`                                                | Zero-initialized          | ⬜      |
| `Matrix(std::initializer_list<std::initializer_list<T>>)` | Brace init                | ⬜      |
| `Matrix& operator=(const Matrix&)`                        | Copy assignment           | ⬜      |
| `operator()(size_t i, size_t j)` / `const`                | Element access            | ⬜      |
| `operator[](size_t i)` / `const`                          | Optional row-style access | ⬜      |


## 2. Arithmetic operators

| Operator                                  | Notes              | Status |
| ----------------------------------------- | ------------------ | ------ |
| `operator+(const Matrix&, const Matrix&)` | Matrix addition    | ⬜      |
| `operator-(const Matrix&, const Matrix&)` | Matrix subtraction | ⬜      |
| `operator-(const Matrix&)`                | Unary negation     | ⬜      |
| `operator*(T, const Matrix&)`             | Scalar \* matrix   | ⬜      |
| `operator*(const Matrix&, T)`             | Matrix \* scalar   | ⬜      |
| `operator/(const Matrix&, T)`             | Matrix / scalar    | ⬜      |


## 3. In place arithmetic operators

| Operator                    | Notes                          | Status |
| --------------------------- | ------------------------------ | ------ |
| `operator+=(const Matrix&)` | In-place addition              | ⬜      |
| `operator-=(const Matrix&)` | In-place subtraction           | ⬜      |
| `operator*=(T)`             | In-place scalar multiplication | ⬜      |
| `operator/=(T)`             | In-place scalar division       | ⬜      |

## 4. Matrix-matrix operators

| Function / Operator                       | Notes                                          | Status |
|-------------------------------------------|------------------------------------------------| ------ |
| `operator*(const Matrix&, const Matrix&)` | Matrix multiplication                          | ⬜      |
| `transpose()`                             | Matrix transpose                               | ⬜      |
| `minor(size_t row, size_t col)`           | Submatrix (for determinant/adjugate)           | ⬜      |
| `determinant()`                           | Uses recursion or direct formula for small `N` | ⬜      |
| `adjugate()`                              | For inverse calculation                        | ⬜      |
| `inverse()`                               | May use `adj / det`, with regularization       | ⬜      |
| `identity()`                              | Static identity matrix                         | ⬜      |
| `trace()`                                 | Sum of diagonal elements                       | ⬜      |

## 5. Norms and regularization

| Function            | Notes                      | Status |
| ------------------- | -------------------------- | ------ |
| `frobenius_norm()`  | sqrt of sum of squares     | ⬜      |
| `rfrobenius_norm()` | With `eps²` regularization | ⬜      |

## 6. Vector-matrix operators

| Operation                  | Notes                        | Status |
| -------------------------- | ---------------------------- | ------ |
| `Vector = Matrix * Vector` | Matrix-vector multiplication | ⬜      |


## 7. Comparison

| Function                             | Notes                 | Status |
| ------------------------------------ | --------------------- | ------ |
| `approx_equal(const Matrix&, T tol)` | Elementwise tolerance | ⬜      |


## 8. Output

| Function                                   | Notes                     | Status |
| ------------------------------------------ | ------------------------- | ------ |
| `operator<<(std::ostream&, const Matrix&)` | Line-by-line pretty-print | ⬜      |


## 9. Internal constants

| Constant      | Notes                                          | Status |
| ------------- | ---------------------------------------------- | ------ |
| `eps`         | From `RegularizationEps<T, REG_PREC>::value()` | ⬜      |
| `eps_squared` | Used in regularized ops                        | ⬜      |
