#ifndef LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
#define LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_

#include <fstream>
#include <stack>
#include <vector>

#include "amiga/geometry.hpp"
#include "amiga/tetrahedron.hpp"

namespace amiga {
/**
 * The sum-code.
 */
enum OctreeSumCode {
  /// Octree sum-code for back, bottom, left subcuboid.
  OCTREE_POSITION_BBL = 0,
  /// Octree sum-code for back, bottom, right subcuboid.
  OCTREE_POSITION_BBR = 1,
  /// Octree sum-code for back, top, left subcuboid.
  OCTREE_POSITION_BTL = 2,
  /// Octree sum-code for back, top, right subcuboid.
  OCTREE_POSITION_BTR = 3,
  /// Octree sum-code for front, bottom, left subcuboid.
  OCTREE_POSITION_FBL = 4,
  /// Octree sum-code for front, bottom, right subcuboid.
  OCTREE_POSITION_FBR = 5,
  /// Octree sum-code for front, top, left subcuboid.
  OCTREE_POSITION_FTL = 6,
  /// Octree sum-code for front, top, right subcuboid.
  OCTREE_POSITION_FTR = 7,
};

/**
 * A function to convert a sum-code to a text representation.
 */
inline std::string
sum_code_str(const OctreeSumCode sum_code) {
  switch (sum_code) {
    case OCTREE_POSITION_BBL: return "BBL";
    case OCTREE_POSITION_BBR: return "BBR";
    case OCTREE_POSITION_BTL: return "BTL";
    case OCTREE_POSITION_BTR: return "BTR";
    case OCTREE_POSITION_FBL: return "FBL";
    case OCTREE_POSITION_FBR: return "FBR";
    case OCTREE_POSITION_FTL: return "FTL";
    case OCTREE_POSITION_FTR: return "FTR";
    default: throw std::runtime_error("Invalid sum-code!");
  }
}

/**
 * A simple function to convert a list of values to a printable table.
 */
template<typename T>
std::string
format_array_as_table(const std::vector<T>& values, int columns) {
  std::vector<std::string> lines;
  std::stringstream ss_current_line;
  bool first_in_line = true;
  int counter = 0;

  for (const auto& value : values) {
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
  for (auto const& line : lines) {
    ss_table << line << "<BR/>";
  }

  return ss_table.str();
}

template<typename T, int MAX_PER_NODE, int MAX_DEPTH>
class Octree;

/**
 * An octree node helper class.
 * @tparam T the underlying data type for the calculation - usually 'double' or
 *           'mpreal'.
 */
template<typename T>
class OctreeNode {
  template<typename, int, int>
  friend class Octree;

  public:
    /**
     * The basic constructor creates an empty Octree node.
     * @param vcl the vertex coordinate list.
     * @param til the tetrahedra index list.
     */
    OctreeNode(const VertexList3D<T>& vcl,
               const IndexTupleList<4>& til)
      : index_(-1),
        parent_(-1),
        depth_(-1),
        r_min_({0.0, 0.0, 0.0}),
        r_max_({0.0, 0.0, 0.0}),
        vcl_(vcl),
        til_(til) {
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
    OctreeNode(const VertexList3D<T>& vcl,
               const IndexTupleList<4>& til,
               Vector3D<T> r_min,
               Vector3D<T> r_max,
               const int depth,
               const int index,
               const int parent)
      : index_(index),
        parent_(parent),
        depth_(depth),
        r_min_(std::move(r_min)),
        r_max_(std::move(r_max)),
        vcl_(vcl),
        til_(til) {
    }

    /**
     * A function to check if this node is a leaf - a leaf is defined as a node
     * that has no children.
     * @return true if this node is a leaf, otherwise false.
     */
    [[nodiscard]] bool
    is_leaf() const {
      return children_[0] < 0
          && children_[1] < 0
          && children_[2] < 0
          && children_[3] < 0
          && children_[4] < 0
          && children_[5] < 0
          && children_[6] < 0
          && children_[7] < 0;
    }

    /**
     * Function to decide if a position vector r would be in the right child node
     * of this node.
     * @param r the vertex to test for 'right-ness'.
     * @return 1 if the position vector r would be in the right child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_right_child(const Vector3D<T>& r) const {
      auto r_mid = (r_min_ + r_max_) / T(2);
      if ((r_min_.x() <= r.x()) && (r.x() < r_mid.x())) {
        // Left
        return 0;
      }
      if ((r_mid.x() <= r.x()) && (r.x() <= r_max_.x())) {
        // Right
        return 1;
      }
      throw std::runtime_error(
        "Proposed position vector is not in the tree!");
    }

    /**
     * Function to decide if a position vector r would be in the top child node.
     * @param r the vertex to test for 'top-ness'.
     * @return 2 if the position vector r would be in the top child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_top_child(const Vector3D<T>& r) const {
      auto r_mid = (r_min_ + r_max_) / T(2);

      if ((r_min_.y() <= r.y()) && (r.y() < r_mid.y())) {
        // Bottom
        return 0;
      }
      if ((r_mid.y() <= r.y()) && (r.y() <= r_max_.y())) {
        // Top
        return 2;
      }
      throw std::runtime_error(
        "Proposed position vector is not in the tree!"
      );
    }

    /**
     * Function to decide if a position vector r would be in the front child node.
     * @param r the vertex to test for 'front-ness'.
     * @return 4 if the position vector r would be in the front child node,
     *         otherwise 0.
     */
    [[nodiscard]] int
    is_front_child(const Vector3D<T>& r) const {
      auto r_mid = (r_min_ + r_max_) / T(2);

      if ((r_min_.z() <= r.z()) && (r.z() < r_mid.z())) {
        // Bottom
        return 0;
      }
      if ((r_mid.z() <= r.z()) && (r.z() <= r_max_.z())) {
        // Top
        return 4;
      }
      throw std::runtime_error(
        "Proposed position vector is not in the tree!"
      );
    }

    /**
     * Compute the sum-code index of the child that a proposed vertex is in.
     * @param r the position vector of a vertex.
     * @return the octree sum-code that the input position vector is in.
     */
    [[nodiscard]] OctreeSumCode
    which_child(const Vector3D<T>& r) const {
      const int left = is_right_child(r);
      const int top = is_top_child(r);
      const int front = is_front_child(r);

      return static_cast<OctreeSumCode>(left + top + front);
    }

    /**
     * Compute the sum-code index of the child that a proposed vertex is in.
     * of this node.
     * @param i the index of the vertex.
     * @return the octree sum-code of the i-th vertex.
     */
    [[nodiscard]] OctreeSumCode
    which_child(const size_t i) const {
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
    child_corners(const OctreeSumCode p) {
      auto r_mid = (r_min_ + r_max_) / T(2);
      switch (p) {
        case OCTREE_POSITION_BBR:
          return {
            {r_mid.x(), r_min_.y(), r_min_.z()},
            {r_max_.x(), r_mid.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BBL:
          return {
            {r_min_.x(), r_min_.y(), r_min_.z()},
            {r_mid.x(), r_mid.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BTR:
          return {
            {r_mid.x(), r_mid.y(), r_min_.z()},
            {r_max_.x(), r_max_.y(), r_mid.z()}
          };
        case OCTREE_POSITION_BTL:
          return {
            {r_min_.x(), r_mid.y(), r_min_.z()},
            {r_mid.x(), r_max_.y(), r_mid.z()}
          };
        case OCTREE_POSITION_FBR:
          return {
            {r_mid.x(), r_min_.y(), r_mid.z()},
            {r_max_.x(), r_mid.y(), r_max_.z()}
          };
        case OCTREE_POSITION_FBL:
          return {
            {r_min_.x(), r_min_.y(), r_mid.z()},
            {r_mid.x(), r_mid.y(), r_max_.z()}
          };
        case OCTREE_POSITION_FTR:
          return {
            {r_mid.x(), r_mid.y(), r_mid.z()},
            {r_max_.x(), r_max_.y(), r_max_.z()}
          };
        case OCTREE_POSITION_FTL:
          return {
            {r_min_.x(), r_mid.y(), r_mid.z()},
            {r_mid.x(), r_max_.y(), r_max_.z()}
          };
        default: throw std::runtime_error("Invalid sum-code!");
      }
    }

    /**
     * Computes the centroid of a tetrahedron.
     * @param i the index of the tetrahedron.
     * @return the centroid of the tetrahedron with index i.
     */
    [[nodiscard]] Vector3D<T>
    centroid(const int i) const {
      auto [n0, n1, n2, n3] = til_[i];
      return (vcl_[n0] + vcl_[n1] + vcl_[n2] + vcl_[n3]) / T(4);
    }

    /**
     * Add a tetrahedron index to the list of tetrahedron indices belonging to
     * this tree node.
     * @param tet_index the tetrahedron index to add.
     */
    void
    add_tet_index(const int tet_index) {
      tet_indices_.push_back(tet_index);
    }

    /**
     * Retrieve the tetrahedron indices belonging to this tree node.
     * @return the list of tetrahedron indices belonging to this tree node.
     */
    [[nodiscard]] const std::vector<int>&
    tet_indices() const {
      return tet_indices_;
    }

    /**
     * Retrieve the number of tetrahedron indices belonging to this tree node.
     * @return the number of tetrahedron indices belonging to this tree node.
     */
    [[nodiscard]] size_t
    n_tet_indices() const {
      return tet_indices_.size();
    }

    /**
     * Retrieve the index of the octree node.
     * @return the index of the octree node.
     */
    [[nodiscard]] int
    index() const {
      return index_;
    }

    /**
     * Sets the index of the octree node.
     * @param index the octree node's index.
     */
    void
    set_index(const int index) {
      index_ = index;
    }

    /**
     * Return the parent of the octree node (-1 represents the root).
     * @return the index of the octree node.
     */
    [[nodiscard]] int
    parent() const {
      return parent_;
    }

    /**
     * Sets the parent index of this octree node.
     * @param parent the new parent index
     */
    void
    set_parent(const int parent) {
      parent_ = parent;
    }

    /**
     * return the depth of the octree node.
     * @return the depth of the octree node.
     */
    [[nodiscard]] int
    depth() const {
      return depth_;
    }

    /**
     * Set the depth of this octree node.
     * @param depth the new depth.
     */
    void
    set_depth(const int depth) {
      depth_ = depth;
    }

    [[nodiscard]] int
    child(const OctreeSumCode sum_code) const {
      return children_[sum_code];
    }

    /**
     * Set the r_min extent of the octree node.
     * @param r_min the new r_min extent value.
     */
    void
    set_r_min(Vector3D<T> r_min) {
      r_min_ = r_min;
    }

    /**
     * Set the r_max extent of the octree node.
     * @param r_max the new r_max extent value.
     */
    void
    set_r_max(Vector3D<T> r_max) {
      r_max_ = r_max;
    }

    /**
     * Set the child node index at the `sum-code` position.
     * @param sum_code the sum-code position to set the new child index.
     * @param index the new value of the child index.
     */
    void
    set_child(const OctreeSumCode sum_code, const int index) {
      children_[sum_code] = index;
    }

    /**
     * Retrieve the children of this node.
     */
    [[nodiscard]] const std::array<int, 8>&
    children() const {
      return children_;
    }

    /**
     * Retrieve the volume of the node.
     */
    [[nodiscard]] double
    volume() const {
      return volume_;
    }

    /**
     * Retrieve the r_min value.
     * @return r_min the smallest extent of the box.
     */
    [[nodiscard]] const Vector3D<T>&
    r_min() const {
      return r_min_;
    }

    /**
     * Retrieve the r_max value.
     * @return r_max the smallest extent of the box.
     */
    [[nodiscard]] const Vector3D<T>&
    r_max() const {
      return r_max_;
    }

    /**
     * Retrieve the extents of the node
     * @return extents
     */
    [[nodiscard]] Vector3D<T>
    extents() const {
      return r_max_ - r_min_;
    }

  private:
    int index_;
    int parent_;
    int depth_;

    Vector3D<T> r_min_;
    Vector3D<T> r_max_;

    std::vector<int> tet_indices_;

    const VertexList3D<T>& vcl_;
    const IndexTupleList<4>& til_;

    T volume_ = 0;

    std::array<int, 8> children_{-1, -1, -1, -1, -1, -1, -1, -1};

    //*********************************************************************************************//
    //* Private member functions                                                                  *//
    //*********************************************************************************************//

    void compute_volume() {
      for (const auto& tid : tet_indices_) {
        BoundTetrahedron<T> bv(vcl_, til_, tid);
        volume_ += bv.volume();
      }
    }
};

template<typename T, int MAX_PER_NODE, int MAX_DEPTH>
class Octree {
  public:
    Octree(
      const VertexList3D<T>& vcl,
      const VectorListList3D<T>& fields,
      const IndexTupleList<4>& til
    ) : vcl_(vcl),
        fields_(fields),
        til_(til) {
      T r_min_x = vcl_[0].x();
      T r_min_y = vcl_[0].y();
      T r_min_z = vcl_[0].z();
      T r_max_x = vcl_[0].x();
      T r_max_y = vcl_[0].y();
      T r_max_z = vcl_[0].z();

      // Compute the extents of the first octree node.
      for (const auto& r : vcl_) {
        if (r.x() < r_min_x) r_min_x = r.x();
        if (r.y() < r_min_y) r_min_y = r.y();
        if (r.z() < r_min_z) r_min_z = r.z();
        if (r_max_x < r.x()) r_max_x = r.x();
        if (r_max_y < r.y()) r_max_y = r.y();
        if (r_max_z < r.z()) r_max_z = r.z();
      }

      // Create the first octree node.
      nodes_.emplace_back(
        vcl_,
        til_,
        Vector3D{r_min_x, r_min_y, r_min_z},
        Vector3D{r_max_x, r_max_y, r_max_z},
        0,
        0,
        -1
      );

      populate();
      finalize();
    }

    [[nodiscard]] const OctreeNode<T>&
    root() const {
      return nodes_[0];
    }

    /**
     * Function to compute the centroid of the tid-th tetrahedron.
     * @param tid the tetrahedron id of for which we wish to compute the sum.
     * @return the vector position of the centroid.
     */
    [[nodiscard]] Vector3D<T>
    centroid(const size_t tid) const {
      auto [n0, n1, n2, n3] = til_[tid];
      return (vcl_[n0] + vcl_[n1] + vcl_[n2] + vcl_[n3]) / T(4);
    }

    [[nodiscard]] int
    find_leaf_index_containing_tet_index(int tet_id) {
      std::stack<int> stack;
      stack.push(0);

      while (!stack.empty()) {
        auto node_index = stack.top();
        stack.pop();

        const auto& node = nodes_[node_index];

        if (node.is_leaf()) {
          for (auto tet_id2 : node.tet_indices()) {
            if (tet_id2 == tet_id) {
              return node.index();
            }
          }
        } else {
          for (auto node_id : node.children()) {
            if (!nodes_[node_id].tet_indices().empty()) {
              stack.push(node_id);
            }
          }
        }
      }
      return -1;
    }

    [[nodiscard]] std::optional<std::reference_wrapper<const OctreeNode<T>> >
    find_leaf_containing_tet_index(const int tet_id) {
      int leaf_index = find_leaf_index_containing_tet_index(tet_id);
      if (leaf_index == -1) {
        return std::nullopt;
      }
      return nodes_[leaf_index];
    }

    /**
     * Function to create a dot representation of the tree.
     * @param file_name the output file to write the dot representation to.
     */
    void
    write_dot(const std::string& file_name) const {
      // Open the file.
      std::ofstream os(file_name);
      if (!os.is_open()) {
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

        const auto& node = nodes_[node_index];

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
        ss_node << "volume: " << node.volume();
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
      os << "digraph G{" << std::endl;
      os << "    " <<
          "graph [splines=ortho, rankdir=LR, nodesep=0.5, overlap=false];" <<
          std::endl;
      os << "    " << "node [shape=box];" << std::endl;

      // Write nodes
      for (const auto& str_node : nodes) {
        os << str_node << std::endl;
      }

      // Write directed edges
      for (const auto& str_edge : edges) {
        os << str_edge << std::endl;
      }

      // Close the graph
      os << "}" << std::endl;

      // Close the file
      os.close();
    }

    /**
     * Retrieve all the nodes in the tree.
     */
    [[nodiscard]] const std::vector<OctreeNode<T> >&
    nodes() {
      return nodes_;
    }

    /**
     * Retrieve a reference to a particular node in the tree.
     * @param node_index the index of the node.
     * @return an octree node.
     */
    [[nodiscard]] const OctreeNode<T>&
    node(int node_index) {
      return nodes_[node_index];
    }

  private:
    std::vector<OctreeNode<T> > nodes_;

    const VertexList3D<T>& vcl_;
    const VectorListList3D<T>& fields_;
    const IndexTupleList<4>& til_;

    /**
     * Splits a node in to eight child nodes - this function will create eight new child nodes,
     * nodes children then refer to the indices of the eight nodes, these indices are returned.
     * @param node_index the index of the node to be split.
     * @return the indices of the new nodes (in sum-code position).
     */
    std::array<int, 8>
    split(int node_index) {
      // The output of the function is a list of indices of octree nodes, the
      // position of each octree node index is the sum-code.
      std::array octree_node_indices = {-1, -1, -1, -1, -1, -1, -1, -1};

      if (nodes_[node_index].is_leaf()) {
        // If the node is a leaf, we split it in to its eight children.
        for (int sum_code = 0; sum_code < 8; ++sum_code) {
          // For each of the sum-codes, find the extent of the child associated
          // with the current sum-code
          Vector3D<T> rmin, rmax;
          std::tie(rmin, rmax) =
              nodes_[node_index].child_corners(
                static_cast<OctreeSumCode>(sum_code)
              );

          // Create a new empty child node on our list of nodes.
          nodes_.emplace_back(vcl_, til_);

          // Create a reference to the new node.
          auto& child_node = nodes_.back();

          // Compute the index of the new child node.
          int new_node_index = nodes_.size() - 1;

          // Set the empty values of the new child node.
          child_node.set_r_min(rmin);
          child_node.set_r_max(rmax);
          child_node.set_depth(nodes_[node_index].depth() + 1);
          child_node.set_index(new_node_index);
          child_node.set_parent(nodes_[node_index].index());

          // Update the index of the child node in the node.
          nodes_[node_index].set_child(static_cast<OctreeSumCode>(sum_code), new_node_index);

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

      for (int tid = 0; tid < til_.size(); ++tid) {
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

          if (nodes_[oni].is_leaf()) {
            // The node is a leaf, so we add the current tetrahedron index to its
            // list of tetrahedron indices.
            nodes_[oni].add_tet_index(frame.tet_index);

            if (nodes_[oni].n_tet_indices() >= MAX_PER_NODE) {
              // Split the current node in to eight.
              auto child_octree_ids = split(nodes_[oni].index());

              for (auto tet_index : nodes_[oni].tet_indices()) {
                // Find the sum-code of the child nodes of each tetrahedron index.
                auto child_sum_code = nodes_[oni].which_child(tet_index);

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
            nodes_[oni].add_tet_index(frame.tet_index);

            // Find the sum-code of the child to which we should pass on the
            // tetrahedron index.
            auto child_sum_code = nodes_[oni].which_child(frame.tet_index);

            // Push the current tetrahedron index, along with the id of the
            // octree node index to which it belongs on to the stack.
            stack.push({frame.tet_index, nodes_[oni].child(child_sum_code)});
          }
        }
      }
    }

    /**
     * Finalizes the octree.
     */
    void
    finalize() {
      struct StackFrame {
        int nidx;
        bool visited;
      };
      std::stack<StackFrame> stack;

      stack.push({0, false});

      // Keep going until the stack is empty.
      while (!stack.empty()) {
        auto frame = stack.top();
        stack.pop();

        auto& node = nodes_[frame.nidx];

        if (node.is_leaf()) {
          node.compute_volume();
          continue;
        }

        if (frame.visited) {
          // All children have been visited
          auto result = node.volume();
          for (const auto& cidx : node.children()) {
            result += nodes_[cidx].volume();
          }
          node.volume_ = result;
        } else {
          // Not all children have been visited yet, push this node back with the visited flag set
          stack.push({frame.nidx, true});
          for (const auto cidx : node.children()) {
            if (cidx >= 0) {
              stack.push({cidx, false});
            }
          }
        }
      }
    }
};
} // namespace amiga
#endif //LIBFABBRI_INCLUDE_TREES_OCTREE_HPP_
