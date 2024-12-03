//
// Created by Lesleis Nagy on 18/03/2024.
//

#ifndef LIBFABBRI_MATRIX3X3_HPP
#define LIBFABBRI_MATRIX3X3_HPP

#include <cassert>

#include "vector3d.hpp"

/**
 * An implementation of a three by three square matrix.
 */
template<typename T>
class Matrix3x3 {

 public:

  /**
   * Create a 3x3 zero-matrix.
   */
  Matrix3x3() :
      _m{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} {}

  /**
   * Create a 3x3 matrix from an input.
   */
  Matrix3x3(std::initializer_list<std::initializer_list<T>> m) {

    assert(m.size() == 3 && "Number of rows must be 3.");

    auto outerIterator = m.begin();
    auto innerIterator = outerIterator->begin();

    assert(outerIterator->size() == 3 && "Number of columns must be 3.");
    _m[0][0] = *innerIterator++;
    _m[0][1] = *innerIterator++;
    _m[0][2] = *innerIterator++;

    outerIterator++;
    innerIterator = outerIterator->begin();

    assert(outerIterator->size() == 3 && "Number of columns must be 3.");
    _m[1][0] = *innerIterator++;
    _m[1][1] = *innerIterator++;
    _m[1][2] = *innerIterator++;

    outerIterator++;
    innerIterator = outerIterator->begin();

    assert(outerIterator->size() == 3 && "Number of columns must be 3.");
    _m[2][0] = *innerIterator++;
    _m[2][1] = *innerIterator++;
    _m[2][2] = *innerIterator++;

  }

  Matrix3x3 &operator=(const Matrix3x3 &m) {

    if (this == &m) return *this;
    _m[0][0] = m._m[0][0];
    _m[0][1] = m._m[0][1];
    _m[0][2] = m._m[0][2];

    _m[1][0] = m._m[1][0];
    _m[1][1] = m._m[1][1];
    _m[1][2] = m._m[1][2];

    _m[2][0] = m._m[2][0];
    _m[2][1] = m._m[2][1];
    _m[2][2] = m._m[2][2];

    return *this;

  }

  [[nodiscard]]
  T operator()(size_t i, size_t j) const { return _m[i][j]; }

 private:

  T _m[3][3];

};

/**
 * Redirection operator to display the matrix.
 * @tparam T the underlying data type for the calculation.
 * @param out the output stream.
 * @param m the matrix to display.
 * @return the output stream with a representation of the input matrix.
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix3x3<T> m) {

  out << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << std::endl;
  out << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << std::endl;
  out << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << std::endl;

  return out;

}

/**
 * Matrix addition operator.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the sum.
 * @param v the matrix on the right hand side of the sum.
 * @return the sum of the two input matrices.
 */
template<typename T>
Matrix3x3<T> operator+(const Matrix3x3<T> &u, const Matrix3x3<T> &v) {

  return {{u(0, 0) + v(0, 0), u(0, 1) + v(0, 1), u(0, 2) + v(0, 2)},
          {u(1, 0) + v(1, 0), u(1, 1) + v(1, 1), u(1, 2) + v(1, 2)},
          {u(2, 0) + v(2, 0), u(2, 1) + v(2, 1), u(2, 2) + v(2, 2)}};

}

/**
 * Matrix subtraction operator.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the operator.
 * @param v the matrix on the right hand side of the operator.
 * @return the difference of two input matrices.
 */
template<typename T>
Matrix3x3<T> operator-(const Matrix3x3<T> &u, const Matrix3x3<T> &v) {

  return {{u(0, 0) - v(0, 0), u(0, 1) - v(0, 1), u(0, 2) - v(0, 2)},
          {u(1, 0) - v(1, 0), u(1, 1) - v(1, 1), u(1, 2) - v(1, 2)},
          {u(2, 0) - v(2, 0), u(2, 1) - v(2, 1), u(2, 2) - v(2, 2)}};

}

/**
 * Matrix-scalar product operator.
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the product.
 * @param lambda the scalar on the right hand side of the product.
 * @return the matrix-scalar product.
 */
