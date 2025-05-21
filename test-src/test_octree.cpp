//
// Created by Lesleis Nagy on 25/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include "trees/octree.hpp"


TEST_CASE("is_leaf()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  REQUIRE(node.is_leaf() == true);

}

TEST_CASE("is_right_child()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  REQUIRE(node.is_right_child({0.2152, 0.9961, 0.4379}) == 0);
  REQUIRE(node.is_right_child({0.0503, 0.2235, 0.7400}) == 0);
  REQUIRE(node.is_right_child({0.8269, 0.4307, 0.5333}) == 1);
  REQUIRE(node.is_right_child({0.6883, 0.7401, 0.2100}) == 1);
  REQUIRE(node.is_right_child({0.2577, 0.6960, 0.9132}) == 0);
  REQUIRE(node.is_right_child({0.7704, 0.6094, 0.5256}) == 1);
  REQUIRE(node.is_right_child({0.1867, 0.3685, 0.9886}) == 0);
  REQUIRE(node.is_right_child({0.8248, 0.6814, 0.7465}) == 1);
  REQUIRE(node.is_right_child({0.2573, 0.4384, 0.8903}) == 0);
  REQUIRE(node.is_right_child({0.4864, 0.7931, 0.9831}) == 0);
  REQUIRE(node.is_right_child({0.7056, 0.3134, 0.0469}) == 1);
  REQUIRE(node.is_right_child({0.8595, 0.5601, 0.1397}) == 1);
  REQUIRE(node.is_right_child({0.1931, 0.6043, 0.8039}) == 0);
  REQUIRE(node.is_right_child({0.7485, 0.0528, 0.1841}) == 1);
  REQUIRE(node.is_right_child({0.0639, 0.4879, 0.2630}) == 0);
  REQUIRE(node.is_right_child({0.0110, 0.4203, 0.0715}) == 0);

}

TEST_CASE("is_top_child()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  REQUIRE(node.is_top_child({0.2152, 0.9961, 0.4379}) == 2);
  REQUIRE(node.is_top_child({0.0503, 0.2235, 0.7400}) == 0);
  REQUIRE(node.is_top_child({0.8269, 0.4307, 0.5333}) == 0);
  REQUIRE(node.is_top_child({0.6883, 0.7401, 0.2100}) == 2);
  REQUIRE(node.is_top_child({0.2577, 0.6960, 0.9132}) == 2);
  REQUIRE(node.is_top_child({0.7704, 0.6094, 0.5256}) == 2);
  REQUIRE(node.is_top_child({0.1867, 0.3685, 0.9886}) == 0);
  REQUIRE(node.is_top_child({0.8248, 0.6814, 0.7465}) == 2);
  REQUIRE(node.is_top_child({0.2573, 0.4384, 0.8903}) == 0);
  REQUIRE(node.is_top_child({0.4864, 0.7931, 0.9831}) == 2);
  REQUIRE(node.is_top_child({0.7056, 0.3134, 0.0469}) == 0);
  REQUIRE(node.is_top_child({0.8595, 0.5601, 0.1397}) == 2);
  REQUIRE(node.is_top_child({0.1931, 0.6043, 0.8039}) == 2);
  REQUIRE(node.is_top_child({0.7485, 0.0528, 0.1841}) == 0);
  REQUIRE(node.is_top_child({0.0639, 0.4879, 0.2630}) == 0);
  REQUIRE(node.is_top_child({0.0110, 0.4203, 0.0715}) == 0);

}

TEST_CASE("is_front_child()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  REQUIRE(node.is_front_child({0.2152, 0.9961, 0.4379}) == 0);
  REQUIRE(node.is_front_child({0.0503, 0.2235, 0.7400}) == 4);
  REQUIRE(node.is_front_child({0.8269, 0.4307, 0.5333}) == 4);
  REQUIRE(node.is_front_child({0.6883, 0.7401, 0.2100}) == 0);
  REQUIRE(node.is_front_child({0.2577, 0.6960, 0.9132}) == 4);
  REQUIRE(node.is_front_child({0.7704, 0.6094, 0.5256}) == 4);
  REQUIRE(node.is_front_child({0.1867, 0.3685, 0.9886}) == 4);
  REQUIRE(node.is_front_child({0.8248, 0.6814, 0.7465}) == 4);
  REQUIRE(node.is_front_child({0.2573, 0.4384, 0.8903}) == 4);
  REQUIRE(node.is_front_child({0.4864, 0.7931, 0.9831}) == 4);
  REQUIRE(node.is_front_child({0.7056, 0.3134, 0.0469}) == 0);
  REQUIRE(node.is_front_child({0.8595, 0.5601, 0.1397}) == 0);
  REQUIRE(node.is_front_child({0.1931, 0.6043, 0.8039}) == 4);
  REQUIRE(node.is_front_child({0.7485, 0.0528, 0.1841}) == 0);
  REQUIRE(node.is_front_child({0.0639, 0.4879, 0.2630}) == 0);
  REQUIRE(node.is_front_child({0.0110, 0.4203, 0.0715}) == 0);

}

