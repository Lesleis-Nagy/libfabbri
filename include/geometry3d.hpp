//
// Created by Lesleis Nagy on 20/03/2024.
//

#ifndef LIBFABBRI_GEOMETRY3D_HPP
#define LIBFABBRI_GEOMETRY3D_HPP

#include "vector3d.hpp"

/**
 * Return the edge_length between two vector endpoints.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param lhs vector representing the start point of the edge.
 * @param rhs vector representing the end point of the edge.
 * @return the length of the edge.
 */
template <typename T>
T edge_length(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {

    return norm(lhs - rhs);

}

/**
 * Return the edge center between two vector endpoints.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *          'mpreal'.
 * @param r1 vector representing the start point of the edge.
 * @param r2 vector representing the end point of the edge.
 * @return the vector representing the center point of the edge.
 */
template <typename T>
Vector3D<T> edge_center(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    return (r1 + r2) / 2.0;

}

/**
 * Return the edge center between two vector endpoints - mpreal specific version.
 * @param r1 vector representing the start point of the edge.
 * @param r2 vector representing the end point of the edge.
 * @return the vector representing the center point of the edge.
 */
template <>
Vector3D<mpfr::mpreal> edge_center(const Vector3D<mpfr::mpreal> &r1, const Vector3D<mpfr::mpreal> &r2) {
    using mpfr::mpreal;

    return (r1 + r2) / mpreal(2.0);

}

/**
 * Return the orientation vector between two vector end points; this is the unit
 * vector pointing from \f$r_1\f$ to
 * \f$r_2\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 vector representing the start point of the edge.
 * @param r2 vector representing the end point of the edge.
 * @return the unit vector pointing from \f$r_1\f$ to \f$r_2\f$.
 */
template <typename T>
Vector3D<T> edge_orientation(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    return normalised( r2 - r1 );

}

/**
 * Return the triangle normal vector assuming vertex clockwise winding
 * \f$ r_1 \rightarrow r_2 \f$, \f$ r_2 \rightarrow r_3 \f$ and
 * \f$ r_3 \rightarrow r_1 \f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 vector representing a point on the triangle.
 * @param r2 vector representing a point on the triangle.
 * @param r3 vector representing a point on the triangle.
 * @return the triangle normal vector.
 */
template <typename T>
Vector3D<T> triangle_normal(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    return normalised(cross(r2 - r1, r3 - r1));

}

/**
 * Return the triangle center vector.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 * @param r1 vector representing a point on the triangle.
 * @param r2 vector representing a point on the triangle.
 * @param r3 vector representing a point on the triangle.
 * @return the triangle center vector.
 */
template <typename T>
Vector3D<T> triangle_center(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    Vector3D<T> sum = (r1 + r2) + r3;
    return sum / 3.0;

}

/**
 * Return the triangle center vector - mpreal specific version.
 * @param r1 vector representing a point on the triangle.
 * @param r2 vector representing a point on the triangle.
 * @param r3 vector representing a point on the triangle.
 * @return the triangle center vector.
 */
template <>
Vector3D<mpfr::mpreal> triangle_center(const Vector3D<mpfr::mpreal> &r1,
                                       const Vector3D<mpfr::mpreal> &r2,
                                       const Vector3D<mpfr::mpreal> &r3) {
    using mpfr::mpreal;

    Vector3D<mpreal> sum = (r1 + r2) + r3;
    return sum / mpreal(3.0);

}

#endif //LIBFABBRI_GEOMETRY3D_HPP