template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T> &v, T lambda) {

  return {{v(0, 0) * lambda, v(0, 1) * lambda, v(0, 2) * lambda},
          {v(1, 0) * lambda, v(1, 1) * lambda, v(1, 2) * lambda},
          {v(2, 0) * lambda, v(2, 1) * lambda, v(2, 2) * lambda}};

}

/**
 * Scalar-matrix product operator.
 * @tparam T the underlying data type for the calculation.
 * @param lambda the scalar on the left hand side of the product.
 * @param v the matrix on the right hand side of the product.
 * @return the scalar-matrix product.
 */
template<typename T>
Matrix3x3<T> operator*(T lambda, const Matrix3x3<T> &v) {

  return {{lambda * v(0, 0), lambda * v(0, 1), lambda * v(0, 2)},
          {lambda * v(1, 0), lambda * v(1, 1), lambda * v(1, 2)},
          {lambda * v(2, 0), lambda * v(2, 1), lambda * v(2, 2)}};

}

/**
 * Matrix-scalar division.
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the division.
 * @param lambda the scalar on the right hand side of the division.
 * @return the matrix-scalar division.
 */
template<typename T>
Matrix3x3<T> operator/(const Matrix3x3<T> &v, T lambda) {

  return {{v(0, 0) / lambda, v(0, 1) / lambda, v(0, 2) / lambda},
          {v(1, 0) / lambda, v(1, 1) / lambda, v(1, 2) / lambda},
          {v(2, 0) / lambda, v(2, 1) / lambda, v(2, 2) / lambda}};

}

/**
 * Matrix-vector multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix on the left hand side of the multiplication.
 * @param v the vector on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template<typename T>
Vector3D<T> operator*(const Matrix3x3<T> &m, const Vector3D<T> &v) {

  return {m(0, 0) * v.x() + m(0, 1) * v.y() + m(0, 2) * v.z(),
          m(1, 0) * v.x() + m(1, 1) * v.y() + m(1, 2) * v.z(),
          m(2, 0) * v.x() + m(2, 1) * v.y() + m(2, 2) * v.z()};

}

/**
 * Vector-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param v the vector on the left hand side of the multiplication.
 * @param m the matrix on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template<typename T>
Vector3D<T> operator*(const Vector3D<T> &v, const Matrix3x3<T> &m) {

  return {m(0, 0) * v.x() + m(1, 0) * v.y() + m(2, 0) * v.z(),
          m(0, 1) * v.x() + m(1, 1) * v.y() + m(2, 1) * v.z(),
          m(0, 2) * v.x() + m(1, 2) * v.y() + m(2, 2) * v.z()};

}

/**
 * Matrix-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m0 the matrix on the left hand side of the multiplication.
 * @param m1 the matrix on the right hand side of the multiplication.
 * @return the matrix-matrix multiplication.
 */
template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T> &m0, const Matrix3x3<T> &m1) {

  return {{m0(0, 0) * m1(0, 0) + m0(0, 1) * m1(1, 0) + m0(0, 2) * m1(2, 0),
           m0(0, 0) * m1(0, 1) + m0(0, 1) * m1(1, 1) + m0(0, 2) * m1(2, 1),
           m0(0, 0) * m1(0, 2) + m0(0, 1) * m1(1, 2) + m0(0, 2) * m1(2, 2)},

          {m0(1, 0) * m1(0, 0) + m0(1, 1) * m1(1, 0) + m0(1, 2) * m1(2, 0),
           m0(1, 0) * m1(0, 1) + m0(1, 1) * m1(1, 1) + m0(1, 2) * m1(2, 1),
           m0(1, 0) * m1(0, 2) + m0(1, 1) * m1(1, 2) + m0(1, 2) * m1(2, 2)},

          {m0(2, 0) * m1(0, 0) + m0(2, 1) * m1(1, 0) + m0(2, 2) * m1(2, 0),
           m0(2, 0) * m1(0, 1) + m0(2, 1) * m1(1, 1) + m0(2, 2) * m1(2, 1),
           m0(2, 0) * m1(0, 2) + m0(2, 1) * m1(1, 2) + m0(2, 2) * m1(2, 2)}};

}

