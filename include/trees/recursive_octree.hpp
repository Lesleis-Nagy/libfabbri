//
// Created by Lesleis Nagy on 22/11/2024.
//

#ifndef LIBFABBRI_INCLUDE_SPACE_RECURSIVE_OCTTREE_HPP_
#define LIBFABBRI_INCLUDE_SPACE_RECURSIVE_OCTTREE_HPP_

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

#include "geometry.hpp"
#include "box.hpp"

template <typename T>
class RecursiveOctree {
 public:

  RecursiveOctree(const Box<T> &boundary,
                  size_t maxObjects,
                  size_t maxDepth)
      : _boundary(boundary),
        _max_objects(maxObjects),
        _max_depth(maxDepth),
        _is_leaf(true) {}

  bool
  insert(const Vector3D<T> &point) {
    if (!_boundary.contains(point.x(), point.y(), point.z())) {
      return false;
    }

    if (_is_leaf) {
      _objects.push_back(point);
      if (_objects.size() > _max_objects && _current_depth < _max_depth) {
        subdivide();
        redistributeObjects();
      }
      return true;
    }

    for (auto &child : _children) {
      if (child->insert(point)) {
        return true;
      }
    }

    return false;
  }

  [[nodiscard]] std::vector<Vector3D<T>>
  query(const Box<T> &region) const {
    std::vector<Vector3D<T>> result;

    if (!_boundary.overlaps(region)) {
      return result;
    }

    for (const auto &obj : _objects) {
      if (region.contains(obj.x(), obj.y(), obj.z())) {
        result.push_back(obj);
      }
    }

    if (!_is_leaf) {
      for (const auto &child : _children) {
        auto childResult = child->query(region);
        result.insert(result.end(), childResult.begin(), childResult.end());
      }
    }

    return result;

  }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const RecursiveOctree<U>& tree);

 private:

  Box<T> _boundary;
  size_t _max_objects;
  size_t _max_depth;
  size_t _current_depth = 0;
  bool _is_leaf;

  std::vector<Vector3D<T>> _objects;
  std::array<std::unique_ptr<RecursiveOctree>, 8> _children;

  void subdivide() {
    _is_leaf = false;

    T xmid = (_boundary.xmin() + _boundary.xmax()) / 2;
    T ymid = (_boundary.ymin() + _boundary.ymax()) / 2;
    T zmid = (_boundary.zmin() + _boundary.zmax()) / 2;

    _children[0] = std::make_unique<RecursiveOctree>(
        Box<T>{
            {_boundary.xmin(),_boundary.ymin(),_boundary.zmin()},
            {xmid, ymid, zmid}
        },
        _max_objects,
        _max_depth
    );

    _children[1] = std::make_unique<RecursiveOctree>(
        Box<T>{
            {xmid, _boundary.ymin(), _boundary.zmin()},
            {_boundary.xmax(), ymid, zmid}
            },
        _max_objects,
        _max_depth
    );

    _children[2] = std::make_unique<RecursiveOctree>(
        Box<T>{
            _boundary.xmin(),
            xmid,
            ymid,
            _boundary.ymax(),
            _boundary.zmin(),
            zmid
        },
        _max_objects,
        _max_depth
    );

    _children[3] = std::make_unique<RecursiveOctree>(
        Box<T>{
            xmid,
            _boundary.xmax(),
            ymid,
            _boundary.ymax(),
            _boundary.zmin(),
            zmid
        },
        _max_objects,
        _max_depth
    );

    _children[4] = std::make_unique<RecursiveOctree>(
        Box<T>{
            _boundary.xmin(),
            xmid,
            _boundary.ymin(),
            ymid,
            zmid,
            _boundary.zmax()
        },
        _max_objects,
        _max_depth
    );

    _children[5] = std::make_unique<RecursiveOctree>(
        Box<T>{
            xmid,
            _boundary.xmax(),
            _boundary.ymin(),
            ymid,
            zmid,
            _boundary.zmax()
            },
        _max_objects,
        _max_depth
    );

    _children[6] = std::make_unique<RecursiveOctree>(
        Box<T>{
            _boundary.xmin(),
            xmid,
            ymid,
            _boundary.ymax(),
            zmid,
            _boundary.zmax()
        },
        _max_objects,
        _max_depth
    );

    _children[7] = std::make_unique<RecursiveOctree>(
        Box<T>{
            xmid,
            _boundary.xmax(),
            ymid,
            _boundary.ymax(),
            zmid,
            _boundary.zmax()
        },
        _max_objects,
        _max_depth
    );
  }

  void
  redistributeObjects() {

    auto oldObjects = std::move(_objects);
    for (const auto &point : oldObjects) {
      for (auto &child : _children) {
        if (child->insert(point)) {
          break;
        }
      }
    }

  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const RecursiveOctree<T>& tree) {
  static size_t node_id_counter = 0;

  std::ostringstream dot;
  dot << "digraph Octree {\n";
  //dot << "graph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"];";
  //dot << "splines=\"ortho\";\n";
  //dot << "node [shape=record];\n";
  //dot << "beautify=true;\n";
  dot << "fixedsize=true;\n";
  dot << "K=1.0;\n";
  dot << "overlap_scaling=100.0;\n";

  // Helper function to recursively traverse the tree
  std::function<void(const RecursiveOctree<T>&, size_t)> write_node;
  write_node = [&](const RecursiveOctree<T>& node, size_t node_id) {
    // Start the node label
    dot << "  node" << node_id << " [";
    dot << "shape=box ";
    dot << "width=6 ";
    dot << "height=3 ";
    dot << "fixedsize=true ";
    dot << "label=\"";

    // Include basic node information
    dot << "Objects: " << node._objects.size() << "\\n";
    dot << "Bounds: ["
        << node._boundary.xmin() << ", " << node._boundary.xmax() << "] x ["
        << node._boundary.ymin() << ", " << node._boundary.ymax() << "] x ["
        << node._boundary.zmin() << ", " << node._boundary.zmax() << "]";

    // Include point coordinates if the node has points
    if (!node._objects.empty()) {
      dot << "\\nPoints:\\n";
      for (const auto& point : node._objects) {
        dot << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")\\n";
      }
    }

    // Close the node label
    dot << "\"];\n";

    // Recursively process child nodes
    if (!node._is_leaf) {
      for (size_t i = 0; i < node._children.size(); ++i) {
        if (node._children[i]) {
          size_t child_id = ++node_id_counter;
          dot << "  node" << node_id << " -> node" << child_id << ";\n";
          write_node(*node._children[i], child_id);
        }
      }
    }
  };

  // Start from the root node
  write_node(tree, node_id_counter);

  dot << "}\n";
  os << dot.str();

  return os;
}

#endif //LIBFABBRI_INCLUDE_SPACE_RECURSIVE_OCTTREE_HPP_
