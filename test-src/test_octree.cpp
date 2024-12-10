//
// Created by Lesleis Nagy on 25/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>
#include <random>

#include "trees/octree.hpp" // Replace with the path to your Octree header file

TEST_CASE("Octree: Basic Insertion and Query", "[Octree]") {

  VertexList3D<double> vcl = {
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  Octree<double, 3, 4> octree(vcl, til);

}
