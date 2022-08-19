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
template<typename T>
std::function<T(const Vector3D<T> &)>
new_omega_tri_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    return [r1, r2, r3](const Vector3D<T> &r) {

        Vector3D<T> v1 = (r1 - r);
        Vector3D<T> v2 = (r2 - r);
        Vector3D<T> v3 = (r3 - r);

        T d1 = norm(v1);
        T d2 = norm(v2);
        T d3 = norm(v3);

        return 2.0 * atan2(dot(v1, cross(v2, v3)),
                           d1 * d2 * d3 + d3 * dot(v1, v2) + d2 * dot(v1, v3) + d1 * dot(v2, v3));

    };

}

/**
 * Return a function that will calculate the edge potential function \f$w_\mathrm{e}\f$ eq. (18) for a line segment
 * with endpoints \f$r_1\f$ & \f$r_2\f$ [1].
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$w_\mathrm{e}\f$.
 */
template<typename T>
std::function<T(const Vector3D<T> &)>
new_we_fun(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    T d_const = norm(r2 - r1);

    return [r1, r2, d_const](const Vector3D<T> &r) {

        T d1 = norm(r1 - r);
        T d2 = norm(r2 - r);

        return log((d2 + d1 + d_const) / (d2 + d1 - d_const));

    };

}

/**
 * Return a function that will calculate \f$\lambda_\mathrm{e}\f$ in eq. (22) for a line segment with endpoints
 * \f$r_1\f$ and \f$r_2\f$ [2].
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$\lambda_\mathrm{e}\f$.
 */
template<typename T>
std::function<T(const Vector3D<T> &)> new_lambda_e_fun(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    using std::function;

    function we = new_we_fun(r1, r2);
    Vector3D<T> ue = normalised(r2 - r1);
    Vector3D<T> re = edge_center(r1, r2);

    return [r1, r2, we, ue, re](const Vector3D<T> &r) {

        return 0.5 * norm(r2 - r) * dot((r2 - r), ue) + 0.5 * norm(r1 - r) * dot((r1 - r), ue)
               + 0.5 * norm_squared(cross((r - re), ue)) * we(r);

    };

}

/**
 * Return a function that will calculate \f$\nabla \lambda_\mathrm{e}\f$ in eq. (29) for a line segment with endpoints
 * \f$r_1\f$ and \f$r_2\f$ [2].
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$\nabla \lambda_\mathrm{e}\f$.
 */
template<typename T>
std::function<Vector3D<T>(const Vector3D<T> &)> new_D_lambda_e_fun(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    using std::function;

    function we = new_we_fun(r1, r2);
    Vector3D<T> ue = normalised(r2 - r1);
    Vector3D<T> re = edge_center(r1, r2);

    return [r1, r2, we, ue, re](const Vector3D<T> &r) {

        return (norm(r1 - r) - norm(r2 - r)) * ue + cross(ue, cross((r - re), ue)) * we(r);

    };

}

/**
 * Return a function that will calculate \f$\frac{\partial \lambda_\mathrm{e}}{\partial m}\f$ for a line segment with
 * endpoints \f$r_1\f$ and \f$r_2\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$\frac{\partial \lambda_\mathrm{e}}{\partial m}\f$ as a function of
 *         \f$\vec{r}\f$ and \f$\vec{m}\f$.
 */
template<typename T>
std::function<T(const Vector3D<T> &, const Vector3D<T> &)>
new_d_lambda_e_by_dm_fun(const Vector3D<T> &r1, const Vector3D<T> &r2) {

    using std::function;

    function D_lambda_e = new_D_lambda_e_fun(r1, r2);

    return [D_lambda_e](const Vector3D<T> &m, const Vector3D<T> &r) {

        return dot(m, D_lambda_e(r));

    };

}

/**
 * Return a function that will calculate the face-potential function \f$W_\mathrm{f}\f$ eq. (17) for a triangular
 * polyhedron [1] with endpoints \f$r_1\f$, \f$r_2\f$ & \f$r_3\f$ and counter-clockwise winding
 * \f$r_1 \rightarrow r2\f$, \f$r_2 \rightarrow r_3\f$ & \f$r3 \rightarrow r1\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a triangle segment.
 * @param r2 the second point of a triangle segment.
 * @param r3 the third point of a triangle.
 * @return a function that will calculate \f$W_\mathrm{f}\f$.
 */
template<typename T>
std::function<T(const Vector3D<T> &)>
new_Wf_tri_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    using std::array;
    using std::function;

    // Face normal.
    Vector3D<T> nf = triangle_normal(r1, r2, r3);

    // Arbitrary point on the face.
    Vector3D<T> rf = triangle_center(r1, r2, r3);

    // Solid angle subtended by this triangle.
    function<T(const Vector3D<T> &)> omega = new_omega_tri_fun(r1, r2, r3);

    // we functions.
    array<function<T(const Vector3D<T> &)>, 3> we;

    we[0] = new_we_fun(r1, r2);
    we[1] = new_we_fun(r2, r3);
    we[2] = new_we_fun(r3, r1);

    array<Vector3D<T>, 3> re;
    re[0] = edge_center(r1, r2);
    re[1] = edge_center(r2, r3);
    re[2] = edge_center(r3, r1);

    array<Vector3D<T>, 3> ue;
    ue[0] = edge_orientation(r1, r2);
    ue[1] = edge_orientation(r2, r3);
    ue[2] = edge_orientation(r3, r1);

    return [nf, rf, omega, re, ue, we](const Vector3D<T> &r) {

        return dot(cross(nf, re[0] - r), ue[0]) * we[0](r)
               + dot(cross(nf, re[1] - r), ue[1]) * we[1](r)
               + dot(cross(nf, re[2] - r), ue[2]) * we[2](r)
               - dot(rf - r, nf) * omega(r);

    };


}

