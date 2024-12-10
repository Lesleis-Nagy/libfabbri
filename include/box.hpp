//
// Created by Lesleis Nagy on 26/11/2024.
//

#ifndef LIBFABBRI_INCLUDE_BOX_HPP_
#define LIBFABBRI_INCLUDE_BOX_HPP_

#include "geometry.hpp"

enum BoxType {
  FreeBoxType,
  BoundBoxType
};

/**
 * A box is an axis-aligned cuboid.
 */
template<typename T>
class Box {
 public:

  explicit Box(BoxType type) : _type{type} {}

  [[nodiscard]] virtual T signed_volume() const = 0;
  [[nodiscard]] virtual T volume() const = 0;
  [[nodiscard]] virtual Vector3D<T> centroid() const = 0;
  [[nodiscard]] virtual bool contains(const Vector3D<T> &r) const = 0;
  [[nodiscard]] virtual const Vector3D<T> & rmin() = 0;
  [[nodiscard]] virtual const Vector3D<T> & rmax() = 0;

  [[nodiscard]] BoxType
  type() const {
    return _type;
  }

 private:

  BoxType _type;

};

/**
 * A class that encapsulates a free box -- this is a box that is
 * not formally part of a complex.
 */
template<typename T>
class FreeBox : public Box<T> {

 public:

  FreeBox(Vector3D<T> r_min, Vector3D<T> r_max) :
      _r_min{r_min}, _r_max{r_max},
      Box<T>(FreeBoxType) {}

  [[nodiscard]] virtual T
  signed_volume() const {
    return (_r_max.x() - _r_min.x())
        * (_r_max.y() - _r_min.y())
        * (_r_max.z() - _r_min.z());
  }

  [[nodiscard]] virtual T
  volume() const {
    return abs(signed_volume());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    return (_r_min + _r_max) / T(2);
  }

  [[nodiscard]] virtual bool
  contains(const Vector3D<T> &r) const {
    return (
        r.x() >= _r_min.x() && r.x() <= _r_max.x()
            && r.y() >= _r_min.y() && r.y() <= _r_max.y()
            && r.z() >= _r_min.z() && r.z() <= _r_max.z()
    );
  }

  [[nodiscard]] virtual const Vector3D<T> &
  rmin() {
    return _r_min;
  }

  [[nodiscard]] virtual const Vector3D<T> &
  rmax() {
    return _r_max;
  }

 private:

  Vector3D<T> _r_min, _r_max;

};

/**
 * Class that encapsulates a bound box -- this is a box that is
 * part of (bound to) a larger complex which gives it a unique index.
 */
template<typename T>
class BoundBox : public Box<T> {

 public:

  BoundBox(const VertexList3D<T> &vcl,
           const IndexTupleList<2> &til,
           size_t index) :
      _vcl{vcl}, _til{til}, _index{index},
      Box<T>(BoundBoxType) {}

  [[nodiscard]] virtual size_t
  index() const {
    return _index;
  }

  [[nodiscard]] virtual T
  signed_volume() const {
    auto [n_min, n_max] = _til[_index];
    auto r_min = _vcl[n_min], r_max = _vcl[n_max];

    return (r_max.x() - r_min.x())
        * (r_max.y() - r_min.y())
        * (r_max.z() - r_min.z());
  }

  [[nodiscard]] virtual T
  volume() const {
    return abs(signed_volume());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    auto [n_min, n_max] = _til[_index];
    auto r_min = _vcl[n_min], r_max = _vcl[n_max];

    return (r_min + r_max) / T(2);
  }

  [[nodiscard]] virtual bool
  contains(const Vector3D<T> &r) const {
    auto [n_min, n_max] = _til[_index];
    auto r_min = _vcl[n_min], r_max = _vcl[n_max];

    return (
        r.x() >= r_min.x() && r.x() <= r_max.x()
            && r.y() >= r_min.y() && r.y() <= r_max.y()
            && r.z() >= r_min.z() && r.z() <= r_max.z()
    );
  }

  [[nodiscard]] virtual const Vector3D<T> &
  rmin() {
    auto [n_min, n_max] = _til[_index];
    return _vcl[n_min];
  }

  [[nodiscard]] virtual const Vector3D<T> &
  rmax() {
    auto [n_min, n_max] = _til[_index];
    return _vcl[n_max];
  }

 private:

  const VertexList3D<T> &_vcl;
  const IndexTupleList<2> &_til;
  size_t _index;

};

#endif //LIBFABBRI_INCLUDE_BOX_HPP_
