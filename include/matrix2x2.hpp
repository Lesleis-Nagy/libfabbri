//
// Created by Lesleis Nagy on 18/03/2024.
//

#ifndef LIBFABBRI_MATRIX2X2_HPP
#define LIBFABBRI_MATRIX2X2_HPP

#include <cassert>

#include "vector2d.hpp"

/**
 * An implementation of a three by three square matrix.
 */
template <typename T>
class Matrix2x2 {

public:

    /**
     * Create a 2x2 zero-matrix.
     */
    Matrix2x2():
    _m{{0.0, 0.0}, {0.0, 0.0}}
    {}

    /**
     * Create a 2x2 matrix from an input.
     */
    Matrix2x2(std::initializer_list<std::initializer_list<T>> m) {

        assert(m.size() == 2 && "Number of rows must be 2.");

        auto outerIterator = m.begin();
        auto innerIterator = outerIterator->begin();

        assert(outerIterator->size() == 2 && "Number of columns must be 2.");
        _m[0][0] = *innerIterator++;
        _m[0][1] = *innerIterator++;

        outerIterator++;
        innerIterator = outerIterator->begin();

        assert(outerIterator->size() == 2 && "Number of columns must be 2.");
        _m[1][0] = *innerIterator++;
        _m[1][1] = *innerIterator++;

    }

    Matrix2x2& operator=(const Matrix2x2 &m) {

        if (this == &m) return *this;
        _m[0][0] = m._m[0][0];
        _m[0][1] = m._m[0][1];

        _m[1][0] = m._m[1][0];
        _m[1][1] = m._m[1][1];

        return *this;

    }

    [[nodiscard]]
    T operator() (size_t i, size_t j) const { return _m[i][j]; }

private:

    T _m[2][2];

};

/**
 * Redirection operator to display the matrix.
 * @tparam T the underlying data type for the calculation.
 * @param out the output stream.
 * @param m the matrix to display.
 * @return the output stream with a representation of the input matrix.
 */
