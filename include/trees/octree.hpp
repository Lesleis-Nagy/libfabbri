#ifndef LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
#define LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_

#include <fstream>
#include <stack>
#include <vector>

#include "geometry.hpp"

/**
 * The sum-code.
 */
enum OctreeSumCode {
  /// Octree sum-code for back, bottom, left sub-cuboid.
  OCTREE_POSITION_BBL = 0,
  /// Octree sum-code for back, bottom, right sub-cuboid.
  OCTREE_POSITION_BBR = 1,
  /// Octree sum-code for back, top, left sub-cuboid.
  OCTREE_POSITION_BTL = 2,
  /// Octree sum-code for back, top, right sub-cuboid.
  OCTREE_POSITION_BTR = 3,
  /// Octree sum-code for front, bottom, left sub-cuboid.
  OCTREE_POSITION_FBL = 4,
  /// Octree sum-code for front, bottom, right sub-cuboid.
  OCTREE_POSITION_FBR = 5,
  /// Octree sum-code for front, top, left sub-cuboid.
  OCTREE_POSITION_FTL = 6,
  /// Octree sum-code for front, top, right sub-cuboid.
  OCTREE_POSITION_FTR = 7,
};

/**
 * A function to convert a sum-code to a text representation.
 */
inline std::string
sum_code_str(const OctreeSumCode sum_code) {
  switch (sum_code) {
    case OCTREE_POSITION_BBL:
      return "BBL";
    case OCTREE_POSITION_BBR:
      return "BBR";
    case OCTREE_POSITION_BTL:
      return "BTL";
    case OCTREE_POSITION_BTR:
      return "BTR";
    case OCTREE_POSITION_FBL:
      return "FBL";
    case OCTREE_POSITION_FBR:
      return "FBR";
    case OCTREE_POSITION_FTL:
      return "FTL";
    case OCTREE_POSITION_FTR:
      return "FTR";
    default:
      throw std::runtime_error("Invalid sum-code!");
  }
}

/**
 * A simple function to convert a list of values to a printable table.
 */
template<typename T>
std::string
format_array_as_table(const std::vector<T> &values, int columns) {
  std::vector<std::string> lines;
  std::stringstream ss_current_line;
  bool first_in_line = true;
  int counter = 0;

  for (const auto &value : values) {
    if (counter == columns) {
      ss_current_line << ", " << "<FONT COLOR=\"BLUE\">" << value << "</FONT>";
      lines.push_back(ss_current_line.str());
      ss_current_line.str("");
      ss_current_line.clear();
      first_in_line = true;
      counter = 0;
    } else {
      if (first_in_line) {
        ss_current_line << "<FONT COLOR=\"BLUE\">" << value << "</FONT>";
        first_in_line = false;
      } else {
        ss_current_line << ", " << "<FONT COLOR=\"BLUE\">" << value <<
            "</FONT>";
      }
      counter++;
    }
  }

  if (counter > 0) {
    lines.push_back(ss_current_line.str());
  }

  std::stringstream ss_table;
  for (auto const &line : lines) {
    ss_table << line << "<BR/>";
  }

  return ss_table.str();
}

/**
 * An octree node helper class.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 */
template<typename T>
class OctreeNode {
  public:
    /**
     * The basic constructor creates an empty Octree node.
     * @param vcl the vertex coordinate list.
     * @param til the tetrahedra index list.
     */
    OctreeNode(const VertexList3D<T> &vcl,
               const IndexTupleList<4> &til)
      : _index(-1),
        _parent(-1),
        _depth(-1),
        _r_min({0.0, 0.0, 0.0}),
        _r_max({0.0, 0.0, 0.0}),
        _vcl(vcl),
        _til(til) {
    }

