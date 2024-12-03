//
// Created by Lesleis Nagy on 02/12/2024.
//

#ifndef LIBFABBRI_INCLUDE_RECTANGLE_HPP_
#define LIBFABBRI_INCLUDE_RECTANGLE_HPP_

#include "geometry.hpp"

enum RectangleType {
  FreeRectangleType,
  BoundRectangleType
};

template <typename T>
class Rectangle {

 public:

  explicit Rectangle(RectangleType type) : _type{type} {}

  [[nodiscard]] virtual T signed_area() const = 0;
  [[nodiscard]] virtual T area() const = 0;
  [[nodiscard]] virtual T centroid() const = 0;
  [[nodiscard]] virtual bool coplanar(const T &r) const = 0;
  [[nodiscard]] virtual bool contains(const T &r) const = 0;

  [[nodiscard]] RectangleType
  type() const {
    return _type;
  }

 private:

  RectangleType _type;

};

/**
 * A class that encapsulates a free rectangle -- this is a rectangle that is
 * not formally part of a complex.
 */
template<typename T>
class FreeRectangle : public Rectangle<T> {

 public:

  FreeRectangle(T r_min, T r_max) :
      _r_min{r_min}, _r_max{r_max},
      Rectangle<T>(FreeRectangleType) {}

  [[nodiscard]] virtual T
  signed_area() const {
    return mfold(_r_max - _r_min);
  }

  [[nodiscard]] virtual T
  area() const {
    return abs(signed_area());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    return (_r_min + _r_max) / T(2);
  }

  [[nodiscard]] virtual bool
  coplanar(const T &r) const {
    if (r.dim() == 2) return true;

  }

  [[nodiscard]] virtual bool
  contains(const T &r) const {
    return (
        r.x() >= _r_min.x() && r.x() <= _r_max.x()
            && r.y() >= _r_min.y() && r.y() <= _r_max.y()
            && r.z() >= _r_min.z() && r.z() <= _r_max.z()
    );
  }

 private:

  T _r_min, _r_max;

};


#endif //LIBFABBRI_INCLUDE_RECTANGLE_HPP_
