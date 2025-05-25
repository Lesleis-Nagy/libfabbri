//
// Created by Lesleis Nagy on 02/12/2024.
//

#ifndef LIBFABBRI_INCLUDE_QUAD_HPP_
#define LIBFABBRI_INCLUDE_QUAD_HPP_

#include "geometry.hpp"

enum QuadType {
  FreeQuadType,
  FreeAxisAlignedQuadType,
  BoundQuadType,
  BoundAxisAlignedQuadType
};

template<typename T>
class Quad {

  public:

    static void set_eps(T eps) { _eps = eps; }
    static T eps() { return _eps; }

    explicit Quad(QuadType type) : _type{type} {}

    [[nodiscard]] virtual T signed_area() const = 0;
    [[nodiscard]] virtual T area() const = 0;
    [[nodiscard]] virtual T centroid() const = 0;
    [[nodiscard]] virtual bool contains(const Vector2D<T> &r) const = 0;

    [[nodiscard]] QuadType
      type() const {
        return _type;
      }

  private:

    QuadType _type;
    static T _eps;

};

template<typename T>
T Quad<T>::_eps = 1E-10;

/**
 * A class that encapsulates a free rectangle -- this is a rectangle that is
 * not formally part of a complex.
 */
template<typename T>
class FreeQuad : public Quad<T> {

  public:

    /**
     * Create a new FreeRectangle object 'origin' r0 and edge vectors e1 and e2,
     * where e1 and e2 are orthogonal (an exception is thrown if this is not the
     * case).
     */
    FreeQuad(Vector2D<T> r1, Vector2D<T> r2, Vector2D<T> r3, Vector2D<T> r4) :
      _r1{r1}, _r2{r2}, _r3{r3}, _r4{r4},
      Quad<T>(FreeQuadType) {
      }

    [[nodiscard]] virtual T
      signed_area() const {
        return (
            (
             _r1.x() * _r2.y()
             + _r2.x() * _r3.y()
             + _r3.x() * _r4.y()
             + _r4.x() * _r1.y()
            ) -
            (
             _r1.y() * _r2.x() +
             _r2.y() * _r3.x() +
             _r3.y() * _r4.x() +
             _r4.y() * _r1.x()
            )
            ) / T(2);
      }

    [[nodiscard]] virtual T
      area() const {
        return abs(signed_area());
      }

    [[nodiscard]] virtual Vector3D<T>
      centroid() const {
        return (_r1 + _r2 + _r3 + _r4) / T(4);
      }

    [[nodiscard]] virtual bool
      contains(const Vector2D<T> &r) const {

        T cp1 = cross(_r2 - _r1, r - _r1);
        T cp2 = cross(_r3 - _r2, r - _r2);
        T cp3 = cross(_r4 - _r3, r - _r3);
        T cp4 = cross(_r1 - _r4, r - _r4);

        return (cp1 > 0 && cp2 > 0 && cp3 > 0 && cp4 > 0) ||
          (cp1 < 0 && cp2 < 0 && cp3 < 0 && cp4 < 0);

      }

  private:

    Vector2D<T> _r1, _r2, _r3, _r4;

};

template<typename T>
class FreeAxisAlignedQuad : public Quad<T> {

  public:

    FreeAxisAlignedQuad(Vector2D<T> rmin, Vector2D<T> rmax) :
      _rmin{rmin}, _rmax{rmax}, Quad<T>(FreeAxisAlignedQuadType) {}

    [[nodiscard]] T
      signed_area() const {
        return (_rmax.x() - _rmin.x()) * (_rmax.y() - _rmin.y());
      }

    [[nodiscard]] virtual T
      area() const {
        return abs(signed_area());
      }

    [[nodiscard]]  virtual Vector3D<T>
      centroid() const {
        return (_rmin + _rmax) / T(2);
      }

    [[nodiscard]] virtual bool
      contains(const Vector2D<T> &r) const {
        return r.x() >= _rmin.x && r.x() <= _rmax.x &&
          r.y() >= _rmin.y && r.y() <= _rmax.y;
      }

  private:

    Vector2D<T> _rmin, _rmax;

};

#endif //LIBFABBRI_INCLUDE_QUAD_HPP_