    /**
     * OctreeNode constructor will create a new octree node object in the tree.
     * Each node holds a reference to the tetrahedral complex represented by
     * a list of vertices (of tetrahedra) called vcl and a list of 4-tuple indices
     * in to the list of vertices.
     *
     * @param vcl the vertex coordinate list.
     * @param til the tetrahedra index list.
     * @param r_min the minimum coordinate of the axis aligned box that this node
     *              represents.
     * @param r_max the maximum coordinate of the axis aligned box that this node
     *              represents.
     * @param depth the depth of this node in the tree.
     * @param index the index of this node in the tree.
     * @param parent the index of the parent of this node.
     */
    OctreeNode(const VertexList3D<T> &vcl,
               const IndexTupleList<4> &til,
               Vector3D<T> r_min,
               Vector3D<T> r_max,
               const int depth,
               const int index,
               const int parent)
      : _index(index),
        _parent(parent),
        _depth(depth),
        _r_min(std::move(r_min)),
        _r_max(std::move(r_max)),
        _vcl(vcl),
        _til(til) {
    }

    /**
     * A function to check if this node is a leaf - a leaf is defined as a node
     * that has no children.
     * @return true if this node is a leaf, otherwise false.
     */
    [[nodiscard]] bool
    is_leaf() const {
      return _children[0] < 0
          && _children[1] < 0
          && _children[2] < 0
          && _children[3] < 0
          && _children[4] < 0
          && _children[5] < 0
          && _children[6] < 0
          && _children[7] < 0;
    }

    /**
     * Function to decide if a position vector r would be in the right child node
     * of this node.
     * @param r the vertex to test for 'right-ness'.
     * @return 1 if the position vector r would be in the right child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_right_child(const Vector3D<T> &r) const {
      auto r_mid = (_r_min + _r_max) / T(2);
      if ((_r_min.x() <= r.x()) && (r.x() < r_mid.x())) {
        // Left
        return 0;
      } else if ((r_mid.x() <= r.x()) && (r.x() <= _r_max.x())) {
        // Right
        return 1;
      } else {
        throw std::runtime_error(
          "Proposed position vector is not in the tree!");
      }
    }

    /**
     * Function to decide if a position vector r would be in the top child node.
     * @param r the vertex to test for 'top-ness'.
     * @return 2 if the position vector r would be in the top child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_top_child(const Vector3D<T> &r) const {
      auto r_mid = (_r_min + _r_max) / T(2);

      if ((_r_min.y() <= r.y()) && (r.y() < r_mid.y())) {
        // Bottom
        return 0;
      } else if ((r_mid.y() <= r.y()) && (r.y() <= _r_max.y())) {
        // Top
        return 2;
      } else {
        throw std::runtime_error(
          "Proposed position vector is not in the tree!");
      }
    }

    /**
     * Function to decide if a position vector r would be in the front child node.
     * @param r the vertex to test for 'front-ness'.
     * @return 4 if the position vector r would be in the front child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_front_child(const Vector3D<T> &r) const {
      auto r_mid = (_r_min + _r_max) / T(2);

      if ((_r_min.z() <= r.z()) && (r.z() < r_mid.z())) {
        // Bottom
        return 0;
      } else if ((r_mid.z() <= r.z()) && (r.z() <= _r_max.z())) {
        // Top
        return 4;
      } else {
        throw std::runtime_error(
          "Proposed position vector is not in the tree!");
      }
    }

    /**
     * Compute the sum-code index of the child that a proposed vertex is in.
     * @param r the position vector of a vertex.
     * @return the octree sum-code that the input position vector is in.
     */
    [[nodiscard]] OctreeSumCode
    which_child(const Vector3D<T> &r) const {
      int left = is_right_child(r);
      int top = is_top_child(r);
      int front = is_front_child(r);

      return static_cast<OctreeSumCode>(left + top + front);
    }

    /**
     * Compute the sum-code index of the child that a proposed vertex is in.
     * of this node.
     * @param i the index of the vertex.
     * @return the osctree sum-code of the i-th vertex.
     */
    [[nodiscard]] OctreeSumCode
    which_child(size_t i) const {
      auto r_c = centroid(i);
      return which_child(r_c);
    }

