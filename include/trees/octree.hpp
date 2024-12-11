/**
 * @file octree.hpp
 * @author L. Nagy
 * @brief Octree functions and classes.
 */

#ifndef LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
#define LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_

#include <vector>
#include <unordered_map>

#include "geometry.hpp"

enum OctreePosition {
  OCTREE_POSITION_BBR = 0,   // Octree, back bottom right
  OCTREE_POSITION_BBL = 1,   // Octree, back bottom left
  OCTREE_POSITION_BTR = 2,   // Octree, back top right
  OCTREE_POSITION_BTL = 3,   // Octree, back top left
  OCTREE_POSITION_FBR = 4,   // Octree, front bottom right
  OCTREE_POSITION_FBL = 5,   // Octree, front bottom left
  OCTREE_POSITION_FTR = 6,   // Octree, front top right
  OCTREE_POSITION_FTL = 7,   // Octree, front top left
};

/**
 * The octree node.
 */
template<typename T>
struct OctreeNode {

  OctreeNode(const VertexList3D<T> &vcl,
             const IndexTupleList<4> &til,
             Vector3D<T> r_min,
             Vector3D<T> r_max,
             int depth,
             int index,
             int parent) :
      _vcl(vcl),
      _til(til),
      _r_min(std::move(r_min)),
      _r_max(std::move(r_max)),
      _depth(depth),
      _index(index),
      _parent(parent) {}

  /**
   * If this node has no children, it is a leaf.
   * @return true if this is a leaf, otherwise false.
   */
  [[nodiscard]] bool
  is_leaf() const {
    return (_children[0] < 0)
        && (_children[1] < 0)
        && (_children[2] < 0)
        && (_children[3] < 0)
        && (_children[4] < 0)
        && (_children[5] < 0)
        && (_children[6] < 0)
        && (_children[7] < 0);
  }

  [[nodiscard]] OctreePosition
  which_child(int i) const {
    auto c = centroid(i);
    return which_child(c);
  }

  /**
   * Compute the index/position that a proposed vertex is in.
   * @param r the vertex to test for position.
   * @param the position.
   */
  [[nodiscard]] OctreePosition
  which_child(const Vector3D<T> &r) const {
    int left = is_left_child(r);
    int top = is_top_child(r);
    int front = is_front_child(r);

    return static_cast<OctreePosition>(left + top + front);
  }

  /**
   * Function to decide if a position vector r would be in the left child-box.
   * @param r the vertex to test for 'left-ness'.
   * @param return 1 if the position vector r would be in the left child-box,
   *               otherwise 0.
   */
  [[nodiscard]] int
  is_left_child(const Vector3D<T> &r) const {
    auto r_mid = (_r_min + _r_max) / T(2);
    if (r_mid.x() < r.x() <= _r_max.x()) {
      return 1;
    } else if (_r_min.x() <= r.x() <= r_mid.x()) {
      return 0;
    } else {
      throw std::runtime_error("Proposed position vector is not in the tree!");
    }
  }

  /**
   * Function to decide if a position vector r would be in the top child-box.
   * @param r the vertex to test for 'top-ness'.
   * @param return 2 if the position vector r would be in the top child-box,
   *               otherwise 0.
   */
  [[nodiscard]] int
  is_top_child(const Vector3D<T> &r) const {
    auto r_mid = (_r_min + _r_max) / T(2);
    if (r_mid.y() < r.y() <= _r_max.y()) {
      return 2;
    } else if (_r_min.y() <= r.y() <= r_mid.y()) {
      return 0;
    } else {
      throw std::runtime_error("Proposed position vector is not in the tree!");
    }
  }

  /**
   * Function to decide if a position vector r would be in the front child-box.
   * @param r the vertex to test for 'front-ness'.
   * @param return 4 if the position vector r would be in the front child-box,
   *               otherwise 0.
   */
  [[nodiscard]] int
  is_front_child(const Vector3D<T> &r) const {
    auto r_mid = (_r_min + _r_max) / T(2);
    if (r_mid.z() < r.z() <= _r_max.z()) {
      return 2;
    } else if (_r_min.z() <= r.z() <= r_mid.z()) {
      return 0;
    } else {
      throw std::runtime_error("Proposed position vector is not in the tree!");
    }
  }