TEST_CASE("which_child()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  REQUIRE(node.which_child({0.2152, 0.9961, 0.4379}) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child({0.0503, 0.2235, 0.7400}) == OCTREE_POSITION_FBL);
  REQUIRE(node.which_child({0.8269, 0.4307, 0.5333}) == OCTREE_POSITION_FBR);
  REQUIRE(node.which_child({0.6883, 0.7401, 0.2100}) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child({0.2577, 0.6960, 0.9132}) == OCTREE_POSITION_FTL);
  REQUIRE(node.which_child({0.7704, 0.6094, 0.5256}) == OCTREE_POSITION_FTR);
  REQUIRE(node.which_child({0.1867, 0.3685, 0.9886}) == OCTREE_POSITION_FBL);
  REQUIRE(node.which_child({0.8248, 0.6814, 0.7465}) == OCTREE_POSITION_FTR);
  REQUIRE(node.which_child({0.2573, 0.4384, 0.8903}) == OCTREE_POSITION_FBL);
  REQUIRE(node.which_child({0.4864, 0.7931, 0.9831}) == OCTREE_POSITION_FTL);
  REQUIRE(node.which_child({0.7056, 0.3134, 0.0469}) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child({0.8595, 0.5601, 0.1397}) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child({0.1931, 0.6043, 0.8039}) == OCTREE_POSITION_FTL);
  REQUIRE(node.which_child({0.7485, 0.0528, 0.1841}) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child({0.0639, 0.4879, 0.2630}) == OCTREE_POSITION_BBL);
  REQUIRE(node.which_child({0.0110, 0.4203, 0.0715}) == OCTREE_POSITION_BBL);

}

TEST_CASE("which_child() - indices", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0.50000, -0.00424, 0.00000},
      {-0.00424, -0.50000, 0.00000},
      {0.50000, -0.50000, 0.50000},
      {0.00424, 0.00000, 0.50000},
      {0.00424, 0.50000, 0.00000},
      {0.50000, 0.50000, 0.50000},
      {-0.50000, 0.50000, 0.50000},
      {-0.50000, 0.00424, 0.00000},
      {-0.50000, -0.50000, 0.50000},
      {0.00424, 0.00000, -0.50000},
      {0.50000, 0.50000, -0.50000},
      {0.50000, -0.50000, -0.50000},
      {-0.50000, 0.50000, -0.50000},
      {-0.50000, -0.50000, -0.50000},
  };

  IndexTupleList<4> til = {
      {13, 10, 0, 8},
      {13, 12, 8, 1},
      {13, 1, 8, 0},
      {12, 2, 8, 1},
      {12, 11, 8, 2},
      {11, 3, 8, 2},
      {10, 3, 0, 8},
      {11, 10, 8, 3},
      {13, 9, 4, 5},
      {13, 12, 1, 4},
      {13, 10, 5, 0},
      {12, 7, 4, 9},
      {10, 6, 9, 5},
      {11, 6, 7, 9},
      {11, 10, 6, 9},
      {11, 10, 3, 6},
      {13, 10, 9, 5},
      {12, 11, 7, 9},
      {12, 11, 2, 7},
      {13, 11, 10, 8},
      {13, 11, 9, 10},
      {13, 12, 4, 9},
      {13, 12, 11, 8},
      {13, 12, 9, 11},
  };

  OctreeNode<double> node(
      vcl, til,
      {-0.5, -0.5, -0.5},
      {0.5, 0.5, 0.5},
      0, 0, -1
  );

  REQUIRE(node.which_child(0) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child(1) == OCTREE_POSITION_BBL);
  REQUIRE(node.which_child(2) == OCTREE_POSITION_FBL);
  REQUIRE(node.which_child(3) == OCTREE_POSITION_FBL);
  REQUIRE(node.which_child(4) == OCTREE_POSITION_FBR);
  REQUIRE(node.which_child(5) == OCTREE_POSITION_FBR);
  REQUIRE(node.which_child(6) == OCTREE_POSITION_FBR);
  REQUIRE(node.which_child(7) == OCTREE_POSITION_FBR);
  REQUIRE(node.which_child(8) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child(9) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child(10) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child(11) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child(12) == OCTREE_POSITION_FTR);
  REQUIRE(node.which_child(13) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child(14) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child(15) == OCTREE_POSITION_FTR);
  REQUIRE(node.which_child(16) == OCTREE_POSITION_BTR);
  REQUIRE(node.which_child(17) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child(18) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child(19) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child(20) == OCTREE_POSITION_BBR);
  REQUIRE(node.which_child(21) == OCTREE_POSITION_BTL);
  REQUIRE(node.which_child(22) == OCTREE_POSITION_BBL);
  REQUIRE(node.which_child(23) == OCTREE_POSITION_BBL);

}

