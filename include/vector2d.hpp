//
// Created by Lesleis Nagy on 26/07/2022.
//

/**
 * @file vector2d.hpp
 * @author L. Nagy
 */

#ifndef LIBFABBRI_VECTOR2D_HPP
#define LIBFABBRI_VECTOR2D_HPP

#include <array>
#include <ostream>
#include <utility>

/**
 * An implementation of a three dimensional cartesian vector.
 * @tparam T the underlying data type for the calculation.
 */
template <typename T>
class Vector2D {

public:

    /**
     * Set the regularisation-epsilon value for **all** Vector2D objects of this
     * type.
     * @param new_eps the new regularisation-epsilon.
     */
    static void set_eps(T new_eps) {

        _eps = new_eps;
        _eps_squared = new_eps * new_eps;

    }

    /**
     * Retrieve the regularisation-epsilon.
     * @return the regularisation-epsilon.
     */
    static T eps() {

        return _eps;

    }

    /**
     * Retrieve the regularisation-epsilon squared.
     * @return the regularisation-epsilon squared.
     */
    static T eps_squared() {

        return _eps_squared;

    }

    /**
     * Create a three dimensional zero-vector object.
     */
    Vector2D(): _x{0.0, 0.0}, _dim(2) {}

    /**
     * Create a three dimensional vector object with the given x, y & z
     * components along with a regularisation-epsilon value.
     * @param x the vector x component.
     * @param y the vector y component.
     */
    Vector2D(T x, T y): _x{x, y} {}

    /**
     * Retrieve the vector's x-component.
     * @return the vector's x-component.
     */
    [[nodiscard]] inline T x() const { return _x[0]; }

    /**
     * Retrieve the vector's y-component.
     * @return the vector's y-component.
     */
    [[nodiscard]] inline T y() const { return _x[1]; }

    /**
     * Retrieve the vector's ith component.
     * @param idx the index of the component.
     * @return the vector component.
     */
    [[nodiscard]] T operator()(size_t idx) const { return _x[idx]; }

    /**
     * Retrieve the dimension of the vector.
     * @return the dimension of the vector.
     */
    [[nodiscard]] int dim() const { return _dim; }


private:

    std::array<T, 2> _x;
    int _dim;

    [[maybe_unused]] static T _eps;
    [[maybe_unused]] static T _eps_squared;

};

// Initialize static eps & eps_squared values to defaults for double precision
// arithmetic.
template <typename T>
T Vector2D<T>::_eps = 1E-7;

template <typename T>
T Vector2D<T>::_eps_squared = 1E-14;

/**
 * Redirection operator to display the vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param out the output stream.
 * @param v the vector to display.
 * @return the output stream with a representation of the input vector.
 */
template <typename T>
std::ostream &operator << (std::ostream &out, const Vector2D<T> v) {

    out << "<" << v.x() << ", " << v.y() << ">";
    return out;

}

/**
 * Vector addition operator.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param u the vector on the left hand side of the sum.
 * @param v the vector on the right hand side of the sum.
 * @return the sum of the two input vectors.
 */
template <typename T>
Vector2D<T> operator+ (const Vector2D<T> &u, const Vector2D<T> &v) {

    return {u.x() + v.x(), u.y() + v.y() };

}

/**
 * Vector subtraction operator.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param u the vector on the left hand side of the operator.
 * @param v the vector on the right hand side of the operator.
 * @return the difference of two input vectors.
 */
template <typename T>
Vector2D<T> operator- (const Vector2D<T> &u, const Vector2D<T> &v) {

    return {u.x() - v.x(), u.y() - v.y() };

}

/**
 * Vector-scalar product operator.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector on the left hand side of the product.
 * @param lambda the scalar on the right hand side of the product.
 * @return the vector-scalar product.
 */
template <typename T>
Vector2D<T> operator*(const Vector2D<T> &v, T lambda) {

    return {lambda * v.x(), lambda * v.y() };

}

/**
 * Scalar-vector product operator.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param lambda the scalar on the left hand side of the product.
 * @param v the vector on the right hand side of the product.
 * @return the scalar-vector product.
 */
template <typename T>
Vector2D<T> operator*(T lambda, const Vector2D<T> &v) {

    return {lambda * v.x(), lambda * v.y() };

}

/**
 * Vector-scalar division.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector on the left hand side of the division.
 * @param lambda the scalar on the right hand side of the division.
 * @return the vector-scalar division.
 */
template <typename T>
Vector2D<T> operator/(const Vector2D<T> &v, T lambda) {

    return {v.x() / lambda, v.y() / lambda };

}

/**
 * Vector dot product.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param u the vector on the left hand side of the dot product.
 * @param v the scalar on the right hand side of the dot product.
 * @return the vector dot product.
 */
template <typename T>
T dot(const Vector2D<T> &u, const Vector2D<T> &v) {

    return u.x() * v.x() + u.y() * v.y();

}

/**
 * Vector cross product.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param u the vector on the left hand side of the cross product.
 * @param v the scalar on the right hand side of the cross product.
 * @return the vector cross product.
 */template <typename T>
T cross(const Vector2D<T> &u, const Vector2D<T> &v)  {

  return u.x() * v.y() - u.y() * v.x();

}

/**
 * The norm of a vector
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector for which we seek the norm.
 * @return the norm of the input vector.
 */
template <typename T>
T norm(const Vector2D<T> &v) {

    return sqrt(dot(v, v) + Vector2D<T>::eps_squared());

}

/**
 * The norm squared of a vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector for which we seek the norm-squared.
 * @return the norm-squared of the input vector.
 */
template <typename T>
T norm_squared(const Vector2D<T> &v) {

    return dot(v, v);

}

/**
 * Produce a normalised version of the input vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector that we seek to normalise.
 * @return the normalised input vector.
 */
template <typename T>
Vector2D<T> normalised(const Vector2D<T> &v) {

    T l = norm(v);
    return v / l;

}

/**
 * Compute the additive fold of the vector.
 * @return the additive fold (sum of all vector elements).
 */
template <typename T>
T afold(const Vector2D<T> &v) {
  return v.x() + v.y();
}

/**
 * Compute the multiplicative fold of the vector.
 * @return the multiplicative fold (product of all vector elements).
 */
template <typename T>
T mfold(const Vector2D<T> &v) {
  return v.x() * v.y();
}

#endif // LIBFABBRI_VECTOR2D_HPP
