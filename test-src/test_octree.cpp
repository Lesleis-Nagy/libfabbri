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

  VectorListList3D<double> fields = {};

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

  // These are the test centroids of the input tetrahedra.
  VertexList3D<double> centroids = {
      {0.00000, -0.12606, -0.12500},
      {-0.37606, -0.25000, -0.12500},
      {-0.12606, -0.37606, 0.00000},
      {-0.12606, -0.25000, 0.12500},
      {0.00000, -0.25000, 0.00000},
      {0.12606, -0.37500, 0.25000},
      {0.12606, -0.00106, 0.12500},
      {0.12606, -0.12500, 0.00000},
      {0.00212, 0.12500, -0.12500},
      {-0.25000, 0.00000, -0.25000},
      {0.25000, 0.12394, -0.12500},
      {-0.24788, 0.25106, -0.25000},
      {0.12606, 0.37500, 0.00000},
      {-0.12394, 0.00106, -0.12500},
      {0.12606, 0.12500, -0.25000},
      {0.12606, 0.12500, 0.00000},
      {0.12606, 0.12500, -0.25000},
      {-0.12394, 0.00106, -0.37500},
      {0.00000, -0.12394, -0.12500},
      {0.00000, -0.25000, -0.25000},
      {0.12606, -0.12500, -0.50000},
      {-0.24788, 0.12500, -0.37500},
      {-0.25000, -0.25000, -0.25000},
      {-0.12394, -0.12500, -0.50000},
  };

  std::vector<int> depth = {
      2, 1, 1, 1, 2, 2, 2, 2, 2, 2,
      2, 2, 1, 2, 2, 1, 2, 2, 2, 2,
      2, 2, 1, 1
  };

  Octree<double, 4, 4> octree(vcl, fields, til);

  for (int tid = 0; tid < centroids.size(); ++tid) {
    // Find the leaf-element in the tree that contains the tetraheron (centroid) index `tid`
    auto node_value = octree.find_leaf_containing_tet_index(tid);

    // Make sure the leaf could be found
    REQUIRE(node_value.has_value());

    const auto &node = node_value.value().get();

    // Get the x/y/z coordinate of the test-centroid
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
}