TEST_CASE("centroid()", "[OctreeNode]") {

  VertexList3D<double> vcl = {
      {0.50000, -0.00424, 0.00000},
      {-0.00424, -0.50000, 0.00000},
      {0.50000, -0.50000, 0.50000},
      {0.00424, 0.00000, 0.50000},
      {0.00424, 0.50000, 0.00000},
      {0.50000, 0.50000, 0.50000},
      {-0.50000, 0.50000, 0.50000},
      {-0.50000, 0.00424, 0.00000},
      {-0.50000, -0.50000, 0.50000},
      {0.00424, 0.00000, -0.50000},
      {0.50000, 0.50000, -0.50000},
      {0.50000, -0.50000, -0.50000},
      {-0.50000, 0.50000, -0.50000},
      {-0.50000, -0.50000, -0.50000},
  };

  IndexTupleList<4> til = {
      {13, 10, 0, 8},
      {13, 12, 8, 1},
      {13, 1, 8, 0},
      {12, 2, 8, 1},
      {12, 11, 8, 2},
      {11, 3, 8, 2},
      {10, 3, 0, 8},
      {11, 10, 8, 3},
      {13, 9, 4, 5},
      {13, 12, 1, 4},
      {13, 10, 5, 0},
      {12, 7, 4, 9},
      {10, 6, 9, 5},
      {11, 6, 7, 9},
      {11, 10, 6, 9},
      {11, 10, 3, 6},
      {13, 10, 9, 5},
      {12, 11, 7, 9},
      {12, 11, 2, 7},
      {13, 11, 10, 8},
      {13, 11, 9, 10},
      {13, 12, 4, 9},
      {13, 12, 11, 8},
      {13, 12, 9, 11},
  };

  std::vector<std::array<double, 3>> exp = {
      {0.00000000, -0.12606001, -0.12500000},
      {-0.37606001, -0.25000000, -0.12500000},
      {-0.12606001, -0.37606001, 0.00000000},
      {-0.12606001, -0.25000000, 0.12500000},
      {0.00000000, -0.25000000, 0.00000000},
      {0.12606001, -0.37500000, 0.25000000},
      {0.12606001, -0.00106001, 0.12500000},
      {0.12606001, -0.12500000, 0.00000000},
      {0.00212003, 0.12500000, -0.12500000},
      {-0.25000000, 0.00000000, -0.25000000},
      {0.25000000, 0.12393999, -0.12500000},
      {-0.24787997, 0.25106001, -0.25000000},
      {0.12606001, 0.37500000, 0.00000000},
      {-0.12393999, 0.00106001, -0.12500000},
      {0.12606001, 0.12500000, -0.25000000},
      {0.12606001, 0.12500000, 0.00000000},
      {0.12606001, 0.12500000, -0.25000000},
      {-0.12393999, 0.00106001, -0.37500000},
      {0.00000000, -0.12393999, -0.12500000},
      {0.00000000, -0.25000000, -0.25000000},
      {0.12606001, -0.12500000, -0.50000000},
      {-0.24787997, 0.12500000, -0.37500000},
      {-0.25000000, -0.25000000, -0.25000000},
      {-0.12393999, -0.12500000, -0.50000000},
  };

  OctreeNode<double> node(
      vcl, til,
      {-0.5, -0.5, -0.5},
      {0.5, 0.5, 0.5},
      0, 0, -1
  );

  double eps = 1e-7;

  for (int i = 0; i < 24; ++i) {
    REQUIRE(abs(node.centroid(i).x() - exp[i][0]) < eps);
    REQUIRE(abs(node.centroid(i).y() - exp[i][1]) < eps);
    REQUIRE(abs(node.centroid(i).z() - exp[i][2]) < eps);
  }
}

