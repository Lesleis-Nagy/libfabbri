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

template<typename T>
class Rectangle {

 public:

  class EdgeVectorOrthogonalityException : public std::exception {

   public:

    explicit EdgeVectorOrthogonalityException(const std::string &message) {}

    const char *what() const noexcept override {
      return "The input vectors were not orthogonal.";
    }

  };

  static void set_eps(T eps) { _eps = eps; }
  static T eps() { return _eps; }

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
  static T _eps;

};

template <typename T>
T Rectangle<T>::_eps = 1E-10;

/**
 * A class that encapsulates a free rectangle -- this is a rectangle that is
 * not formally part of a complex.
 */
template<typename T>
class FreeRectangle : public Rectangle<T> {

 public:

  /**
   * Create a new FreeRectangle object 'origin' r0 and edge vectors e1 and e2,
   * where e1 and e2 are orthogonal (an exception is thrown if this is not the
   * case).
   */
  FreeRectangle(T r0, T e1, T e2) :
      _r0{r0}, _e1{e1}, _e2{e2},
      Rectangle<T>(FreeRectangleType) {

    if (Rectangle<T>::eps() < dot(e1, e2)) {
      throw Rectangle<T>::EdgeVectorOrthogonalityException();
    }

  }

  [[nodiscard]] virtual T
  signed_area() const {
    return mfold(_e1 - _e2);
  }

  [[nodiscard]] virtual T
  area() const {
    return abs(signed_area());
  }

  [[nodiscard]] virtual Vector3D<T>
  centroid() const {
    return (_e1 + _e2) / T(2);
  }

  [[nodiscard]] virtual bool
  coplanar(const T &r) const {
    if (r.dim() == 2) return true;

    return det(row_matrix(_e1, _e2, r)) < Rectangle<T>::eps();

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

  T _r0, _e1, _e2;

};

#endif //LIBFABBRI_INCLUDE_RECTANGLE_HPP_