    /**
     * Function to return the corner vertices of one of the child nodes of this
     * node.
     * @param p the sum code of the child node (of this node) for which we'd like
     *        the dimensions.
     */
    [[nodiscard]] std::pair<Vector3D<T>, Vector3D<T> >
    child_corners(OctreeSumCode p) {
      auto r_mid = (_r_min + _r_max) / T(2);
      switch (p) {
        case OCTREE_POSITION_BBR:
          return {
            {r_mid.x(), _r_min.y(), _r_min.z()},
            {_r_max.x(), r_mid.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BBL:
          return {
            {_r_min.x(), _r_min.y(), _r_min.z()},
            {r_mid.x(), r_mid.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BTR:
          return {
            {r_mid.x(), r_mid.y(), _r_min.z()},
            {_r_max.x(), _r_max.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BTL:
          return {
            {_r_min.x(), r_mid.y(), _r_min.z()},
            {r_mid.x(), _r_max.y(), r_mid.z()}
          };
        case OCTREE_POSITION_FBR:
          return {
            {r_mid.x(), _r_min.y(), r_mid.z()},
            {_r_max.x(), r_mid.y(), _r_max.z()}
          };
        case OCTREE_POSITION_FBL:
          return {
            {_r_min.x(), _r_min.y(), r_mid.z()},
            {r_mid.x(), r_mid.y(), _r_max.z()}
          };
        case OCTREE_POSITION_FTR:
          return {
            {r_mid.x(), r_mid.y(), r_mid.z()},
            {_r_max.x(), _r_max.y(), _r_max.z()}
          };
        case OCTREE_POSITION_FTL:
          return {
            {_r_min.x(), r_mid.y(), r_mid.z()},
            {r_mid.x(), _r_max.y(), _r_max.z()}
          };
        default:
          throw std::runtime_error("Invalid sum-code!");
      }
    }

    /**
     * Computes the centroid of a tetrahedron.
     * @param i the index of the tetrahedron.
     * @return the centroid of the tetrahedron with index i.
     */
    [[nodiscard]] Vector3D<T>
    centroid(int i) const {
      auto [n0, n1, n2, n3] = _til[i];
      return (_vcl[n0] + _vcl[n1] + _vcl[n2] + _vcl[n3]) / T(4);
    }

    /**
     * Add a tetrahedron index to the list of tetrahedron indices belonging to
     * this tree node.
     * @param tet_index the tetrahedron index to add.
     */
    void
    add_tet_index(int tet_index) {
      _tet_indices.push_back(tet_index);
    }

    /**
     * Retrieve the tetrahedron indices belonging to this tree node.
     * @return the list of tetrahedron indices belonging to this tree node.
     */
    [[nodiscard]] const std::vector<int> &
    tet_indices() const {
      return _tet_indices;
    }

    /**
     * Retrieve the number of tetrahedron indices belonging to this tree node.
     * @return the number of tetrahedron indices belonging to this tree node.
     */
    [[nodiscard]] size_t
    n_tet_indices() const {
      return _tet_indices.size();
    }

    /**
     * Retrieve the index of the octree node.
     * @return the index of the octree node.
     */
    [[nodiscard]] int
    index() const {
      return _index;
    }

    /**
     * Sets the index of the octree node.
     * @param index the octree node's index.
     */
    void
    set_index(int index) {
      _index = index;
    }

    /**
     * Return the parent of the octree node (-1 represents the root).
     * @return the index of the octree node.
     */
    [[nodiscard]] int
    parent() const {
      return _parent;
    }

    /**
     * Sets the parent index of this octree node.
     * @param parent the new parent index
     */
    void
    set_parent(int parent) {
      _parent = parent;
    }

    /**
     * return the depth of the octree node.
     * @return the depth of the octree node.
     */
    [[nodiscard]] int
    depth() const {
      return _depth;
    }

    /**
     * Set the depth of this octree node.
     * @param depth the new depth.
     */
    void
    set_depth(int depth) {
      _depth = depth;
    }

    [[nodiscard]] int
    child(OctreeSumCode sum_code) const {
      return _children[sum_code];
    }

    /**
     * Set the r_min extent of the octree node.
     * @param r_min the new rmin extent value.
     */
    void
    set_r_min(Vector3D<T> r_min) {
      _r_min = r_min;
    }

    /**
     * Set the r_max extent of the octree node.
     * @param r_max the new rmax extent value.
     */
    void
    set_r_max(Vector3D<T> r_max) {
      _r_max = r_max;
    }

    /**
     * Set the child node index at the `sum-code` position.
     * @param sum_code the sum-code position to set the new child index.
     * @param index the new value of the child index.
     */
    void
    set_child(OctreeSumCode sum_code, int index) {
      _children[sum_code] = index;
    }

    /**
     * Retrieve the children of this node.
     */
    [[nodiscard]] const std::array<int, 8> &
    children() const {
      return _children;
    }

    /**
     * Retrieve the r_min value.
     * @return r_min the smallest extent of the box.
     */
    [[nodiscard]] const Vector3D<T> &
    r_min() const {
      return _r_min;
    }

    /**
     * Retrieve the r_max value.
     * @return r_max the smallest extent of the box.
     */
    [[nodiscard]] const Vector3D<T> &
    r_max() const {
      return _r_max;
    }

  private:
    int _index;
    int _parent;
    int _depth;

    Vector3D<T> _r_min;
    Vector3D<T> _r_max;

    std::vector<int> _tet_indices;

    const VertexList3D<T> &_vcl;
    const IndexTupleList<4> &_til;

    std::array<int, 8> _children{-1, -1, -1, -1, -1, -1, -1, -1};
};

template<typename T, int MAX_PER_NODE, int MAX_DEPTH>
class Octree {
  public:
    Octree(const VertexList3D<T> &vcl,
           const IndexTupleList<4> &til) : _vcl(vcl), _til(til) {
      T r_min_x = _vcl[0].x();
      T r_min_y = _vcl[0].y();
      T r_min_z = _vcl[0].z();
      T r_max_x = _vcl[0].x();
      T r_max_y = _vcl[0].y();
      T r_max_z = _vcl[0].z();

      // Compute the extents of the first octree node.
      Vector3D<T> r_max = _vcl[0];
      for (const auto &r : _vcl) {
        if (r.x() < r_min_x) r_min_x = r.x();
        if (r.y() < r_min_y) r_min_y = r.y();
        if (r.z() < r_min_z) r_min_z = r.z();
        if (r_max_x < r.x()) r_max_x = r.x();
        if (r_max_y < r.y()) r_max_y = r.y();
        if (r_max_z < r.z()) r_max_z = r.z();
      }

      // Create the first octree node.
      _nodes.emplace_back(
        _vcl,
        _til,
        Vector3D{r_min_x, r_min_y, r_min_z},
        Vector3D{r_max_x, r_max_y, r_max_z},
        0,
        0,
        -1);

      populate();
    }

    /**
     * Function to compute the centroid of the tid-th tetrahedron.
     * @param tid the tetrahedron id of for which we wish to compute the sum.
     * @return the vector position of the centroid.
     */
    [[nodiscard]] Vector3D<T>
    centroid(size_t tid) const {
      auto [n0, n1, n2, n3] = _til[tid];
      return (_vcl[n0] + _vcl[n1] + _vcl[n2] + _vcl[n3]) / T(4);
    }

    [[nodiscard]] int
    find_leaf_index_containing_tet_index(int tet_id) {
      std::stack<int> stack;
      stack.push(0);

      while (!stack.empty()) {
        auto node_index = stack.top();
        stack.pop();

        const auto &node = _nodes[node_index];

        if (node.is_leaf()) {
          bool contains = false;
          for (auto tet_id2 : node.tet_indices()) {
            if (tet_id2 == tet_id) {
              return node.index();
            }
          }
        } else {
          for (auto node_id : node.children()) {
            if (!_nodes[node_id].tet_indices().empty()) {
              stack.push(node_id);
            }
          }
        }
      }
      return -1;
    }

    [[nodiscard]] std::optional<std::reference_wrapper<const OctreeNode<T>> >
    find_leaf_containing_tet_index(int tet_id) {
      int leaf_index = find_leaf_index_containing_tet_index(tet_id);
      if (leaf_index == -1) {
        return std::nullopt;
      } else {
        return _nodes[leaf_index];
      }
    }

    /**
     * Function to create a dot representation of the tree.
     * @param file_name the output file to write the dot representation to.
     */
    void
    write_dot(const std::string &file_name) const {
      // Open the file.
      std::ofstream fout_dot(file_name);
      if (!fout_dot.is_open()) {
        std::cerr << "Error:";
        std::cerr << " could not open file: '" << file_name << "'" << std::endl;
        return;
      }

      // Define the nodes/edges that will be written.
      std::vector<std::string> nodes;
      std::vector<std::string> edges;

      // Push the root octree node on to a stack.
      std::stack<int> stack;
      stack.push(0);

      // Keep going until the stack is empty.
      while (!stack.empty()) {
        auto node_index = stack.top();
        stack.pop();

        const auto &node = _nodes[node_index];

        std::stringstream ss_node;
        ss_node << "    ";
        ss_node << node.index();

        ss_node << " [label=<";
        ss_node << "<FONT COLOR=\"RED\">" << node.index() << "</FONT>";
        ss_node << " ";
        ss_node << "(" << node.parent() << ")";
        ss_node << " ";
        ss_node << "{" << node.depth() << "}";
        ss_node << "<BR/>";
        ss_node << "min:";
        ss_node << node.r_min().x() << ", ";
        ss_node << node.r_min().y() << ", ";
        ss_node << node.r_min().z();
        ss_node << "<BR/>";
        ss_node << "max:";
        ss_node << node.r_max().x() << ", ";
        ss_node << node.r_max().y() << ", ";
        ss_node << node.r_max().z();
        ss_node << "<BR/>";
        ss_node << format_array_as_table(node.tet_indices(), 5);
        ss_node << ">]";

        nodes.push_back(ss_node.str());

        // Process the nodes of the octree.
        std::stringstream ss_edge;
        if (node.parent() >= 0) {
          ss_edge << "    " << node.parent() << " -> " << node.index();
        }
        edges.push_back(ss_edge.str());

        // Process the children of this node.
        for (auto child_node_index : node.children()) {
          if (child_node_index >= 0) {
            stack.push(child_node_index);
          }
        }
      }

      // Write the directed graph
      fout_dot << "digraph G{" << std::endl;
      fout_dot << "    " <<
          "graph [splines=ortho, rankdir=LR, nodesep=0.5, overlap=false];" <<
          std::endl;
      fout_dot << "    " << "node [shape=box];" << std::endl;

      // Write nodes
      for (const auto &str_node : nodes) {
        fout_dot << str_node << std::endl;
      }

      // Write directed edges
      for (const auto &str_edge : edges) {
        fout_dot << str_edge << std::endl;
      }

      // Close the graph
      fout_dot << "}" << std::endl;

      // Close the file
      fout_dot.close();
    }

    /**
     * Retrieve all the nodes in the tree.
     * @param the octree nodes.
     */
    [[nodiscard]] const std::vector<OctreeNode<T> > &
    nodes() {
      return _nodes;
    }

    /**
     * Retrieve a reference to a particular node in the tree.
     * @param node_index the index of the node.
     * @param an octree node.
     */
    [[nodiscard]] const OctreeNode<T> &
    node(int node_index) {
      return _nodes[node_index];
    }

  private:
    std::vector<OctreeNode<T> > _nodes;

    const VertexList3D<T> &_vcl;
    const IndexTupleList<4> &_til;

    /**
     * Splits a node in to eight child nodes - this function will create eight
     * new child nodes, `node`s children then refer to the indices of the eight
     * nodes, these indices are returned.
     * @param node_index the index of the node to be split.
     * @return the indices of the new nodes (in sum-code position).
     */
    std::array<int, 8>
    split(int node_index) {
      // The output of the function is a list of indices of octree nodes, the
      // position of each octree node index is the sum-code.
      std::array<int, 8> octree_node_indices = {-1, -1, -1, -1, -1, -1, -1, -1};

      if (_nodes[node_index].is_leaf()) {
        // If the node is a leaf, we split it in to its eight children.
        for (int sum_code = 0; sum_code < 8; ++sum_code) {
          // For each of the sum-codes, find the extent of the child associated
          // with the current sum-code
          Vector3D<T> rmin, rmax;
          std::tie(rmin, rmax) =
              _nodes[node_index].child_corners(
                static_cast<OctreeSumCode>(sum_code)
              );

          // Create a new empty child node on our list of nodes.
          _nodes.emplace_back(_vcl, _til);

          // Create a reference to the new node.
          auto &child_node = _nodes.back();

          // Compute the index of the new child node.
          int new_node_index = _nodes.size() - 1;

          // Set the empty values of the new child node.
          child_node.set_r_min(rmin);
          child_node.set_r_max(rmax);
          child_node.set_depth(_nodes[node_index].depth() + 1);
          child_node.set_index(new_node_index);
          child_node.set_parent(_nodes[node_index].index());

          // Update the index of the child node in the node.
          _nodes[node_index].set_child(OctreeSumCode(sum_code), new_node_index);

          octree_node_indices[sum_code] = new_node_index;
        }
      }

      // Return the indices of the new octree nodes.
      return octree_node_indices;
    }

    /**
     * This function runs through all the elements in `_til` and builds the
     * octree using the element centroids.
     */
    void
    populate() {
      // Stack frame to hold stack information.
      struct StackFrame {
        int tet_index; // Tetrahedron index.
        int octree_node_index; // Index of a tree node.
      };

      // The stack.
      std::stack<StackFrame> stack;

      for (int tid = 0; tid < _til.size(); ++tid) {
        // Iterate through every tetrahedron index (tid); pushing the tid on to
        // the stack at octree node index zero - the root of the tree.
        stack.push({tid, 0});

        while (!stack.empty()) {
          // Keep looping until the stack contains no more entries, first popping
          // the stack to grap the top stack frame object.
          auto frame = std::move(stack.top());
          stack.pop();

          // Retrieve the current frame's octree node id
          auto oni = frame.octree_node_index;

          if (_nodes[oni].is_leaf()) {
            // The node is a leaf, so we add the current tetrahedron index to its
            // list of tetrahedron indices.
            _nodes[oni].add_tet_index(frame.tet_index);

            if (_nodes[oni].n_tet_indices() >= MAX_PER_NODE) {
              // Split the current node in to eight.
              auto child_octree_ids = split(_nodes[oni].index());

              for (auto tet_index : _nodes[oni].tet_indices()) {
                // Find the sum-code of the child nodes of each tetrahedron index.
                auto child_sum_code = _nodes[oni].which_child(tet_index);

                // Push the current tetrahedron index along with the id of its
                // octree node index (to which it belongs) on to the stack.
                stack.push({tet_index, child_octree_ids[child_sum_code]});
              }
            }
          } else {
            // The node is not a leaf, so after adding the current tetrahedron
            // index to the current octree node's list we pass it on to the
            // child with which its associated.

            // Add the tetrahedron id to the current octree node's tetrahedron
            // index list.
            _nodes[oni].add_tet_index(frame.tet_index);

            // Find the sum-code of the child to which we should pass on the
            // tetrahedron index.
            auto child_sum_code = _nodes[oni].which_child(frame.tet_index);

            // Push the current tetrahedron index, along with the id of the
            // octree node index to which it belongs on to the stack.
            stack.push({frame.tet_index, _nodes[oni].child(child_sum_code)});
          }
        }
      }
    }
};

#endif //LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
