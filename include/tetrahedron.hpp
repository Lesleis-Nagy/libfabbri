//
// Created by Lesleis Nagy on 26/11/2024.
//

#ifndef LIBFABBRI_INCLUDE_TETRAHEDRON_HPP_
#define LIBFABBRI_INCLUDE_TETRAHEDRON_HPP_

#include "geometry.hpp"

enum TetrahedronType {
  FreeTetrahedronType,
  BoundTetrahedronType
};

template<typename T>
class Tetrahedron {
 public:

  explicit Tetrahedron(TetrahedronType type) : _type{type} {}

  [[nodiscard]] virtual T det() const = 0;
  [[nodiscard]] virtual T signed_volume() const = 0;
  [[nodiscard]] virtual T volume() const = 0;
  [[nodiscard]] virtual Vector3D<T> centroid() const = 0;
  [[nodiscard]] virtual bool contains(const Vector3D<T> &r) const = 0;

  [[nodiscard]] TetrahedronType
  type() const {
    return _type;
  }

 private:

  TetrahedronType _type;

};

/**
 * A class that encapsulates a free tetrahedron, which is a tetrahedron that is
 * not formally part of a complex.
 */
template<typename T>
class FreeTetrahedron : public Tetrahedron<T> {

 public:

  FreeTetrahedron(Vector3D<T> r0,
                  Vector3D<T> r1,
                  Vector3D<T> r2,
                  Vector3D<T> r3) :
      _r0{r0}, _r1{r1}, _r2{r2}, _r3{r3},
      Tetrahedron<T>(FreeTetrahedronType) {}

  [[nodiscard]] virtual T
  det() const {
    return ::det(
        Matrix4x4<T>{
            {_r0.x(), _r0.y(), _r0.z(), 1.0},
            {_r1.x(), _r1.y(), _r1.z(), 1.0},
            {_r2.x(), _r2.y(), _r2.z(), 1.0},
            {_r3.x(), _r3.y(), _r3.z(), 1.0}
        }
    );
  }

  [[nodiscard]] virtual T
  signed_volume() const {
    return (1.0 / 6.0) * det();
  }

  [[nodiscard]] virtual T
  volume() const {
    return abs(signed_volume());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    return (_r0 + _r1 + _r2 + _r3) / T(4);
  }

  [[nodiscard]] virtual bool
  contains(const Vector3D<T> &r) const {

    double v_total = volume();
    FreeTetrahedron<T> t1{r, _r1, _r2, _r3};
    FreeTetrahedron<T> t2{_r0, r, _r2, _r3};
    FreeTetrahedron<T> t3{_r0, _r1, r, _r3};
    FreeTetrahedron<T> t4{_r0, _r1, _r2, r};

    double v1 = t1.volume();
    double v2 = t2.volume();
    double v3 = t3.volume();
    double v4 = t4.volume();

    return std::abs(v_total - (v1 + v2 + v3 + v4)) < 1e-10;

  };


 private:

  Vector3D<T> _r0, _r1, _r2, _r3;

};

/**
 * Class that encapsulates a bound tetrahedron, this is a tetrahedron that is
 * part of (bound to) a larger complex which gives it a unique index.
 */
template<typename T>
class BoundTetrahedron : public Tetrahedron<T> {

 public:

  BoundTetrahedron(const VertexList<T> &vcl,
                   const IndexTupleList<4> &til,
                   size_t index) :
      _vcl{vcl}, _til{til}, _index{index},
      Tetrahedron<T>(BoundTetrahedronType) {}

  [[nodiscard]] virtual size_t
  index() const {
    return _index;
  }

  [[nodiscard]] virtual T
  det() const {
    auto [n0, n1, n2, n3] = _til[_index];
    auto r0 = _vcl[n0], r1 = _vcl[n1], r2 = _vcl[n2], r3 = _vcl[n3];
    return ::det(
        Matrix4x4<T>{
            {r0.x(), r0.y(), r0.z(), 1.0},
            {r1.x(), r1.y(), r1.z(), 1.0},
            {r2.x(), r2.y(), r2.z(), 1.0},
            {r3.x(), r3.y(), r3.z(), 1.0}
        }
    );
  }

  [[nodiscard]] virtual T
  signed_volume() const {
    return (1.0 / 6.0) * det();
  }

  [[nodiscard]] virtual T
  volume() const {
    return abs(signed_volume());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    auto [n0, n1, n2, n3] = _til[_index];
    auto r0 = _vcl[n0], r1 = _vcl[n1], r2 = _vcl[n2], r3 = _vcl[n3];
    return (r0 + r1 + r2 + r3) / T(4);
  }

  [[nodiscard]] virtual bool
  contains(const Vector3D<T> &r) const {
    auto [n0, n1, n2, n3] = _til[_index];
    auto r0 = _vcl[n0], r1 = _vcl[n1], r2 = _vcl[n2], r3 = _vcl[n3];

    double v_total = volume();
    FreeTetrahedron<T> t1{r, r1, r2, r3};
    FreeTetrahedron<T> t2{r0, r, r2, r3};
    FreeTetrahedron<T> t3{r0, r1, r, r3};
    FreeTetrahedron<T> t4{r0, r1, r2, r};

    double v1 = t1.volume();
    double v2 = t2.volume();
    double v3 = t3.volume();
    double v4 = t4.volume();

    return std::abs(v_total - (v1 + v2 + v3 + v4)) < 1e-10;

  };

 private:

  const VertexList<T> &_vcl;
  const IndexTupleList<4> &_til;
  size_t _index;

};

#endif //LIBFABBRI_INCLUDE_TETRAHEDRON_HPP_
