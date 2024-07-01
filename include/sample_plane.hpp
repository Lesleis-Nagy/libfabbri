//
// Created by Lesleis Nagy on 28/06/2024.
//

#ifndef LIBFABBRI_INCLUDE_SAMPLE_PLANE_HPP_
#define LIBFABBRI_INCLUDE_SAMPLE_PLANE_HPP_

#include "geometry3d.hpp"

template <typename T>
class SamplePlane {

 public:

  SamplePlane(Vector3D<T> centre, T theta, T width, T height, T spacing):
  _target{0, 0, 0},
  _centre{centre},
  _theta{theta},
  _width{width},
  _height{height},
  _spacing{spacing} {

    Vector3D<T> e1{1, 0, 0};
    Vector3D<T> e2{0, 1, 0};
    Vector3D<T> e3{0, 0, 1};

    auto d = normalised(_target - _centre);

    auto axis = normalised(cross(e3, d));
    auto angle = acos(dot(e3, d));
    auto axis_angle_matrix = rotation3x3(axis, angle);
    auto orientation_matrix = rotation3x3(d, _theta);

    auto transform = orientation_matrix * axis_angle_matrix;

    _e1 = transform * e1;
    _e2 = transform * e2;
    _e3 = transform * e3;

    auto nx = ceil(width / spacing);
    auto ny = ceil(height / spacing);

    _nx = (size_t)nx;
    _ny = (size_t)ny;

    _anchor = _centre - (_width / 2.0) * _e1 - (_height / 2.0) * _e2;

    _data.resize(_nx * _ny);

    for (size_t i = 0; i < _ny; ++i) {

      for(size_t j = 0; j < _nx; ++j) {

        size_t index = _nx * i + j;

        _data[index] = _anchor + _spacing * j * _e1 + _spacing * i * _e2;

      }

    }

  }

  Vector3D<T> operator()(size_t i, size_t j) {

    size_t index = _nx * i + j;

    return _data[index];

  }

  [[nodiscard]] size_t nx() const { return _nx; }

  [[nodiscard]] size_t ny() const { return _ny; }

 private:

  Vector3D<T> _target;
  Vector3D<T> _centre;
  T _theta;
  T _width;
  T _height;
  T _spacing;

  Vector3D<T> _e1;
  Vector3D<T> _e2;
  Vector3D<T> _e3;

  Vector3D<T> _anchor;

  size_t _nx;
  size_t _ny;

  std::vector<Vector3D<T>> _data;

};

#endif //LIBFABBRI_INCLUDE_SAMPLE_PLANE_HPP_