TEST_CASE("child_corners()", "[OctreeNode]") {
  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  OctreeNode<double> node(
      vcl, til,
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0},
      0, 0, -1
  );

  Vector3D<double> rmin, rmax;

  // OCTREE_POSITION_BBR

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_BBR);

  REQUIRE(abs(rmin.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.0) < 1E-10);

  REQUIRE(abs(rmax.x() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.z() - 0.5) < 1E-10);

  // OCTREE_POSITION_BBL

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_BBL);

  REQUIRE(abs(rmin.x() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.0) < 1E-10);

  REQUIRE(abs(rmax.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.z() - 0.5) < 1E-10);

  // OCTREE_POSITION_BTR

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_BTR);

  REQUIRE(abs(rmin.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.0) < 1E-10);

  REQUIRE(abs(rmax.x() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.y() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.z() - 0.5) < 1E-10);

  // OCTREE_POSITION_BTL

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_BTL);

  REQUIRE(abs(rmin.x() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.0) < 1E-10);

  REQUIRE(abs(rmax.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.y() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.z() - 0.5) < 1E-10);

  // OCTREE_POSITION_FBR

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_FBR);

  REQUIRE(abs(rmin.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.5) < 1E-10);

  REQUIRE(abs(rmax.x() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.z() - 1.0) < 1E-10);

  // OCTREE_POSITION_FBL

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_FBL);

  REQUIRE(abs(rmin.x() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.5) < 1E-10);

  REQUIRE(abs(rmax.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.z() - 1.0) < 1E-10);

  // OCTREE_POSITION_FTR

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_FTR);

  REQUIRE(abs(rmin.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.5) < 1E-10);

  REQUIRE(abs(rmax.x() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.y() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.z() - 1.0) < 1E-10);

  // OCTREE_POSITION_FTL

  std::tie(rmin, rmax) = node.child_corners(OCTREE_POSITION_FTL);

  REQUIRE(abs(rmin.x() - 0.0) < 1E-10);
  REQUIRE(abs(rmin.y() - 0.5) < 1E-10);
  REQUIRE(abs(rmin.z() - 0.5) < 1E-10);

  REQUIRE(abs(rmax.x() - 0.5) < 1E-10);
  REQUIRE(abs(rmax.y() - 1.0) < 1E-10);
  REQUIRE(abs(rmax.z() - 1.0) < 1E-10);

}

TEST_CASE("Octree: Basic tree construction", "[Octree]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  VectorListList3D<double> fields = {
      {
          {1.0, 0.0, 0.0},
          {0.0, 1.0, 0.0},
          {0.0, 0.0, 1.0},
          {sqrt(1.0 / 3.0), sqrt(1.0 / 3.0), sqrt(1.0 / 3.0)}
      }
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  Octree<double, 3, 4> octree(vcl, fields, til);

}