/**
 * Matrix adjugate.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix adjugate.
 */
template<typename T>
Matrix3x3<T> adj(const Matrix3x3<T> &m) {

  return {{-(m(1, 2) * m(2, 1)) + m(1, 1) * m(2, 2),
           m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2),
           -(m(0, 2) * m(1, 1)) + m(0, 1) * m(1, 2)},

          {m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2),
           -(m(0, 2) * m(2, 0)) + m(0, 0) * m(2, 2),
           m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)},

          {-(m(1, 1) * m(2, 0)) + m(1, 0) * m(2, 1),
           m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1),
           -(m(0, 1) * m(1, 0)) + m(0, 0) * m(1, 1)}};

}

/**
 * Matrix determinant.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix determinant.
 */
template<typename T>
T det(const Matrix3x3<T> &m) {

  return -(m(0, 2) * m(1, 1) * m(2, 0)) + m(0, 1) * m(1, 2) * m(2, 0) +
      m(0, 2) * m(1, 0) * m(2, 1) - m(0, 0) * m(1, 2) * m(2, 1) -
      m(0, 1) * m(1, 0) * m(2, 2) + m(0, 0) * m(1, 1) * m(2, 2);

}

/**
 * Matrix transpose.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix transpose.
 */
template<typename T>
Matrix3x3<T> tr(const Matrix3x3<T> &m) {

  return {{m(0, 0), m(1, 0), m(2, 0)},
          {m(0, 1), m(1, 1), m(2, 1)},
          {m(0, 2), m(1, 2), m(2, 2)}};

}

/**
 * Matrix-matrix Frobenius (dot) product.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the dot product.
 * @param v the matrix on the right hand side of the dot product.
 * @return the matrix-vector multiplication.
 */
template<typename T>
T dot(const Matrix3x3<T> &u, const Matrix3x3<T> &v) {

  return u(0, 0) * v(0, 0) + u(0, 1) * v(0, 1) + u(0, 2) * v(0, 2) +
      u(1, 0) * v(1, 0) + u(1, 1) * v(1, 1) + u(1, 2) * v(1, 2) +
      u(2, 0) * v(2, 0) + u(2, 1) * v(2, 1) + u(2, 2) * v(2, 2);

}

/**
 * Matrix Frobenius norm.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix to take the norm of.
 * @return the matrix Frobenius norm.
 */
template<typename T>
T norm(const Matrix3x3<T> &u) {

  return sqrt(dot(u, u));

}

/**
 * Matrix diagonal.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix from which to extract the diagonal.
 * @return the matrix diagonal.
 */
template<typename T>
Vector3D<T> diag(const Matrix3x3<T> &m) {

  return {m(0, 0), m(1, 1), m(2, 2)};

}

/**
 * Matrix trace.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix for which to compute the trace.
 * @return the matrix trace.
 */
template<typename T>
T trace(const Matrix3x3<T> &m) {

  return m(0, 0) + m(1, 1) + m(2, 2);

}

/**
 * Create a column matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @param v3 the third vector
 * @return the column matrix formed from v1, v2 & v3
 */
template<typename T>
Matrix3x3<T> column_matrix(
    const Vector3D<T> &v1,
    const Vector3D<T> &v2,
    const Vector3D<T> &v3
) {
  return {
      {v1.x(), v2.x(), v3.x()},
      {v1.y(), v2.y(), v3.y()},
      {v1.z(), v2.z(), v3.z()}
  };
}

/**
 * Create a row matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @param v3 the third vector
 * @return the row matrix formed from v1, v2 & v3
 */
template<typename T>
Matrix3x3<T> row_matrix(
    const Vector3D<T> &v1,
    const Vector3D<T> &v2,
    const Vector3D<T> &v3) {
  return {
      {v1.x(), v1.y(), v1.z()},
      {v2.x(), v2.y(), v2.z()},
      {v3.x(), v3.y(), v3.z()}
  };
}

#endif //LIBFABBRI_MATRIX3X3_HPP