  [[nodiscard]] std::pair<Vector3D<T>, Vector3D<T>>
  child_dimensions(OctreePosition p) {
    auto r_mid = (_r_min + _r_max) / T(2);
    switch (p) {
      case OCTREE_POSITION_BBR:
        return {
            {_r_min.x(), _r_min.y(), _r_min.z()},
            {r_mid.x(), r_mid.y(), r_mid.z()}
        };
      case OCTREE_POSITION_BBL:
        return {
            {r_mid.x(), _r_min.y(), _r_min.z()},
            {_r_max.x(), r_mid.y(), r_mid.z()}
        };
      case OCTREE_POSITION_BTR:
        return {
            {_r_min.x(), r_mid.y(), _r_min.z()},
            {r_mid.x(), _r_max.y(), r_mid.z()}
        };

    }
  }

  /**
   * Computes the centroid of a tetrahedron.
   * @param i the index of the tetrahedron.
   * @return the centroid of the tetrahedron with index i.
   */
  [[nodiscard]] Vector3D<T>
  centroid(int i) {
    auto [n0, n1, n2, n3] = _til[i];
    return (_vcl[n0] + _vcl[n1] + _vcl[n2] + _vcl[n3]) / T(4);
  }

  int _index;
  int _parent;

  int _depth;

  Vector3D<T> _r_min;
  Vector3D<T> _r_max;

  std::vector<int> _elements;

  const VertexList3D<T> &_vcl;
  const IndexTupleList<4> &_til;

  std::array<int, 8> _children{-1, -1, -1, -1, -1, -1, -1, -1};

};

template<typename T, int MAX_PER_NODE, int MAX_DEPTH>
class Octree {

 public:

  Octree(const VertexList3D<T> &vcl, const IndexTupleList<4> &til) :
      _vcl(vcl), _til(til) {
    T r_min_x = _vcl[0].x();
    T r_min_y = _vcl[0].y();
    T r_min_z = _vcl[0].z();
    T r_max_x = _vcl[0].x();
    T r_max_y = _vcl[0].y();
    T r_max_z = _vcl[0].z();

    Vector3D<T> r_max = _vcl[0];
    for (const auto &r : vcl) {
      if (r.x() < r_min_x) r_min_x = r.x();
      if (r.y() < r_min_y) r_min_y = r.y();
      if (r.z() < r_min_z) r_min_z = r.z();
      if (r_max_x < r.x()) r_max_x = r.x();
      if (r_max_y < r.y()) r_max_y = r.y();
      if (r_max_z < r.z()) r_max_z = r.z();
    }

    _nodes.push_back(
        OctreeNode(vcl, til,
                   {r_min_x, r_min_y, r_min_z},
                   {r_max_x, r_max_y, r_max_z},
                   0, 0, -1)
    );

  }

 private:

  std::vector<OctreeNode<T>> _nodes;

  const VertexList3D<T> &_vcl;
  const IndexTupleList<4> &_til;

  void
  populate() {

    struct StackFrame {
      int tet_index;
      int node_index;
    };

    std::queue<StackFrame> stack;

    for (int i = 0; i < _vcl.size(); ++i) {
      // Push the ith tetrahedron on to the stack along with the node that
      // we wish to push it to (the start node).
      stack.push({i, 0});

      while (!stack.empty()) {

        // Pop the stack.
        StackFrame frame = stack.pop();

        // Retrieve the node.
        auto &node = _nodes[frame.node_index];

        // Test if the node is a leaf.
        if (node.is_leaf()) {
          // This node is a leaf, so add the tetrahedron index of the current
          // frame to the node's list of elements.
          node.elements.push_back(frame.tet_index);
        }

        // Test if the current node is full and can be split.
        if (node.elements.size() > MAX_PER_NODE && node.depth <= MAX_DEPTH) {
          // There are too many nodes and we can split.
          for (int j = 0; j < node.elements.size(); ++j) {
            // For every element index in the current node find child node
            // to which it belongs.
            auto child = node.which_child(j);
            if (node.children[i] < 0) {
              _nodes.push_back(OctreeNode(_vcl, _til,))
            }
          }

        }

      }

    }

  }

  /**
   * Computes the centroid of a tetrahedron.
   * @param i the index of the tetrahedron.
   * @return the centroid of the tetrahedron with index i.
   */
  [[nodiscard]] Vector3D<T>
  centroid(int i) {
    auto [n0, n1, n2, n3] = _til[i];
    return (_vcl[n0] + _vcl[n1] + _vcl[n2] + _vcl[n3]) / T(4);
  }

};

#endif //LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