TEST_CASE("Octree: find_leaf_index_containing_tet_index", "[Octree]") {

    VertexList3D<double> vcl = {
  {   0.037168885097203,    0.037168885097203,    0.500000000000000},
  {   0.000000000000000,   -0.500000000000000,    0.500000000000000},
  {  -0.500000000000000,   -0.500000000000000,    0.000000000000000},
  {  -0.037168885097204,   -0.500000000000000,   -0.037168885097203},
  {  -0.500000000000000,    0.500000000000000,    0.000000000000000},
  {   0.000000000000000,    0.500000000000000,    0.500000000000000},
  {  -0.500000000000000,    0.000000000000000,    0.500000000000000},
  {  -0.500000000000000,   -0.500000000000000,    0.500000000000000},
  {   0.500000000000000,   -0.037168885097204,   -0.037168885097203},
  {   0.500000000000000,   -0.500000000000000,   -0.500000000000000},
  {   0.000000000000000,   -0.500000000000000,   -0.500000000000000},
  {   0.037168885097203,   -0.037168885097203,   -0.500000000000000},
  {   0.500000000000000,    0.000000000000000,   -0.500000000000000},
  {   0.037168885097203,    0.500000000000000,   -0.037168885097203},
  {   0.000000000000000,    0.500000000000000,   -0.500000000000000},
  {   0.500000000000000,    0.500000000000000,    0.000000000000000},
  {   0.500000000000000,    0.500000000000000,   -0.500000000000000},
  {  -0.183512429123672,    0.007912059693842,   -0.225483911425726},
  {  -0.500000000000000,    0.500000000000000,   -0.500000000000000},
  {  -0.500000000000000,    0.000000000000000,   -0.500000000000000},
  {  -0.500000000000000,   -0.500000000000000,   -0.500000000000000},
  {  -0.500000000000000,    0.037168885097203,   -0.037168885097203},
  {   0.500000000000000,   -0.500000000000000,    0.000000000000000},
  {   0.500000000000000,    0.000000000000000,    0.500000000000000},
  {   0.500000000000000,    0.500000000000000,    0.500000000000000},
  {  -0.500000000000000,    0.500000000000000,    0.500000000000000},
  {   0.500000000000000,   -0.500000000000000,    0.500000000000000}
};

    VectorListList3D<double> fields = {};

IndexTupleList<4> til = {
 {  0,   1,   2,   3},
 {  4,   5,   6,   0},
 {  2,   7,   1,   6},
 {  8,   9,  10,  11},
 {  8,  12,   9,  11},
 { 13,  14,  12,  11},
 { 15,  13,  16,  12},
 {  2,   1,   0,   6},
 { 13,  14,  16,  12},
 { 17,  13,  11,  14},
 {  0,  13,   4,   5},
 { 17,   4,  14,  18},
 { 17,  19,  11,  10},
 { 17,  20,  19,  10},
 { 17,   2,   0,  21},
 { 17,   2,  19,  20},
 { 17,  10,   8,   3},
 {  8,  22,   1,   3},
 { 17,  18,  14,  19},
 {  0,   2,  17,   3},
 { 17,  19,  14,  11},
 {  0,   4,  21,   6},
 { 17,   0,   4,  21},
 { 17,  13,  14,   4},
 {  2,   6,   0,  21},
 {  0,  15,  13,   5},
 {  8,  13,  12,  11},
 {  0,   8,  13,  15},
 {  8,  15,  12,  13},
 {  8,  22,  10,   9},
 {  1,  22,   8,  23},
 {  8,  22,   3,  10},
 { 17,   8,  11,  13},
 {  0,  15,   5,  24},
 {  6,   5,   4,  25},
 { 17,   0,   3,   8},
 {  8,  10,  17,  11},
 { 17,  21,  19,   2},
 { 17,   0,   8,  13},
 { 17,   0,  13,   4},
 { 17,   3,  20,  10},
 { 17,  21,  18,  19},
 { 17,   2,  20,   3},
 { 17,   4,  18,  21},
 {  1,   8,   0,  23},
 { 23,   0,  15,   8},
 { 23,   0,  24,  15},
 {  0,   8,   1,   3},
 { 23,   1,  22,  26}
};

VertexList3D<double> centroids = {
 {  -0.125000000000000,   -0.365707778725699,    0.240707778725699},
 {  -0.240707778725699,    0.259292221274301,    0.375000000000000},
 {  -0.375000000000000,   -0.375000000000000,    0.375000000000000},
 {   0.259292221274301,   -0.268584442548602,   -0.384292221274301},
 {   0.384292221274301,   -0.143584442548602,   -0.384292221274301},
 {   0.143584442548602,    0.240707778725699,   -0.384292221274301},
 {   0.384292221274301,    0.375000000000000,   -0.259292221274301},
 {  -0.240707778725699,   -0.240707778725699,    0.375000000000000},
 {   0.259292221274301,    0.375000000000000,   -0.384292221274301},
 {  -0.027293664732316,    0.242685793649160,   -0.315663199130732},
 {  -0.106415557451398,    0.384292221274301,    0.240707778725699},
 {  -0.295878107280918,    0.376978014923461,   -0.306370977856431},
 {  -0.161585886006617,   -0.132314206350840,   -0.431370977856431},
 {  -0.295878107280918,   -0.248021985076539,   -0.431370977856431},
 {  -0.286585886006617,   -0.104437542527938,    0.059336800869268},
 {  -0.420878107280918,   -0.248021985076539,   -0.306370977856431},
 {   0.069829671444781,   -0.257314206350840,   -0.199955420405033},
 {   0.240707778725699,   -0.384292221274301,    0.106415557451398},
 {  -0.295878107280918,    0.251978014923461,   -0.431370977856431},
 {  -0.170878107280918,   -0.238729763802239,    0.059336800869268},
 {  -0.161585886006617,    0.117685793649160,   -0.431370977856431},
 {  -0.365707778725699,    0.143584442548602,    0.240707778725699},
 {  -0.286585886006617,    0.145562457472062,    0.059336800869268},
 {  -0.161585886006617,    0.376978014923461,   -0.190663199130732},
 {  -0.365707778725699,   -0.106415557451398,    0.240707778725699},
 {   0.143584442548602,    0.384292221274301,    0.240707778725699},
 {   0.268584442548602,    0.106415557451398,   -0.268584442548602},
 {   0.268584442548602,    0.250000000000000,    0.106415557451398},
 {   0.384292221274301,    0.240707778725699,   -0.143584442548602},
 {   0.375000000000000,   -0.384292221274301,   -0.259292221274301},
 {   0.375000000000000,   -0.259292221274301,    0.240707778725699},
 {   0.240707778725699,   -0.384292221274301,   -0.143584442548602},
 {   0.097706335267684,    0.108393572374859,   -0.199955420405033},
 {   0.259292221274301,    0.384292221274301,    0.375000000000000},
 {  -0.375000000000000,    0.375000000000000,    0.375000000000000},
 {   0.079121892719082,   -0.123021985076540,    0.050044579594967},
 {   0.088414113993383,   -0.141606427625141,   -0.315663199130732},
 {  -0.420878107280918,   -0.113729763802239,   -0.190663199130732},
 {   0.097706335267684,    0.126978014923460,    0.050044579594967},
 {  -0.152293664732316,    0.261270236197761,    0.059336800869268},
 {  -0.180170328555219,   -0.373021985076539,   -0.315663199130732},
 {  -0.420878107280918,    0.136270236197761,   -0.315663199130732},
 {  -0.305170328555219,   -0.373021985076539,   -0.190663199130732},
 {  -0.420878107280918,    0.261270236197761,   -0.190663199130732},
 {   0.259292221274301,   -0.125000000000000,    0.365707778725699},
 {   0.384292221274301,    0.125000000000000,    0.240707778725699},
 {   0.384292221274301,    0.259292221274301,    0.375000000000000},
 {   0.125000000000000,   -0.250000000000000,    0.231415557451398},
 {   0.375000000000000,   -0.375000000000000,    0.375000000000000}
};

    /*
  std::vector<int> depth = {
      2, 1, 1, 1, 2, 2, 2, 2, 2, 2,
      2, 2, 1, 2, 2, 1, 2, 2, 2, 2,
      2, 2, 1, 1
  };
  */

    Octree<double, 4, 4> octree(vcl, fields, til);

    /*
  for (int tid = 0; tid < centroids.size(); ++tid) {
    // Find the leaf-element in the tree that contains the tetraheron (centroid) index `tid`
    auto node_value = octree.find_leaf_containing_tet_index(tid); // Make sure the leaf could be found REQUIRE(node_value.has_value()); const auto &node = node_value.value().get(); // Get the x/y/z coordinate of the test-centroid
    double rc_x = centroids[tid].x();
    double rc_y = centroids[tid].y();
    double rc_z = centroids[tid].z();

    // Make sure that the test-centroid is within the box representing the leaf
    REQUIRE(node.r_min().x() <= rc_x);
    REQUIRE(rc_x <= node.r_max().x());
    REQUIRE(node.r_min().y() <= rc_y);
    REQUIRE(rc_y <= node.r_max().y());
    REQUIRE(node.r_min().z() <= rc_z);
    REQUIRE(rc_z <= node.r_max().z());

    // Make sure the box containing the test-centroid is at the correct depth
    REQUIRE(node.depth() == depth[tid]);

    // Make sure that the box containing the test-centroid has the correct dimensions
    auto extents = node.extents();
    auto root_extent = octree.root().extents();

    auto expected_dx = root_extent.x() / pow(2.0, node.depth());
    auto actual_dx = extents.x();

    REQUIRE(abs(expected_dx - actual_dx) < 1E-12);
  }
  */

  double expected_volume = 0.0;
  for (size_t tid = 0; tid < til.size(); ++tid) {
    auto [n0, n1, n2, n3] = til[tid];
    auto r0 = vcl[n0], r1 = vcl[n1], r2 = vcl[n2], r3 = vcl[n3];
    FreeTetrahedron<double> ftet(r0, r1, r2, r3);
    std::cout << "Volume of " << std::setw(3) << tid << " = " << ftet.volume() << std::endl;
    expected_volume += ftet.volume();
  }

  std::cout << expected_volume << std::endl;
  std::cout << octree.node(0).volume() << std::endl;

  octree.write_dot("myoctree.dot");
}
