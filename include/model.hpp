//
// Created by Lesleis Nagy on 15/06/2024.
//

#ifndef LIBFABBRI_INCLUDE_MODEL_HPP_
#define LIBFABBRI_INCLUDE_MODEL_HPP_

#include <utility>

#include "aliases.hpp"
#include "field.hpp"
#include "mesh.hpp"


/**
 * A model consists of a mesh and a field.
 */
template <size_t DIM>
class Model {

 public:

  explicit Model(Mesh<DIM> mesh) :
      _mesh{std::move(mesh)} {}

  Model(Mesh<DIM> mesh,
        FieldList field_list) :
      _mesh{std::move(mesh)},
      _field_list{std::move(field_list)} {}

  [[nodiscard]] const Mesh<DIM> &
  mesh() const { return _mesh; }

  [[nodiscard]] const FieldList &
  field_list() const { return _field_list; }

  void add_list(Field field) { _field_list.add_field(std::move(field)); }

 private:

  Mesh<DIM> _mesh;

  FieldList _field_list;

};

#endif //LIBFABBRI_INCLUDE_MODEL_HPP_
