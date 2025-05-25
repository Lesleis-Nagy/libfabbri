//
// Created by Lesleis Nagy on 19/03/2024.
//

#ifndef LIBFABBRI_MATRIX4X4_HPP
#define LIBFABBRI_MATRIX4X4_HPP

#include <cassert>

#include "vector4d.hpp"

/**
 * An implementation of a three by three square matrix.
 */
template <typename T>
class Matrix4x4 {

  public:

    /**
     * Create a 4x4 zero-matrix.
     */
    Matrix4x4():
      _m{{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}
    {}

    /**
     * Create a 4x4 matrix from an input.
     */
    Matrix4x4(std::initializer_list<std::initializer_list<T>> m) {

      assert(m.size() == 4 && "Number of rows must be 4.");

      auto outerIterator = m.begin();
      auto innerIterator = outerIterator->begin();

      assert(outerIterator->size() == 4 && "Number of columns must be 4.");
      _m[0][0] = *innerIterator++;
      _m[0][1] = *innerIterator++;
      _m[0][2] = *innerIterator++;
      _m[0][3] = *innerIterator++;

      outerIterator++;
      innerIterator = outerIterator->begin();

      assert(outerIterator->size() == 4 && "Number of columns must be 4.");
      _m[1][0] = *innerIterator++;
      _m[1][1] = *innerIterator++;
      _m[1][2] = *innerIterator++;
      _m[1][3] = *innerIterator++;

      outerIterator++;
      innerIterator = outerIterator->begin();

      assert(outerIterator->size() == 4 && "Number of columns must be 4.");
      _m[2][0] = *innerIterator++;
      _m[2][1] = *innerIterator++;
      _m[2][2] = *innerIterator++;
      _m[2][3] = *innerIterator++;

      outerIterator++;
      innerIterator = outerIterator->begin();

      assert(outerIterator->size() == 4 && "Number of columns must be 4.");
      _m[3][0] = *innerIterator++;
      _m[3][1] = *innerIterator++;
      _m[3][2] = *innerIterator++;
      _m[3][3] = *innerIterator++;

    }

    Matrix4x4& operator=(const Matrix4x4 &m) {

      if (this == &m) return *this;
      _m[0][0] = m._m[0][0];
      _m[0][1] = m._m[0][1];
      _m[0][2] = m._m[0][2];
      _m[0][3] = m._m[0][3];

      _m[1][0] = m._m[1][0];
      _m[1][1] = m._m[1][1];
      _m[1][2] = m._m[1][2];
      _m[1][3] = m._m[1][3];

      _m[2][0] = m._m[2][0];
      _m[2][1] = m._m[2][1];
      _m[2][2] = m._m[2][2];
      _m[2][3] = m._m[2][3];

      _m[3][0] = m._m[3][0];
      _m[3][1] = m._m[3][1];
      _m[3][2] = m._m[3][2];
      _m[3][3] = m._m[3][3];

      return *this;

    }

    [[nodiscard]]
      T operator() (size_t i, size_t j) const { return _m[i][j]; }

  private:

    T _m[4][4];

};

/**
 * Redirection operator to display the matrix.
 * @tparam T the underlying data type for the calculation.
 * @param out the output stream.
 * @param m the matrix to display.
 * @return the output stream with a representation of the input matrix.
 */
template <typename T>
std::ostream &operator << (std::ostream &out, const Matrix4x4<T> m) {

  out << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " " << m(0, 3) << std::endl;
  out << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " " << m(1, 3) << std::endl;
  out << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " " << m(2, 3) << std::endl;
  out << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << " " << m(3, 3) << std::endl;

  return out;

}

/**
 * Matrix addition operator.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the sum.
 * @param v the matrix on the right hand side of the sum.
 * @return the sum of the two input matrices.
 */
template <typename T>
Matrix4x4<T> operator+ (const Matrix4x4<T> &u, const Matrix4x4<T> &v) {

  return {{u(0, 0) + v(0, 0), u(0, 1) + v(0, 1), u(0, 2) + v(0, 2), u(0, 3) + v(0, 3) },
    {u(1, 0) + v(1, 0), u(1, 1) + v(1, 1), u(1, 2) + v(1, 2), u(1, 3) + v(1, 3) },
    {u(2, 0) + v(2, 0), u(2, 1) + v(2, 1), u(2, 2) + v(2, 2), u(2, 3) + v(2, 3) },
    {u(3, 0) + v(3, 0), u(3, 1) + v(3, 1), u(3, 2) + v(3, 2), u(3, 3) + v(3, 3) }
  };

}

/**
 * Matrix subtraction operator.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the sum.
 * @param v the matrix on the right hand side of the sum.
 * @return the difference of the two input matrices.
 */
template <typename T>
Matrix4x4<T> operator- (const Matrix4x4<T> &u, const Matrix4x4<T> &v) {

  return {{u(0, 0) - v(0, 0), u(0, 1) - v(0, 1), u(0, 2) - v(0, 2), u(0, 3) - v(0, 3) },
    {u(1, 0) - v(1, 0), u(1, 1) - v(1, 1), u(1, 2) - v(1, 2), u(1, 3) - v(1, 3) },
    {u(2, 0) - v(2, 0), u(2, 1) - v(2, 1), u(2, 2) - v(2, 2), u(2, 3) - v(2, 3) },
    {u(3, 0) - v(3, 0), u(3, 1) - v(3, 1), u(3, 2) - v(3, 2), u(3, 3) - v(3, 3) }
  };

}

/**
 * Scalar-matrix product operator.
 * @tparam T the underlying data type for the calculation.
 * @param lambda the scalar on the right hand side of the product.
 * @param v the matrix on the left hand side of the product.
 * @return the matrix-scalar product.
 */
template <typename T>
Matrix4x4<T> operator*(T lambda, const Matrix4x4<T> &v) {

  return {{lambda * v(0, 0), lambda * v(0, 1), lambda * v(0, 2), lambda * v(0, 3)},
    {lambda * v(1, 0), lambda * v(1, 1), lambda * v(1, 2), lambda * v(1, 3)},
    {lambda * v(2, 0), lambda * v(2, 1), lambda * v(2, 2), lambda * v(2, 3)},
    {lambda * v(3, 0), lambda * v(3, 1), lambda * v(3, 2), lambda * v(3, 3)}};

}

/**
 * Matrix-scalar product operator.
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the product.
 * @param lambda the scalar on the right hand side of the product.
 * @return the matrix-scalar product.
 */
template <typename T>
Matrix4x4<T> operator*(const Matrix4x4<T> &v, T lambda) {

  return {{v(0, 0) * lambda, v(0, 1) * lambda, v(0, 2) * lambda, v(0, 3) * lambda},
    {v(1, 0) * lambda, v(1, 1) * lambda, v(1, 2) * lambda, v(1, 3) * lambda},
    {v(2, 0) * lambda, v(2, 1) * lambda, v(2, 2) * lambda, v(2, 3) * lambda},
    {v(3, 0) * lambda, v(3, 1) * lambda, v(3, 2) * lambda, v(3, 3) * lambda}};

}

/**
 * Matrix-scalar division operator.
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the product.
 * @param lambda the scalar on the right hand side of the product.
 * @return the matrix-scalar division.
 */
template <typename T>
Matrix4x4<T> operator/(const Matrix4x4<T> &v, T lambda) {

  return {{v(0, 0) / lambda, v(0, 1) / lambda, v(0, 2) / lambda, v(0, 3) / lambda},
    {v(1, 0) / lambda, v(1, 1) / lambda, v(1, 2) / lambda, v(1, 3) / lambda},
    {v(2, 0) / lambda, v(2, 1) / lambda, v(2, 2) / lambda, v(2, 3) / lambda},
    {v(3, 0) / lambda, v(3, 1) / lambda, v(3, 2) / lambda, v(3, 3) / lambda}};

}

/**
 * Matrix-vector multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix on the left hand side of the multiplication.
 * @param v the vector on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template <typename T>
Vector4D<T> operator*(const Matrix4x4<T> &m, const Vector4D<T> &v) {

  return {m(0, 3)*v.w() + m(0, 0)*v.x() + m(0, 1)*v.y() + m(0, 2)*v.z(),
    m(1, 3)*v.w() + m(1, 0)*v.x() + m(1, 1)*v.y() + m(1, 2)*v.z(),
    m(2, 3)*v.w() + m(2, 0)*v.x() + m(2, 1)*v.y() + m(2, 2)*v.z(),
    m(3, 3)*v.w() + m(3, 0)*v.x() + m(3, 1)*v.y() + m(3, 2)*v.z()};

}

/**
 * Vector-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param v the vector on the left hand side of the multiplication.
 * @param m the matrix on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template <typename T>
Vector4D<T> operator*(const Vector4D<T> &v, const Matrix4x4<T> &m) {

  return {m(3, 0)*v.w() + m(0, 0)*v.x() + m(1, 0)*v.y() + m(2, 0)*v.z(),
    m(3, 1)*v.w() + m(0, 1)*v.x() + m(1, 1)*v.y() + m(2, 1)*v.z(),
    m(3, 2)*v.w() + m(0, 2)*v.x() + m(1, 2)*v.y() + m(2, 2)*v.z(),
    m(3, 3)*v.w() + m(0, 3)*v.x() + m(1, 3)*v.y() + m(2, 3)*v.z()};

}

/**
 * Matrix-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m0 the matrix on the left hand side of the multiplication.
 * @param m1 the matrix on the right hand side of the multiplication.
 * @return the matrix-matrix multiplication.
 */
template <typename T>
Matrix4x4<T> operator *(const Matrix4x4<T> &m0, const Matrix4x4<T> &m1) {

  return{{m0(0, 0)*m1(0, 0) + m0(0, 1)*m1(1, 0) + m0(0, 2)*m1(2, 0) + m0(0, 3)*m1(3, 0),
    m0(0, 0)*m1(0, 1) + m0(0, 1)*m1(1, 1) + m0(0, 2)*m1(2, 1) + m0(0, 3)*m1(3, 1),
    m0(0, 0)*m1(0, 2) + m0(0, 1)*m1(1, 2) + m0(0, 2)*m1(2, 2) + m0(0, 3)*m1(3, 2),
    m0(0, 0)*m1(0, 3) + m0(0, 1)*m1(1, 3) + m0(0, 2)*m1(2, 3) + m0(0, 3)*m1(3, 3)},

    {m0(1, 0)*m1(0, 0) + m0(1, 1)*m1(1, 0) + m0(1, 2)*m1(2, 0) + m0(1, 3)*m1(3, 0),
      m0(1, 0)*m1(0, 1) + m0(1, 1)*m1(1, 1) + m0(1, 2)*m1(2, 1) + m0(1, 3)*m1(3, 1),
      m0(1, 0)*m1(0, 2) + m0(1, 1)*m1(1, 2) + m0(1, 2)*m1(2, 2) + m0(1, 3)*m1(3, 2),
      m0(1, 0)*m1(0, 3) + m0(1, 1)*m1(1, 3) + m0(1, 2)*m1(2, 3) + m0(1, 3)*m1(3, 3)},

    {m0(2, 0)*m1(0, 0) + m0(2, 1)*m1(1, 0) + m0(2, 2)*m1(2, 0) + m0(2, 3)*m1(3, 0),
      m0(2, 0)*m1(0, 1) + m0(2, 1)*m1(1, 1) + m0(2, 2)*m1(2, 1) + m0(2, 3)*m1(3, 1),
      m0(2, 0)*m1(0, 2) + m0(2, 1)*m1(1, 2) + m0(2, 2)*m1(2, 2) + m0(2, 3)*m1(3, 2),
      m0(2, 0)*m1(0, 3) + m0(2, 1)*m1(1, 3) + m0(2, 2)*m1(2, 3) + m0(2, 3)*m1(3, 3)},

    {m0(3, 0)*m1(0, 0) + m0(3, 1)*m1(1, 0) + m0(3, 2)*m1(2, 0) + m0(3, 3)*m1(3, 0),
      m0(3, 0)*m1(0, 1) + m0(3, 1)*m1(1, 1) + m0(3, 2)*m1(2, 1) + m0(3, 3)*m1(3, 1),
      m0(3, 0)*m1(0, 2) + m0(3, 1)*m1(1, 2) + m0(3, 2)*m1(2, 2) + m0(3, 3)*m1(3, 2),
      m0(3, 0)*m1(0, 3) + m0(3, 1)*m1(1, 3) + m0(3, 2)*m1(2, 3) + m0(3, 3)*m1(3, 3)}};

}

/**
 * Matrix adjugate.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix adjugate.
 */
template <typename T>
Matrix4x4<T> adj(const Matrix4x4<T> &m) {

  return {
    {-(m(1, 3)*m(2, 2)*m(3, 1)) + m(1, 2)*m(2, 3)*m(3, 1) + m(1, 3)*m(2, 1)*m(3, 2) - m(1, 1)*m(2, 3)*m(3, 2) - m(1, 2)*m(2, 1)*m(3, 3) + m(1, 1)*m(2, 2)*m(3, 3),
      m(0, 3)*m(2, 2)*m(3, 1)  - m(0, 2)*m(2, 3)*m(3, 1) - m(0, 3)*m(2, 1)*m(3, 2) + m(0, 1)*m(2, 3)*m(3, 2) + m(0, 2)*m(2, 1)*m(3, 3) - m(0, 1)*m(2, 2)*m(3, 3),
      -(m(0, 3)*m(1, 2)*m(3, 1)) + m(0, 2)*m(1, 3)*m(3, 1) + m(0, 3)*m(1, 1)*m(3, 2) - m(0, 1)*m(1, 3)*m(3, 2) - m(0, 2)*m(1, 1)*m(3, 3) + m(0, 1)*m(1, 2)*m(3, 3),
      m(0, 3)*m(1, 2)*m(2, 1)  - m(0, 2)*m(1, 3)*m(2, 1) - m(0, 3)*m(1, 1)*m(2, 2) + m(0, 1)*m(1, 3)*m(2, 2) + m(0, 2)*m(1, 1)*m(2, 3) - m(0, 1)*m(1, 2)*m(2, 3)},

      {  m(1, 3)*m(2, 2)*m(3, 0)  - m(1, 2)*m(2, 3)*m(3, 0) - m(1, 3)*m(2, 0)*m(3, 2) + m(1, 0)*m(2, 3)*m(3, 2) + m(1, 2)*m(2, 0)*m(3, 3) - m(1, 0)*m(2, 2)*m(3, 3),
        -(m(0, 3)*m(2, 2)*m(3, 0)) + m(0, 2)*m(2, 3)*m(3, 0) + m(0, 3)*m(2, 0)*m(3, 2) - m(0, 0)*m(2, 3)*m(3, 2) - m(0, 2)*m(2, 0)*m(3, 3) + m(0, 0)*m(2, 2)*m(3, 3),
        m(0, 3)*m(1, 2)*m(3, 0)  - m(0, 2)*m(1, 3)*m(3, 0) - m(0, 3)*m(1, 0)*m(3, 2) + m(0, 0)*m(1, 3)*m(3, 2) + m(0, 2)*m(1, 0)*m(3, 3) - m(0, 0)*m(1, 2)*m(3, 3),
        -(m(0, 3)*m(1, 2)*m(2, 0)) + m(0, 2)*m(1, 3)*m(2, 0) + m(0, 3)*m(1, 0)*m(2, 2) - m(0, 0)*m(1, 3)*m(2, 2) - m(0, 2)*m(1, 0)*m(2, 3) + m(0, 0)*m(1, 2)*m(2, 3)},

      {-(m(1, 3)*m(2, 1)*m(3, 0)) + m(1, 1)*m(2, 3)*m(3, 0) + m(1, 3)*m(2, 0)*m(3, 1) - m(1, 0)*m(2, 3)*m(3, 1) - m(1, 1)*m(2, 0)*m(3, 3) + m(1, 0)*m(2, 1)*m(3, 3),
        m(0, 3)*m(2, 1)*m(3, 0)  - m(0, 1)*m(2, 3)*m(3, 0) - m(0, 3)*m(2, 0)*m(3, 1) + m(0, 0)*m(2, 3)*m(3, 1) + m(0, 1)*m(2, 0)*m(3, 3) - m(0, 0)*m(2, 1)*m(3, 3),
        -(m(0, 3)*m(1, 1)*m(3, 0)) + m(0, 1)*m(1, 3)*m(3, 0) + m(0, 3)*m(1, 0)*m(3, 1) - m(0, 0)*m(1, 3)*m(3, 1) - m(0, 1)*m(1, 0)*m(3, 3) + m(0, 0)*m(1, 1)*m(3, 3),
        m(0, 3)*m(1, 1)*m(2, 0)  - m(0, 1)*m(1, 3)*m(2, 0) - m(0, 3)*m(1, 0)*m(2, 1) + m(0, 0)*m(1, 3)*m(2, 1) + m(0, 1)*m(1, 0)*m(2, 3) - m(0, 0)*m(1, 1)*m(2, 3)},

      {  m(1, 2)*m(2, 1)*m(3, 0)  - m(1, 1)*m(2, 2)*m(3, 0) - m(1, 2)*m(2, 0)*m(3, 1) + m(1, 0)*m(2, 2)*m(3, 1) + m(1, 1)*m(2, 0)*m(3, 2) - m(1, 0)*m(2, 1)*m(3, 2),
        -(m(0, 2)*m(2, 1)*m(3, 0)) + m(0, 1)*m(2, 2)*m(3, 0) + m(0, 2)*m(2, 0)*m(3, 1) - m(0, 0)*m(2, 2)*m(3, 1) - m(0, 1)*m(2, 0)*m(3, 2) + m(0, 0)*m(2, 1)*m(3, 2),
        m(0, 2)*m(1, 1)*m(3, 0)  - m(0, 1)*m(1, 2)*m(3, 0) - m(0, 2)*m(1, 0)*m(3, 1) + m(0, 0)*m(1, 2)*m(3, 1) + m(0, 1)*m(1, 0)*m(3, 2) - m(0, 0)*m(1, 1)*m(3, 2),
        -(m(0, 2)*m(1, 1)*m(2, 0)) + m(0, 1)*m(1, 2)*m(2, 0) + m(0, 2)*m(1, 0)*m(2, 1) - m(0, 0)*m(1, 2)*m(2, 1) - m(0, 1)*m(1, 0)*m(2, 2) + m(0, 0)*m(1, 1)*m(2, 2)}
  };

}

/**
 * Matrix determinant.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix determinant.
 */
template <typename T>
T det(const Matrix4x4<T> &m) {

  return m(0, 3)*m(1, 2)*m(2, 1)*m(3, 0) - m(0, 2)*m(1, 3)*m(2, 1)*m(3, 0) -
    m(0, 3)*m(1, 1)*m(2, 2)*m(3, 0) + m(0, 1)*m(1, 3)*m(2, 2)*m(3, 0) +
    m(0, 2)*m(1, 1)*m(2, 3)*m(3, 0) - m(0, 1)*m(1, 2)*m(2, 3)*m(3, 0) -
    m(0, 3)*m(1, 2)*m(2, 0)*m(3, 1) + m(0, 2)*m(1, 3)*m(2, 0)*m(3, 1) +
    m(0, 3)*m(1, 0)*m(2, 2)*m(3, 1) - m(0, 0)*m(1, 3)*m(2, 2)*m(3, 1) -
    m(0, 2)*m(1, 0)*m(2, 3)*m(3, 1) + m(0, 0)*m(1, 2)*m(2, 3)*m(3, 1) +
    m(0, 3)*m(1, 1)*m(2, 0)*m(3, 2) - m(0, 1)*m(1, 3)*m(2, 0)*m(3, 2) -
    m(0, 3)*m(1, 0)*m(2, 1)*m(3, 2) + m(0, 0)*m(1, 3)*m(2, 1)*m(3, 2) +
    m(0, 1)*m(1, 0)*m(2, 3)*m(3, 2) - m(0, 0)*m(1, 1)*m(2, 3)*m(3, 2) -
    m(0, 2)*m(1, 1)*m(2, 0)*m(3, 3) + m(0, 1)*m(1, 2)*m(2, 0)*m(3, 3) +
    m(0, 2)*m(1, 0)*m(2, 1)*m(3, 3) - m(0, 0)*m(1, 2)*m(2, 1)*m(3, 3) -
    m(0, 1)*m(1, 0)*m(2, 2)*m(3, 3) + m(0, 0)*m(1, 1)*m(2, 2)*m(3, 3);

}

/**
 * Matrix transpose.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix transpose.
 */
template <typename T>
Matrix4x4<T> tr(const Matrix4x4<T> &m) {

  return {{m(0, 0), m(1, 0), m(2, 0), m(3, 0)},
    {m(0, 1), m(1, 1), m(2, 1), m(3, 1)},
    {m(0, 2), m(1, 2), m(2, 2), m(3, 2)},
    {m(0, 3), m(1, 3), m(2, 3), m(3, 3)}};

}

/**
 * Matrix-matrix Frobenius (dot) product.
 * @tparam T the underlying data type for the calculation.
 * @param m0 the matrix on the left hand side of the dot product.
 * @param m1 the matrix on the right hand side of the dot product.
 * @return the matrix-vector multiplication.
 */
template <typename T>
T dot(const Matrix4x4<T> &m0, const Matrix4x4<T> &m1) {

  return
    m0(0, 0)*m1(0, 0) + m0(0, 1)*m1(0, 1) + m0(0, 2)*m1(0, 2) + m0(0, 3)*m1(0, 3) +
    m0(1, 0)*m1(1, 0) + m0(1, 1)*m1(1, 1) + m0(1, 2)*m1(1, 2) + m0(1, 3)*m1(1, 3) +
    m0(2, 0)*m1(2, 0) + m0(2, 1)*m1(2, 1) + m0(2, 2)*m1(2, 2) + m0(2, 3)*m1(2, 3) +
    m0(3, 0)*m1(3, 0) + m0(3, 1)*m1(3, 1) + m0(3, 2)*m1(3, 2) + m0(3, 3)*m1(3, 3);
}

/**
 * Matrix Frobenius product.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix Frobenius norm.
 */
template <typename T>
T norm(const Matrix4x4<T> &m) {

  return sqrt(dot(m, m));

}

/**
 * Matrix diagonal.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix from which to extract the diagonal.
 * @return the matrix diagonal.
 */
template <typename T>
Vector4D<T> diag(const Matrix4x4<T> &m) {

  return {m(0, 0), m(1, 1), m(2, 2), m(3, 3)};

}

/**
 * Matrix trace.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix for which to compute the trace.
 * @return the matrix trace.
 */
template <typename T>
T trace(const Matrix4x4<T> &m) {

  return m(0, 0) + m(1, 1) + m(2, 2) + m(3, 3);

}

/**
 * Create a column matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @param v3 the third vector
 * @param v4 the fourth vector
 * @return the column matrix formed from v1, v2, v3 & v4
 */
template<typename T>
Matrix4x4<T> column_matrix(
    const Vector4D<T> &v1,
    const Vector4D<T> &v2,
    const Vector4D<T> &v3,
    const Vector4D<T> &v4
    ) {
  return {
    {v1.x(), v2.x(), v3.x(), v4.x()},
    {v1.y(), v2.y(), v3.y(), v4.y()},
    {v1.z(), v2.z(), v3.z(), v4.z()},
    {v1.w(), v2.w(), v3.w(), v4.w()}
  };
}

/**
 * Create a row matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @param v3 the third vector
 * @param v4 the fourth vector
 * @return the row matrix formed from v1, v2, v3 & v4
 */
template<typename T>
Matrix4x4<T> row_matrix(
    const Vector4D<T> &v1,
    const Vector4D<T> &v2,
    const Vector4D<T> &v3,
    const Vector4D<T> &v4
    ) {
  return {
    {v1.x(), v1.y(), v1.z(), v1.w()},
    {v2.x(), v2.y(), v2.z(), v2.w()},
    {v3.x(), v3.y(), v3.z(), v3.w()},
    {v4.x(), v4.y(), v4.z(), v4.w()}
  };
}

#endif //LIBFABBRI_MATRIX4X4_HPP
