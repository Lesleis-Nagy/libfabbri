//
// Created by Lesleis Nagy on 27/07/2022.
//

/** @file */

#ifndef LIBFABBRI_FABBRI_HPP
#define LIBFABBRI_FABBRI_HPP

#include <array>
#include <functional>

#include "vector3d.hpp"

/**
 * Return a function that will calculate the solid angle subtended by the triangle with vertices \f$r_1\f$, \f$r_2\f$ &
 * \f$r_3\f$ as a as a function of space -- see eq. (21) in Fabbri 2008.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first vertex of the subtending triangle.
 * @param r2 the second vertex of the subtending triangle.
 * @param r3 the third vertex of the subtending triangle.
 * @return a function that will take Vector3D<T> values as input and output the solid angle at the input point
 *         subtended by the triangle with vertices \f$r_1\f$, \f$r_2\f$ & \f$r_3\f$.
 */
template <typename T>
std::function<T (const Vector3D<T>&)>
new_omega_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    return [r1, r2, r3] (const Vector3D<T>& r) {

        Vector3D<T> v1 = (r1 - r);
        Vector3D<T> v2 = (r2 - r);
        Vector3D<T> v3 = (r3 - r);

        T d1 = norm(v1);
        T d2 = norm(v2);
        T d3 = norm(v3);

        return atan2( dot(v1, cross(v2, v3)), d1*d2*d3 + d3*dot(v1, v2) + d2*dot(v1, v3) + d1*dot(v2, v3) ) * 2.0;

    };

}

/**
 * Return a function that will calculate Fabbri's edge potential function \f$w_\mathrm{e}\f$ eq. (18) for a line segment
 * with endpoints \f$r1\f$ & \f$r2\f$ [1].
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$w_\mathrm{e}\f$.
 */
template <typename T>
std::function<T (const Vector3D<T>&)>
new_we_fun(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    T d_const = norm(r2 - r1);

    return [r1, r2, d_const] (const Vector3D<T>& r) {

        T d1 = norm(r1 - r);
        T d2 = norm(r2 - r);

        return log( ( d2 + d1 + d_const ) / ( d2 + d1 - d_const ) );

    };

}

/**
 * Return a function that will calculate Fabbri's face potential function \f$W_\mathrm{f}\f$ eq. (17) for a triangular
 * face [1] with endpoints \f$r_1\f$, \f$r_2\f$ & \f$r_3\f$ with winding \f$r_1 \rightarrow r2\f$,
 * \f$r_2 \rightarrow r_3\f$ & \f$r3 \rightarrow r1\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a triangle segment.
 * @param r2 the second point of a triangle segment.
 * @param r3 the third point of a triangle.
 * @return a function that will calculate \f$W_\mathrm{f}\f$.
 */
template <typename T>
std::function<T (const Vector3D<T>&)>
new_Wf_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    using std::array;

    Vector3D<T> nf = triangle_normal(r1, r2, r3); // Face normal.
    Vector3D<T> rf = triangle_center(r1, r2, r3); // Arbitrary point on the face;

    array<std::function<T(const Vector3D<T> &)>, 3> omega;
    array<std::function<T(const Vector3D<T> &)>, 3> we;

    // The first edge: r1 -> r2.

    // The second edge: r2 -> r3.

    // The third edge: r3 -> r1.

    return [nf, rf, we, omega] {



    };

}

/*
 * References
 * 1.Fabbri, M. Magnetic Flux Density and Vector Potential of Uniform Polyhedral Sources.
 *              Ieee T Magn 44, 32–36 (2008).
 * 2.Fabbri, M. Magnetic flux density and vector potential of linear polyhedral sources.
 *              Compel - Int J Comput Math Electr Electron Eng 28, 1688–1700 (2009).
 */

#endif //LIBFABBRI_FABBRI_HPP
