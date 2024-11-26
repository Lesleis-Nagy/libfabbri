//
// Created by Lesleis Nagy on 26/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include "cuboid.hpp"

TEST_CASE("Test FreeCuboid basic operations", "[FreeCuboid]") {

  Cuboid<double> *cub = new FreeCuboid<double>{
      {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}
  };

  REQUIRE(cub->signed_volume() == Approx(1.0));
  REQUIRE(cub->volume() == Approx(1.0));

  auto centroid = cub->centroid();
  REQUIRE(centroid.x() == Approx(0.5));
  REQUIRE(centroid.y() == Approx(0.5));
  REQUIRE(centroid.z() == Approx(0.5));

  REQUIRE(cub->type() == FreeCuboidType);

}

TEST_CASE("Test FreeCuboid: contains()", "[FreeCuboid]") {

  Cuboid<double> *cub = new FreeCuboid<double>{
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

TEST_CASE("Test BoundCuboid basic operations", "[BoundCuboid]") {

  VertexList<double> vcl = {
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0}
  };

  IndexTupleList<2> til = {
      {0, 1}
  };

  Cuboid<double> *cub = new BoundCuboid<double> {vcl, til, 0};

  REQUIRE(cub->signed_volume() == Approx(1.0));
  REQUIRE(cub->volume() == Approx(1.0));

  auto centroid = cub->centroid();
  REQUIRE(centroid.x() == Approx(0.5));
  REQUIRE(centroid.y() == Approx(0.5));
  REQUIRE(centroid.z() == Approx(0.5));

  REQUIRE(cub->type() == BoundCuboidType);

  // Since we know this is a BoundCuboid, cast it to a BoundCuboid
  // and make sure the index is correct.
  REQUIRE(((BoundCuboid<double>*)cub)->index() == 0);

}

TEST_CASE("Test BoundCuboid: contains()", "[BoundCuboid]") {

  VertexList<double> vcl = {
      {0.0, 0.0, 0.0},
      {1.0, 1.0, 1.0}
  };

  IndexTupleList<2> til = {
      {0, 1}
  };

  Cuboid<double> *cub = new BoundCuboid<double>{vcl, til, 0};

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
