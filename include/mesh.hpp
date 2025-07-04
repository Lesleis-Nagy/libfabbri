//
// Created by Lesleis Nagy on 05/04/2024.
//

#ifndef LIBFABBRI_READMESH_HPP
#define LIBFABBRI_READMESH_HPP

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "vector3d.hpp"
#include "aliases.hpp"
#include "mesh_utilities.hpp"
#include "sample_plane.hpp"

//###########################################################################//
//# An DIM-dimensional mesh.                                                #//
//###########################################################################//

/**
 * An DIM-dimesional mesh forward declaration.
 * @tparam DIM the dimensionality of the mesh.
 */
template <Dimension DIM>
class Mesh;

/**
 * An object that holds information about a three-dimensional mesh.
 */
template <>
class Mesh<DIM2> {

 public:

  /**
   * Constructor will create a new mesh.
   * @param vcl the (v)ertex (c)oordinate (l)ist.
   * @param cil the (c)onnectivity (i)ndex (l)ist.
   * @param sml the (s)ub-(m)esh (i)ndex (l)ist.
   */
  Mesh(v_list vcl, tri_list cil, smi_list sml) :
      _vcl(std::move(vcl)),
      _cil(std::move(cil)),
      _sml(std::move(sml)) {

  }

  /**
   * Create a new mesh from a sample_plane.
   */
  Mesh(const SamplePlane<double> &sample_plane) {

    _vcl = sample_plane.vcl();
    _cil = sample_plane.cil();
    _sml = sample_plane.sml();

  }

  /**
   * Retrieve the vertex coordinate list.
   * @return the vertex coordinate list.
   */
  [[nodiscard]] const v_list &
  vcl() const {

    return _vcl;

  }

  /**
   * Retrieve the connectivity index list.
   * @return the connectivity index list.
   */
  [[nodiscard]] const tri_list &
  cil() const {

    return _cil;

  }

  /**
   * Retrieve the sub-mesh index list.
   * @return the sub-mesh index list.
   */
  [[nodiscard]] const smi_list &
  sml() const {

    return _sml;

  }

 private:

  // Vertex list.
  v_list _vcl;

  // Connectivity index list.
  tri_list _cil;

  // Sub-mesh (index) list.
  smi_list _sml;

};

/**
 * An object that holds information about a three-dimensional mesh.
 */
template <>
class Mesh<DIM3> {

 public:

  /**
   * Constructor will create a new three-dimensional mesh.
   * @param vcl the (v)ertex (c)oordinate (l)ist.
   * @param cil the (c)onnectivity (i)ndex (l)ist.
   * @param sml the (s)ub-(m)esh list.
   */
  Mesh(v_list vcl, tet_list cil, smi_list sml) :
      _vcl(std::move(vcl)),
      _cil(std::move(cil)),
      _sml(std::move(sml)) {

    // Initialize internal data structures.
    init_stri2tet_stri2tri_stri2smi();
    init_sedge2tet();
    init_tet2tet_tri();
    init_v2v_edge();

  }

  /**
   * Retrieve the vertex coordinate list.
   * @return the vertex coordinate list.
   */
  [[nodiscard]] const v_list &
  vcl() const {

    return _vcl;

  }

  /**
   * Retrieve the connectivity index list.
   * @return the connectivity index list.
   */
  [[nodiscard]] const tet_list &
  cil() const {

    return _cil;

  }

  /**
   * Retrieve the sub-mesh index list.
   * @return the sub-mesh index list.
   */
  [[nodiscard]] const smi_list &
  sml() const {

    return _sml;

  }

  /**
   * Return the mapping from sorted triangle faces to tetrahedra.
   * @return mapping from sorted triangle faces to tetrahedra.
   */
  [[nodiscard]] const stri_to_tets_map &
  stri2tets() const {

    return _stri2tets;

  }

  /**
   * Return the mapping from sorted edge to tetrahedra.
   * @return mapping from sorted edge to tetrahedra.
   */
  [[nodiscard]] const sedge_to_tets_map &
  sedge2tets() const {

    return _sedge2tets;

  }

  /**
   * Return the mapping from sorted triangle face to triangle face - which is
   * in its original order.
   * @return mapping from sorted triangle face to triangle face.
   */
  [[nodiscard]] const stri_to_tri_map &
  stri2tri() const {

    return _stri2tri;

  }

  /**
   * Return the mapping from a tetrahedron to each of its face-neighbour
   * tetrahedra.
   * @return the mapping from tetrahedron to tetrahedra.
   */
  [[nodiscard]] const tet_to_tets_map &
  tet2tets_tri() const {

    return _tet2tets_tri;

  }

  /**
   * Return the mapping from a vertex to each of its edge-neighbour vertices.
   * @return the mapping from vertex to vertices.
   */
  [[nodiscard]] const v_to_vs_list &
  v2vs_edge() const {

    return _v2vs_edge;

  }

  /**
   * Extract the surface of the mesh as a new mesh object.
   *
   */
  [[nodiscard]] Mesh<DIM2>
  extract_surface_mesh() const {

    // Take a deep copy of mesh information.
    tri_list cil;
    smi_list sml;

    // Populate the connectivity list (cil) and sub-mesh list (sml).
    for (const auto &kv : _stri2tets) {

      auto stri = kv.first;
      auto tets = kv.second;

      // If the triangle face belongs to only one element ...
      if (tets.size() == 1) {
        // ... then it is a boundary face, so get the unsorted triangle-face
        // (i.e. the triangle with its original winding) associated with the
        // sorted triangle-face; and ...
        const auto &face = _stri2tri.find(stri)->second;

        // ... push the unsorted-triangle indices to the connectivity index list
        // of the 2D surface mesh that we're building.
        cil.push_back(face);
      }

      // If a triangle face belongs to only one element ...
      if (tets.size() == 1) {
        // ... then it is a boundary face, so get the sub-mesh index associated
        // with this face; and ...
        const auto &sub_mesh_id = _stri2smi.find(stri)->second;

        // ... push that index to the sub-mesh indices of the 2D surface mesh
        // that we're building.
        sml.push_back(sub_mesh_id);
      }

    }

    v_list vcl(_vcl);

    return {vcl, cil, sml};

  }

