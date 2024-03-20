//
// Created by Lesleis Nagy on 19/03/2024.
//

#ifndef LIBFABBRI_MATRIX4X4_HPP
#define LIBFABBRI_MATRIX4X4_HPP

#include <ostream>
#include <utility>

#include "mpreal.h"

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
    T operator() (size_t i, size_t j) const {
        return _m[i][j];
    }

private:

    T _m[4][4];

};

/**
 * Redirection operator to display the matrix.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param out the output stream.
 * @param v the matrix to display.
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
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
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
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
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
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
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
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
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
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
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

#endif //LIBFABBRI_MATRIX4X4_HPP
