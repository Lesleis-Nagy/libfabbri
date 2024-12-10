//
// Created by Lesleis Nagy on 26/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include "box.hpp"

TEST_CASE("Test FreeBox basic operations", "[FreeBox]") {

  Box<double> *cub = new FreeBox<double>{
      {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}
  };

  REQUIRE(cub->signed_volume() == Approx(1.0));
  REQUIRE(cub->volume() == Approx(1.0));

  auto centroid = cub->centroid();
  REQUIRE(centroid.x() == Approx(0.5));
  REQUIRE(centroid.y() == Approx(0.5));
  REQUIRE(centroid.z() == Approx(0.5));

  REQUIRE(cub->type() == FreeBoxType);

}

TEST_CASE("Test FreeBox: contains()", "[FreeBox]") {

  Box<double> *cub = new FreeBox<double>{
      {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}
  };

  REQUIRE(cub->contains({0.5, 0.5, 0.5}) == true);

  REQUIRE(cub->contains({1.0, 0.0, 0.0}) == true);
  REQUIRE(cub->contains({0.0, 0.0, 0.0}) == true);
  REQUIRE(cub->contains({1.0, 1.0, 0.0}) == true);
  REQUIRE(cub->contains({0.0, 1.0, 0.0}) == true);

  REQUIRE(cub->contains({1.0, 0.0, 1.0}) == true);
  REQUIRE(cub->contains({0.0, 0.0, 1.0}) == true);
  REQUIRE(cub->contains({1.0, 1.0, 1.0}) == true);
  REQUIRE(cub->contains({0.0, 1.0, 1.0}) == true);

  double eps = 1E-10;

  REQUIRE(cub->contains({1.0+eps, 0.0, 0.0}) == false);
  REQUIRE(cub->contains({0.0-eps, 0.0, 0.0}) == false);
  REQUIRE(cub->contains({1.0+eps, 1.0, 0.0}) == false);
  REQUIRE(cub->contains({0.0, 1.0, 0.0-eps}) == false);

  REQUIRE(cub->contains({1.0+eps, 0.0, 1.0}) == false);
  REQUIRE(cub->contains({0.0-eps, 0.0, 1.0}) == false);
  REQUIRE(cub->contains({1.0, 1.0+eps, 1.0}) == false);
  REQUIRE(cub->contains({0.0, 1.0, 1.0+eps}) == false);

}

TEST_CASE("Test BoundBox basic operations", "[BoundBox]") {

  VertexList3D<double> vcl = {
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0}
  };

  IndexTupleList<2> til = {
      {0, 1}
  };

  Box<double> *cub = new BoundBox<double> {vcl, til, 0};

  REQUIRE(cub->signed_volume() == Approx(1.0));
  REQUIRE(cub->volume() == Approx(1.0));

  auto centroid = cub->centroid();
  REQUIRE(centroid.x() == Approx(0.5));
  REQUIRE(centroid.y() == Approx(0.5));
  REQUIRE(centroid.z() == Approx(0.5));

  REQUIRE(cub->type() == BoundBoxType);

  // Since we know this is a BoundBox, cast it to a BoundBox
  // and make sure the index is correct.
  REQUIRE(((BoundBox<double>*)cub)->index() == 0);

}

TEST_CASE("Test BoundBox: contains()", "[BoundBox]") {

  VertexList3D<double> vcl = {
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0}
  };

  IndexTupleList<2> til = {
      {0, 1}
  };

  Box<double> *cub = new BoundBox<double>{vcl, til, 0};

  REQUIRE(cub->contains({0.5, 0.5, 0.5}) == true);

  REQUIRE(cub->contains({1.0, 0.0, 0.0}) == true);
  REQUIRE(cub->contains({0.0, 0.0, 0.0}) == true);
  REQUIRE(cub->contains({1.0, 1.0, 0.0}) == true);
  REQUIRE(cub->contains({0.0, 1.0, 0.0}) == true);

  REQUIRE(cub->contains({1.0, 0.0, 1.0}) == true);
  REQUIRE(cub->contains({0.0, 0.0, 1.0}) == true);
  REQUIRE(cub->contains({1.0, 1.0, 1.0}) == true);
  REQUIRE(cub->contains({0.0, 1.0, 1.0}) == true);

  double eps = 1E-10;

  REQUIRE(cub->contains({1.0+eps, 0.0, 0.0}) == false);
  REQUIRE(cub->contains({0.0-eps, 0.0, 0.0}) == false);
  REQUIRE(cub->contains({1.0+eps, 1.0, 0.0}) == false);
  REQUIRE(cub->contains({0.0, 1.0, 0.0-eps}) == false);

  REQUIRE(cub->contains({1.0+eps, 0.0, 1.0}) == false);
  REQUIRE(cub->contains({0.0-eps, 0.0, 1.0}) == false);
  REQUIRE(cub->contains({1.0, 1.0+eps, 1.0}) == false);
  REQUIRE(cub->contains({0.0, 1.0, 1.0+eps}) == false);

}
