//
// Created by Lesleis Nagy on 26/07/2022.
//

#ifndef LIBFABBRI_VECTOR4D_HPP
#define LIBFABBRI_VECTOR4D_HPP

#include <array>
#include <ostream>
#include <utility>

/**
 * An implementation of a three dimensional cartesian vector.
 * @tparam T the underlying data type for the calculation - usually ‘double’ or
 *           ‘mpreal’.
 */
template <typename T>
class Vector4D {

  public:

    /**
     * Set the regularisation-epsilon value for **all** Vector4D objects of this
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
    Vector4D(): _x{0.0, 0.0, 0.0, 0.0}, _dim(4) {}

    /**
     * Create a three dimensional vector object with the given x, y & z
     * components along with a regularisation-epsilon value.
     * @param x the vector x component.
     * @param y the vector y component.
     * @param z the vector z component.
     * @param w the vector w component.
     */
    Vector4D(T x, T y, T z, T w): _x{x, y, z, w} {}

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
     * Retrieve the vector's z-component.
     * @return the vector's z-component.
     */
    [[nodiscard]] inline T z() const { return _x[2]; }

    /**
     * Retrieve the vector's w-component.
     * @return the vector's w-component.
     */
    [[nodiscard]] inline T w() const { return _x[3]; }

    /**
     * Retrieve the dimension of the vector.
     * @return the dimension of the vector.
     */
    [[nodiscard]] int dim() const { return _dim; }

  private:

    std::array<T, 4> _x;
    int _dim;

    [[maybe_unused]] static T _eps;
    [[maybe_unused]] static T _eps_squared;

};

// Initialize static eps & eps_squared values to defaults for double precision
// arithmetic.
template <typename T>
T Vector4D<T>::_eps = 1E-7;

template <typename T>
T Vector4D<T>::_eps_squared = 1E-14;

/**
 * Redirection operator to display the vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param out the output stream.
 * @param v the vector to display.
 * @return the output stream with a representation of the input vector.
 */
template <typename T>
std::ostream &operator << (std::ostream &out, const Vector4D<T> v) {

  out << "<" << v.x() << ", "
    << v.y() << ", "
    << v.z() << ", "
    << v.w() << ">";

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
Vector4D<T> operator+ (const Vector4D<T> &u, const Vector4D<T> &v) {

  return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z(), u.w() + v.w()};

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
Vector4D<T> operator- (const Vector4D<T> &u, const Vector4D<T> &v) {

  return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z(),  u.w() - v.w()};

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
Vector4D<T> operator*(const Vector4D<T> &v, T lambda) {

  return {v.x() * lambda, v.y() * lambda, v.z() * lambda, v.w() * lambda};

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
Vector4D<T> operator*(T lambda, const Vector4D<T> &v) {

  return {lambda * v.x(), lambda * v.y(), lambda * v.z(), lambda * v.w()};

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
Vector4D<T> operator/(const Vector4D<T> &v, T lambda) {

  return {v.x() / lambda, v.y() / lambda, v.z() / lambda, v.w() / lambda};

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
T dot(const Vector4D<T> &u, const Vector4D<T> &v) {

  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z() + u.w() * v.w();

}

/**
 * The norm of a vector
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector for which we seek the norm.
 * @return the norm of the input vector.
 */
template <typename T>
T norm(const Vector4D<T> &v) {

  return sqrt(dot(v, v) + Vector4D<T>::eps_squared());

}

/**
 * The norm squared of a vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param v the vector for which we seek the norm-squared.
 * @return the norm-squared of the input vector.
 */
template <typename T>
T norm_squared(const Vector4D<T> &v) {

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
Vector4D<T> normalised(const Vector4D<T> &v) {

  T l = norm(v);
  return v / l;

}

/**
 * Compute the additive fold of the vector.
 * @return the additive fold (sum of all vector elements).
 */
template <typename T>
T afold(const Vector4D<T> &v) {
  return v.x() + v.y() + v.z() + v.w();
}

/**
 * Compute the multiplicative fold of the vector.
 * @return the multiplicative fold (product of all vector elements).
 */
template <typename T>
T mfold(const Vector4D<T> &v) {
  return v.x() * v.y() * v.z() * v.w();
}

#endif // LIBFABBRI_VECTOR4D_HPP
