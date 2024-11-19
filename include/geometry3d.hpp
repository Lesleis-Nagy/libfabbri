//
// Created by Lesleis Nagy on 20/03/2024.
//

#ifndef LIBFABBRI_GEOMETRY3D_HPP
#define LIBFABBRI_GEOMETRY3D_HPP

#include "vector3d.hpp"
#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

/**
 * Return the edge_length between two vector endpoints.
 * @tparam T the underlying data type for the calculation.
 * @param lhs vector representing the start point of the edge.
 * @param rhs vector representing the end point of the edge.
 * @return the length of the edge.
 */
template<typename T>
T edge_length(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {

  return norm(lhs - rhs);

}

/**
 * Return the edge center between two vector endpoints.
 * @tparam T the underlying data type for the calculation.
 * @param r1 vector representing the start point of the edge.
 * @param r2 vector representing the end point of the edge.
 * @return the vector representing the center point of the edge.
 */
template<typename T>
Vector3D<T> edge_center(const Vector3D<T> &r1, const Vector3D<T> &r2) {

  return (r1 + r2) / T(2.0);

}

/**
 * Return the orientation vector between two vector end points; this is the unit
 * vector pointing from \f$r_1\f$ to
 * \f$r_2\f$.
 * @tparam T the underlying data type for the calculation.
 * @param r1 vector representing the start point of the edge.
 * @param r2 vector representing the end point of the edge.
 * @return the unit vector pointing from \f$r_1\f$ to \f$r_2\f$.
 */
template<typename T>
Vector3D<T> edge_orientation(const Vector3D<T> &r1, const Vector3D<T> &r2) {

  return normalised(r2 - r1);

}

/**
 * Return the triangle normal vector assuming vertex clockwise winding
 * \f$ r_1 \rightarrow r_2 \f$, \f$ r_2 \rightarrow r_3 \f$ and
 * \f$ r_3 \rightarrow r_1 \f$.
 * @tparam T the underlying data type for the calculation.
 * @param r1 vector representing a point on the triangle.
 * @param r2 vector representing a point on the triangle.
 * @param r3 vector representing a point on the triangle.
 * @return the triangle normal vector.
 */
template<typename T>
Vector3D<T> triangle_normal(const Vector3D<T> &r1,
                            const Vector3D<T> &r2,
                            const Vector3D<T> &r3) {

  return normalised(cross(r2 - r1, r3 - r1));

}

/**
 * Return the triangle center vector.
 * @tparam T the underlying data type for the calculation.
 * @param r1 vector representing a point on the triangle.
 * @param r2 vector representing a point on the triangle.
 * @param r3 vector representing a point on the triangle.
 * @return the triangle center vector.
 */
template<typename T>
Vector3D<T> triangle_center(const Vector3D<T> &r1,
                            const Vector3D<T> &r2,
                            const Vector3D<T> &r3) {

  Vector3D<T> sum = (r1 + r2) + r3;
  return sum / T(3.0);

}

/**
 * Retrieves a rotation matrix using the axis/angle formulation.
 * @tparam T the underlying data type for the calculation.
 * @param v the axis vector of rotation.
 * @param theta the angle of rotation in radians.
 * @return a 3x3 matrix that will perform an `angle` degree rotation about the
 *         given axis `v`.
 */
template<typename T>
Matrix3x3<T>
rotation3x3(const Vector3D<T> &v, const T &theta) {

  auto u = normalised(v);

  auto one_minus_cos_theta = 1 - cos(theta);
  auto sin_theta = sin(theta);
  auto cos_theta = cos(theta);

  return {

      // First row
      {
          cos_theta + u.x() * u.x() * one_minus_cos_theta,
          u.x() * u.y() * one_minus_cos_theta - u.z() * sin_theta,
          u.x() * u.z() * one_minus_cos_theta + u.y() * sin_theta
      },

      // Second row
      {
          u.y() * u.x() * one_minus_cos_theta + u.z() * sin_theta,
          cos_theta + u.y() * u.y() * one_minus_cos_theta,
          u.y() * u.z() * one_minus_cos_theta - u.x() * sin_theta
      },

      // Third row
      {
          u.z() * u.x() * one_minus_cos_theta - u.y() * sin_theta,
          u.z() * u.y() * one_minus_cos_theta + u.x() * sin_theta,
          cos_theta + u.z() * u.z() * one_minus_cos_theta
      }

  };

}

/**
 * Retrieves a homogenous rotation matrix using the axis/angle formulation.
 * @tparam T the underlying data type for the calculation.
 * @param v the axis 3D vector of rotation.
 * @param theta the angle of rotation in radians.
 * @return a homogenous 4x4 matrix that will perform an `angle` degree rotation
 *         about the given axis `v`.
 */
template<typename T>
Matrix4x4<T>
rotation4x4(const Vector3D<T> &v, const T &theta) {

  auto m = rotation3x3(v, theta);

  return {
      {m(0, 0), m(0, 1), m(0, 2), 0},
      {m(1, 0), m(1, 1), m(1, 2), 0},
      {m(2, 0), m(2, 1), m(2, 2), 0},
      {      0,       0,       0, 1}
  };

}

/**
 * Retrieves a homogenous rotation matrix using the axis/angle formulation.
 * @tparam T the underlying data type for the calculation.
 * @param v the axis 4D vector of rotation.
 * @param theta the angle of rotation in radians.
 * @return a homogenous 4x4 matrix that will perform an `angle` degree rotation
 *         about the given axis `v`.
 */
template<typename T>
Matrix4x4<T>
rotation4x4(const Vector4D<T> &v, const T &theta) {

  auto m = rotation3x3({v.x(), v.y(), v.z()}, theta);

  return {
      {m(0, 0), m(0, 1), m(0, 2), 0},
      {m(1, 0), m(1, 1), m(1, 2), 0},
      {m(2, 0), m(2, 1), m(2, 2), 0},
      {      0,       0,       0, 1}
  };

}

#endif //LIBFABBRI_GEOMETRY3D_HPP