/**
 * Return a function that will calculate the gradient of Fabbri's face potential function \f$\Delta W_\mathrm{f}\f$ eq.
 * (25) for a triangular polyhedron [1] with endpoints \f$r_1\f$, \f$r_2\f$ & \f$r_3\f$ and winding \f$r_1 \rightarrow r2\f$,
 * \f$r_2 \rightarrow r_3\f$ & \f$r3 \rightarrow r1\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a triangle segment.
 * @param r2 the second point of a triangle segment.
 * @param r3 the third point of a triangle.
 * @return a function that will calculate \f$\Delta W_\mathrm{f}\f$.
 */
template<typename T>
std::function<Vector3D<T>(const Vector3D<T> &)>
new_DWf_tri_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    using std::array;
    using std::function;

    // Face normal.
    Vector3D<T> nf = triangle_normal(r1, r2, r3);

    // Solid angle subtended by this triangle.
    function<T(const Vector3D<T> &)> omega = new_omega_tri_fun(r1, r2, r3);

    // we functions.
    array<function<T(const Vector3D<T> &)>, 3> we;

    we[0] = new_we_fun(r1, r2);
    we[1] = new_we_fun(r2, r3);
    we[2] = new_we_fun(r3, r1);

    array<Vector3D<T>, 3> ue;
    ue[0] = edge_orientation(r1, r2);
    ue[1] = edge_orientation(r2, r3);
    ue[2] = edge_orientation(r3, r1);

    return [nf, omega, ue, we](const Vector3D<T> &r) {

        return cross(nf, ue[0]) * we[0](r)
               + cross(nf, ue[1]) * we[1](r)
               + cross(nf, ue[2]) * we[2](r)
               + nf * omega(r);

    };

}

/**
 * Return a function that will calculate \f$\frac{\partial W_\mathrm{f}}{\partial m}\f$ for a line segment with
 * endpoints \f$r_1\f$ and \f$r_2\f$ [2].
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param r1 the first point of a line segment.
 * @param r2 the second point of a line segment.
 * @return a function that will calculate \f$\nabla \lambda_\mathrm{e}\f$.
 */
template<typename T>
std::function<T(const Vector3D<T> &, const Vector3D<T> &)>
new_d_Wf_by_dm_tri_fun(const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3) {

    using std::function;

    function DWf = new_DWf_tri_fun(r1, r2, r3);

    return [DWf](const Vector3D<T> &m, const Vector3D<T> &r) {

        return dot(m, DWf(r));

    };

}

/**
 * Return a function that will calculate the magnetic scalar potential \f$\mathbf{A}\f$ for a uniformly magnetised
 * tetrahedron using eq. (11) [1]. The input tetrahedron assumes the following winding for each triangular face:
 * - \f$r_1 \rightarrow r_2 \rightarrow r_3\f$,
 * - \f$r_1 \rightarrow r_3 \rightarrow r_4\f$,
 * - \f$r_1 \rightarrow r_4 \rightarrow r_2\f$,
 * - \f$r_2 \rightarrow r_4 \rightarrow r_3\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param M the (uniform) magnetisation of the tetrahedron.
 * @param r1 the first vertex of the tetrahedron.
 * @param r2 the second vertex of the tetrahedron.
 * @param r3 the third vertex of the tetrahedron.
 * @param r4 the fourth vertex of the tetrahedron.
 * @return a function that will calculate the scalar potential at any point in space due to the uniformly magnetised
 *         tetrahedron defined by the inputs.
 */
template<typename T>
std::function<T(const Vector3D<T> &)> new_uni_tet_phi_fun(const Vector3D<T> &M,
                                                          const Vector3D<T> &r1, const Vector3D<T> &r2,
                                                          const Vector3D<T> &r3, const Vector3D<T> &r4) {

    using std::array;
    using std::function;

    // Face normals.
    array<Vector3D<T>, 4> nf;
    nf[0] = triangle_normal(r1, r2, r3);
    nf[1] = triangle_normal(r1, r3, r4);
    nf[2] = triangle_normal(r1, r4, r2);
    nf[3] = triangle_normal(r2, r4, r3);

    // Wf functions.
    array<function<T(const Vector3D<T> &)>, 4> Wf;
    Wf[0] = new_Wf_tri_fun(r1, r2, r3);
    Wf[1] = new_Wf_tri_fun(r1, r3, r4);
    Wf[2] = new_Wf_tri_fun(r1, r4, r2);
    Wf[3] = new_Wf_tri_fun(r2, r4, r3);

    return [M, nf, Wf](const Vector3D<T> &r) {
        return dot(M, nf[0]) * Wf[0](r)
               + dot(M, nf[1]) * Wf[1](r)
               + dot(M, nf[2]) * Wf[2](r)
               + dot(M, nf[3]) * Wf[3](r);
    };

}