template <typename T>
std::ostream &operator << (std::ostream &out, const Matrix2x2<T> m) {

    out << m(0, 0) << " " << m(0, 1) << std::endl;
    out << m(1, 0) << " " << m(1, 1) << std::endl;

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
Matrix2x2<T> operator+ (const Matrix2x2<T> &u, const Matrix2x2<T> &v) {

    return {{u(0, 0) + v(0, 0), u(0, 1) + v(0, 1)},
            {u(1, 0) + v(1, 0), u(1, 1) + v(1, 1)}};

}

/**
 * Matrix subtraction operator.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the operator.
 * @param v the matrix on the right hand side of the operator.
 * @return the difference of two input matrices.
 */
template <typename T>
Matrix2x2<T> operator- (const Matrix2x2<T> &u, const Matrix2x2<T> &v) {

    return {{u(0, 0) - v(0, 0), u(0, 1) - v(0, 1)},
            {u(1, 0) - v(1, 0), u(1, 1) - v(1, 1)}};

}

/**
 * Matrix-scalar product operator
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the product.
 * @param lambda the scalar on the right hand side of the product.
 * @return the matrix-scalar product.
 */
template <typename T>
Matrix2x2<T> operator*(const Matrix2x2<T> &v, T lambda) {

    return {{v(0, 0) * lambda, v(0, 1) * lambda},
            {v(1, 0) * lambda, v(1, 1) * lambda}};

}

/**
 * Scalar-matrix product operator.
 * @tparam T the underlying data type for the calculation.
 * @param lambda the scalar on the left hand side of the product.
 * @param v the matrix on the right hand side of the product.
 * @return the scalar-matrix product.
 */
template <typename T>
Matrix2x2<T> operator*(T lambda, const Matrix2x2<T> &v) {

    return {{lambda * v(0, 0), lambda *  v(0, 1)},
            {lambda * v(1, 0), lambda *  v(1, 1)}};

}

/**
 * Matrix-scalar division.
 * @tparam T the underlying data type for the calculation.
 * @param v the matrix on the left hand side of the division.
 * @param lambda the scalar on the right hand side of the division.
 * @return the matrix-scalar division.
 */
template <typename T>
Matrix2x2<T> operator/(const Matrix2x2<T> &v, T lambda) {

    return {{v(0, 0) / lambda, v(0, 1) / lambda},
            {v(1, 0) / lambda, v(1, 1) / lambda}};

}

/**
 * Matrix-vector multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix on the left hand side of the multiplication.
 * @param v the vector on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template <typename T>
Vector2D<T> operator*(const Matrix2x2<T> &m, const Vector2D<T> &v) {

    return {m(0, 0)*v.x() + m(0, 1)*v.y(),
            m(1, 0)*v.x() + m(1, 1)*v.y()};

}

/**
 * Vector-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param v the vector on the left hand side of the multiplication.
 * @param m the matrix on the right hand side of the multiplication.
 * @return the matrix-vector multiplication.
 */
template <typename T>
Vector2D<T> operator*(const Vector2D<T> &v, const Matrix2x2<T> &m) {

    return {m(0, 0)*v.x() + m(1, 0)*v.y(),
            m(0, 1)*v.x() + m(1, 1)*v.y()};

}

/**
 * Matrix-matrix multiplication.
 * @tparam T the underlying data type for the calculation.
 * @param m0 the matrix on the left hand side of the multiplication.
 * @param m1 the matrix on the right hand side of the multiplication.
 * @return the matrix-matrix multiplication.
 */
template <typename T>
Matrix2x2<T> operator *(const Matrix2x2<T> &m0, const Matrix2x2<T> &m1) {

    return {{m0(0, 0) * m1(0, 0) + m0(0, 1) * m1(1, 0),
             m0(0, 0) * m1(0, 1) + m0(0, 1) * m1(1, 1)},

            {m0(1, 0) * m1(0, 0) + m0(1, 1) * m1(1, 0),
             m0(1, 0) * m1(0, 1) + m0(1, 1) * m1(1, 1)}};

}

/**
 * Matrix adjugate.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix adjugate.
 */
template <typename T>
Matrix2x2<T> adj(const Matrix2x2<T> &m) {

    return {{ m(1,1),-m(0,1)},
            {-m(1,0), m(0,0)}};

}

/**
 * Matrix determinant.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix determinant.
 */
template <typename T>
T det(const Matrix2x2<T> &m) {

    return   m(0,0) * m(1,1) - m(0,1) * m(1,0);

}

/**
 * Matrix transpose.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix.
 * @return the matrix transpose.
 */
template <typename T>
Matrix2x2<T> tr(const Matrix2x2<T> &m) {

    return {{m(0, 0), m(1, 0)},
            {m(0, 1), m(1, 1)}};

}

/**
 * Matrix-matrix Frobenius (dot) product.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix on the left hand side of the dot product.
 * @param v the matrix on the right hand side of the dot product.
 * @return the matrix-vector multiplication.
 */
template <typename T>
T dot(const Matrix2x2<T> &u, const Matrix2x2<T> &v) {

    return u(0, 0) * v(0, 0) + u(0, 1) * v(0, 1)
           + u(1, 0) * v(1, 0) + u(1, 1) * v(1, 1);

}

/**
 * Matrix Frobenius norm.
 * @tparam T the underlying data type for the calculation.
 * @param u the matrix to take the norm of.
 * @return the matrix Frobenius norm.
 */
template <typename T>
T norm(const Matrix2x2<T> &u) {

    return sqrt(dot(u, u));

}

/**
 * Matrix diagonal.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix from which to extract the diagonal.
 * @return the matrix diagonal.
 */
template <typename T>
Vector2D<T> diag(const Matrix2x2<T> &m) {

    return {m(0, 0), m(1, 1)};

}

/**
 * Matrix trace.
 * @tparam T the underlying data type for the calculation.
 * @param m the matrix for which to compute the trace.
 * @return the matrix trace.
 */
template <typename T>
T trace(const Matrix2x2<T> &m) {

    return m(0, 0) + m(1, 1);

}

/**
 * Create a column matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the column matrix formed from v1 and v2
 */
template <typename T>
Matrix2x2<T> column_matrix(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  return {
      {v1.x(), v2.x()},
      {v1.y(), v2.y()}
  };
}

/**
 * Create a row matrix from two input vectors.
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the row matrix formed from v1 and v2
 */
template <typename T>
Matrix2x2<T> row_matrix(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  return {
      {v1.x(), v1.y()},
      {v2.x(), v2.y()}
  };
}

#endif //LIBFABBRI_MATRIX2X2_HPP
