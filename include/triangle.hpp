//
// Created by Lesleis Nagy on 06/12/2024.
//

#ifndef LIBFABBRI_INCLUDE_TRIANGLE_HPP_
#define LIBFABBRI_INCLUDE_TRIANGLE_HPP_

#include "geometry.hpp"

enum TriangleType {
  FreeTriangleType,
  BoundTriangleType
};

template<typename T>
class Triangle {

 public:

  static void set_eps(T eps) { _eps = eps; }
  static T eps() { return _eps; }

  explicit Triangle(TriangleType type) : _type{type} {}

  [[nodiscard]] virtual T det() const = 0;
  [[nodiscard]] virtual T signed_area() const = 0;
  [[nodiscard]] virtual T area() const = 0;
  [[nodiscard]] virtual T centroid() const = 0;
  [[nodiscard]] virtual bool contains(const Vector2D<T> &r) const = 0;

  [[nodiscard]] TriangleType
  type() const {
    return _type;
  }

 private:

  TriangleType _type;
  static T _eps;

};

template<typename T>
T Triangle<T>::_eps = 1E-10;

template<typename T>
class FreeTriangle : public Triangle<T> {

 public:

  FreeTriangle(Vector2D<T> r0, Vector2D<T> r1, Vector2D<T> r2) :
      _r0{r0}, _r1{r1}, _r2{r2},
      Triangle<T>(FreeTriangleType) {}

  [[nodiscard]] virtual T
  det() const {
    return ::det(
        Matrix3x3<T>{
            {_r0.x(), _r0.y(), 1.0},
            {_r1.x(), _r1.y(), 1.0},
            {_r2.x(), _r2.y(), 1.0}
        }
    );
  }

  [[nodiscard]] virtual T
  signed_area() const {
    return det() / T(2);
  }

  [[nodiscard]] virtual T
  area() const {
    return abs(signed_area());
  }

  [[nodiscard]] virtual Vector2D<T>
  centroid() const {
    return (_r0 + _r1 + _r2) / T(3);
  }

  [[nodiscard]] virtual bool
  contains(const Vector2D<T> &r) const {

    using namespace std;

    FreeTriangle t0(r, _r1, _r2);
    FreeTriangle t1(_r0, r, _r2);
    FreeTriangle t2(_r0, _r1, r);

    T a0 = t0.area();
    T a1 = t1.area();
    T a2 = t2.area();

    return abs((a0 + a1 + a2) - area()) < Triangle<T>::eps();

  }

 private:

  Vector2D<T> _r0, _r1, _r2;

};

template<typename T>
class BoundTriangle : public Triangle<T> {

 public:

  BoundTriangle(const VertexList2D<T> &vcl,
                const IndexTupleList<3> &til,
                size_t index) :
      _vcl{vcl}, _til{til}, _index{index}, Triangle<T>(BoundTriangleType) {}

  [[nodiscard]] virtual T
  det() const {
    auto [n0, n1, n2] = _til[_index];
    const auto &r0 = _vcl[n0], &r1 = _vcl[n1], &r2 = _vcl[n2];

    return ::det(
        Matrix3x3<T>{
            {r0.x(), r0.y(), 1.0},
            {r1.x(), r1.y(), 1.0},
            {r2.x(), r2.y(), 1.0}
        }
    );
  }

  [[nodiscard]] virtual T
  signed_area() const {
    return det() / T(2);
  }

  [[nodiscard]] virtual T
  area() const {
    return abs(signed_area());
  }

  [[nodiscard]] virtual Vector2D<T>
  centroid() const {
    auto [n0, n1, n2] = _til[_index];
    const auto &r0 = _vcl[n0], &r1 = _vcl[n1], &r2 = _vcl[n2];

    return (r0 + r1 + r2) / T(3);
  }

  [[nodiscard]] virtual bool
  contains(const Vector2D<T> &r) const {

    using namespace std;

    auto [n0, n1, n2] = _til[_index];
    const auto &r0 = _vcl[n0], &r1 = _vcl[n1], &r2 = _vcl[n2];

    FreeTriangle t0(r, r1, r2);
    FreeTriangle t1(r0, r, r2);
    FreeTriangle t2(r0, r1, r);

    T a0 = t0.area();
    T a1 = t1.area();
    T a2 = t2.area();

    return abs((a0 + a1 + a2) - area()) < Triangle<T>::eps();

  }

 private:

  const VertexList2D<T> &_vcl;
  const IndexTupleList<3> &_til;
  size_t _index;

};

#endif //LIBFABBRI_INCLUDE_TRIANGLE_HPP_