 private:

  // Vertex list.
  v_list _vcl;

  // Tetrahedra (index) list.
  tet_list _cil;

  // Sub-mesh (index) list.
  smi_list _sml;

  // Mapping of (s)orted (tri)angle to (tet)rahedra.
  stri_to_tets_map _stri2tets;

  // Mapping of (s)orted (tri)angles to (tri)angles (where the unsorted triangle
  // indices: 0, 1, 2 are in counter-clockwise winding order).
  stri_to_tri_map _stri2tri;

  // Mapping of (s)orted (tri)angles to (s)ub-(m)esh (i)ndices.
  stri_to_smi_map _stri2smi;

  // Mapping of (s)orted (edge) to (tet)rahedra.
  sedge_to_tets_map _sedge2tets;

  // Mapping of (tet)rahedra indices (in cil) to (tet)rahedra indices by
  // triangular face.
  tet_to_tets_map _tet2tets_tri;

  // Mapping of (v)ertex index to (v)ertex indices by edge.
  v_to_vs_list _v2vs_edge;

  /**
   * Initialize the sorted triangle to tetrahedron index mapping.
   */
  void init_stri2tet_stri2tri_stri2smi() {

    for (size_t i = 0; i < _cil.size(); ++i) {

      auto fs = faces(_cil[i]);
      auto sub_id = _sml[i];

      size_t tri_idx = 0;
      for (auto &f : fs) {

        // For the first or third triangle index, we fix the winding.
        if ((tri_idx == 1) || (tri_idx == 3)) {
          size_t tmp_idx = f[0];
          f[0] = f[1];
          f[1] = tmp_idx;
        }

        tri_idx++;

        auto sf = sort(f);

        // Add a mapping from the sorted triangle face to the original triangle.
        // Recall that we do this because sorted triangle indices are optimal
        // for testing the equality of two triangles but sorting triangle
        // indices destroys their winding.
        _stri2tri[sf] = f;

        // If the sorted (triangle) face is *NOT* in _stri2tet ...
        if (_stri2tets.find(sf) == _stri2tets.end()) {
          // ... then create a new mapping from the sorted face to the
          //     tetrahedron's index.
          _stri2tets[sf] = {i};
        } else {
          // ... otherwise append a new tetrahedron index to
          //     the mapping from sorted (triangle) faces to
          //     tetrahedra.
          _stri2tets[sf].push_back(i);
        }

        // Add the sub-mesh index to the sorted triangle face index. NOTE:
        // for internal triangles that span two sub-meshes, this quantity is
        // undefined (since we don't know which sub-mesh index) was written
        // first, however for boundary-face triangles the sub-mesh index will
        // be well-defined.
        _stri2smi[sf] = _sml[i];

      }

    }

  }

  /**
   * Initialize the sorted edge to tetrahedron index mapping.
   */
  void init_sedge2tet() {

    for (size_t i = 0; i < _cil.size(); ++i) {

      auto es = edges(_cil[i]);

      for (auto &e : es) {

        auto se = sort(e);
        if (_sedge2tets.find(se) == _sedge2tets.end()) {
          _sedge2tets[se] = {i};
        } else {
          _sedge2tets[se].push_back(i);
        }

      }

    }

  }

  /**
   * Initialize the tetrahedron to tetrahedron (by triangle face) mapping.
   */
  void init_tet2tet_tri() {

    for (const auto &kv : _stri2tets) {

      auto stri = kv.first;
      auto tets = kv.second;

      // If the triangle face belongs to two elements.
      if (tets.size() == 2) {
        size_t v0 = tets[0];
        size_t v1 = tets[1];

        // Associate the first tetrahedron index with the second.
        if (_tet2tets_tri.find(v0) == _tet2tets_tri.end()) {
          _tet2tets_tri[v0] = {v1};
        } else {
          _tet2tets_tri[v0].push_back(v1);
        }

        // Associate the second tetrahedron index with the first.
        if (_tet2tets_tri.find(v1) == _tet2tets_tri.end()) {
          _tet2tets_tri[v1] = {v0};
        } else {
          _tet2tets_tri[v1].push_back(v0);
        }

      }

    }

  }

  /**
   * Initialize the vertex to vertex (by edge) mapping.
   */
  void init_v2v_edge() {

    for (const auto &kv : _sedge2tets) {

      auto &sedge = kv.first;

      if (_v2vs_edge.find(sedge[0]) == _v2vs_edge.end()) {
        _v2vs_edge[sedge[0]] = {sedge[1]};
      } else {
        _v2vs_edge[sedge[0]].push_back(sedge[1]);
      }

      if (_v2vs_edge.find(sedge[1]) == _v2vs_edge.end()) {
        _v2vs_edge[sedge[1]] = {sedge[0]};
      } else {
        _v2vs_edge[sedge[1]].push_back(sedge[0]);
      }

    }

    for (auto &kv : _v2vs_edge) {
      auto &vs = kv.second;
      sort(vs.begin(), vs.end());
    }

  }

};

#endif //LIBFABBRI_READMESH_HPP
