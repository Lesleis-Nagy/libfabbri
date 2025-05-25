//
// Created by Lesleis Nagy on 26/11/2024.
//

#ifndef LIBFABBRI_INCLUDE_BOX_HPP_
#define LIBFABBRI_INCLUDE_BOX_HPP_

#include "geometry.hpp"

namespace amiga {
/**
 * An enumeration indicating the type of box.
 */
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
    virtual ~Box() = default;

    explicit Box(const BoxType type) : type_{type} {
    }

    [[nodiscard]] virtual T signed_volume() const = 0;
    [[nodiscard]] virtual T volume() const = 0;
    [[nodiscard]] virtual Vector3D<T> centroid() const = 0;
    [[nodiscard]] virtual bool contains(const Vector3D<T>& r) const = 0;
    [[nodiscard]] virtual const Vector3D<T>& rmin() const = 0;
    [[nodiscard]] virtual const Vector3D<T>& rmax() const = 0;

    [[nodiscard]] BoxType
    type() const {
      return type_;
    }

  private:
    BoxType type_;
};

/**
 * A class that encapsulates a free box -- this is a box that is
 * not formally part of a complex.
 */
template<typename T>
class FreeBox final : public Box<T> {
  public:
    FreeBox(Vector3D<T> r_min, Vector3D<T> r_max) : Box<T>(FreeBoxType), r_min_{r_min},
                                                    r_max_{r_max} {
    }

    [[nodiscard]] T
    signed_volume() const override {
      return (r_max_.x() - r_min_.x())
          * (r_max_.y() - r_min_.y())
          * (r_max_.z() - r_min_.z());
    }

    [[nodiscard]] T
    volume() const override {
      return abs(signed_volume());
    }

    [[nodiscard]] Vector3D<T>
    centroid() const override {
      return (r_min_ + r_max_) / T(2);
    }

    [[nodiscard]] bool
    contains(const Vector3D<T>& r) const override {
      return r.x() >= r_min_.x() && r.x() <= r_max_.x()
          && r.y() >= r_min_.y() && r.y() <= r_max_.y()
          && r.z() >= r_min_.z() && r.z() <= r_max_.z();
    }

    [[nodiscard]] const Vector3D<T>&
    rmin() const override {
      return r_min_;
    }

    [[nodiscard]] const Vector3D<T>&
    rmax() const override {
      return r_max_;
    }

  private:
    Vector3D<T> r_min_, r_max_;
};

/**
 * Class that encapsulates a bound box -- this is a box that is
 * part of (bound to) a larger complex which gives it a unique index.
 */
template<typename T>
class BoundBox final : public Box<T> {
  public:
    BoundBox(const VertexList3D<T>& vcl,
             const IndexTupleList<2>& til,
             const size_t index) : Box<T>(BoundBoxType), vcl_{vcl}, til_{til}, _index{index} {
    }

    [[nodiscard]] size_t
    index() const {
      return _index;
    }

    [[nodiscard]] T
    signed_volume() const override {
      auto [n_min, n_max] = til_[_index];
      auto r_min = vcl_[n_min], r_max = vcl_[n_max];

      return (r_max.x() - r_min.x())
          * (r_max.y() - r_min.y())
          * (r_max.z() - r_min.z());
    }

    [[nodiscard]] T
    volume() const override {
      return abs(signed_volume());
    }

    [[nodiscard]] Vector3D<T>
    centroid() const override {
      auto [n_min, n_max] = til_[_index];
      auto r_min = vcl_[n_min], r_max = vcl_[n_max];

      return (r_min + r_max) / T(2);
    }

    [[nodiscard]] bool
    contains(const Vector3D<T>& r) const override {
      auto [n_min, n_max] = til_[_index];
      auto r_min = vcl_[n_min], r_max = vcl_[n_max];

      return r.x() >= r_min.x() && r.x() <= r_max.x()
          && r.y() >= r_min.y() && r.y() <= r_max.y()
          && r.z() >= r_min.z() && r.z() <= r_max.z();
    }

    [[nodiscard]] const Vector3D<T>&
    rmin() const override {
      auto [n_min, n_max] = til_[_index];
      return vcl_[n_min];
    }

    [[nodiscard]] const Vector3D<T>&
    rmax() const override {
      auto [n_min, n_max] = til_[_index];
      return vcl_[n_max];
    }

  private:
    const VertexList3D<T>& vcl_;
    const IndexTupleList<2>& til_;
    size_t _index;
};
} // namespace amiga
#endif //LIBFABBRI_INCLUDE_BOX_HPP_