/**
 * Return a function that will calculate the magnetic vector potential \f$\mathbf{A}\f$ for a uniformly magnetised
 * tetrahedron using eq. (11) [1]. The input tetrahedron assumes the following winding for each triangular face:
 * - \f$r_1 \rightarrow r_2 \rightarrow r_3\f$,
 * - \f$r_1 \rightarrow r_3 \rightarrow r_4\f$,
 * - \f$r_1 \rightarrow r_4 \rightarrow r_2\f$,
 * - \f$r_2 \rightarrow r_4 \rightarrow r_3\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param M the (uniform) magnetisation of the tetrahedron.
 * @param r1 the first vertex of the tetrahedron.
 * @param r2 the second vertex of the tetrahedron.
 * @param r3 the third vertex of the tetrahedron.
 * @param r4 the fourth vertex of the tetrahedron.
 * @return a function that will calculate the vector potential at any point in space due to the uniformly magnetised
 *         tetrahedron defined by the inputs.
 */
template<typename T>
std::function<Vector3D<T>(const Vector3D<T> &)>
new_uni_tet_A_fun(const Vector3D<T> &M,
                  const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3, const Vector3D<T> &r4) {

    using std::array;
    using std::function;

    // Face normals.
    array<Vector3D<T>, 4> nf;
    nf[0] = triangle_normal(r1, r2, r3);
    nf[1] = triangle_normal(r1, r3, r4);
    nf[2] = triangle_normal(r1, r4, r2);
    nf[3] = triangle_normal(r2, r4, r3);

    // Wf functions.
    array<function<T(const Vector3D<T> &)>, 4> Wf;
    Wf[0] = new_Wf_tri_fun(r1, r2, r3);
    Wf[1] = new_Wf_tri_fun(r1, r3, r4);
    Wf[2] = new_Wf_tri_fun(r1, r4, r2);
    Wf[3] = new_Wf_tri_fun(r2, r4, r3);

    return [M, nf, Wf](const Vector3D<T> &r) {
        return cross(M, nf[0]) * Wf[0](r)
               + cross(M, nf[1]) * Wf[1](r)
               + cross(M, nf[2]) * Wf[2](r)
               + cross(M, nf[3]) * Wf[3](r);
    };

}

/**
 * Return a function that will calculate the magnetic induction \f$\mathbf{B}\f$ for a uniformly magnetised
 * tetrahedron using eq. (12) [1]. The input tetrahedron assumes the following winding for each triangular face:
 * - \f$r_1 \rightarrow r_2 \rightarrow r_3\f$,
 * - \f$r_1 \rightarrow r_3 \rightarrow r_4\f$,
 * - \f$r_1 \rightarrow r_4 \rightarrow r_2\f$,
 * - \f$r_2 \rightarrow r_4 \rightarrow r_3\f$.
 * @tparam T the underlying data type for the calculation - usually 'double' or 'mpreal'.
 * @param M the (uniform) magnetisation of the tetrahedron.
 * @param r1 the first vertex of the tetrahedron.
 * @param r2 the second vertex of the tetrahedron.
 * @param r3 the third vertex of the tetrahedron.
 * @param r4 the fourth vertex of the tetrahedron.
 * @return a function that will calculate the magnetic induction at any point in space due to the uniformly magnetised
 *         tetrahedron defined by the inputs.
 */
template<typename T>
std::function<Vector3D<T>(const Vector3D<T> &)>
new_uni_tet_B_fun(const Vector3D<T> &M,
                  const Vector3D<T> &r1, const Vector3D<T> &r2, const Vector3D<T> &r3, const Vector3D<T> &r4) {

    using std::array;
    using std::function;

    // Face normals.
    array<Vector3D<T>, 4> nf;
    nf[0] = triangle_normal(r1, r2, r3);
    nf[1] = triangle_normal(r1, r3, r4);
    nf[2] = triangle_normal(r1, r4, r2);
    nf[3] = triangle_normal(r2, r4, r3);

    // DWf functions.
    array<function<Vector3D<T>(const Vector3D<T> &)>, 4> DWf;
    DWf[0] = new_DWf_tri_fun(r1, r2, r3);
    DWf[1] = new_DWf_tri_fun(r1, r3, r4);
    DWf[2] = new_DWf_tri_fun(r1, r4, r2);
    DWf[3] = new_DWf_tri_fun(r2, r4, r3);

    return [M, nf, DWf](const Vector3D<T> &r) {
        return cross(cross(M, nf[0]), DWf[0](r))
               + cross(cross(M, nf[1]), DWf[1](r))
               + cross(cross(M, nf[2]), DWf[2](r))
               + cross(cross(M, nf[3]), DWf[3](r));
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
