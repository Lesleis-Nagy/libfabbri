//
// Created by Lesleis Nagy on 26/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include "tetrahedron.hpp"

TEST_CASE("Test FreeTetrahedron", "[FreeTetrahedron]") {

  Tetrahedron<double> *tet = new FreeTetrahedron<double>{
      {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}
  };

  REQUIRE(tet->det() == Approx(-1.0));
  REQUIRE(tet->signed_volume() == Approx(-1.0 / 6.0));
  REQUIRE(tet->volume() == Approx(1.0 / 6.0));

  auto centroid = tet->centroid();
  REQUIRE(centroid.x() == Approx(0.25));
  REQUIRE(centroid.y() == Approx(0.25));
  REQUIRE(centroid.z() == Approx(0.25));

  REQUIRE(tet->type() == FreeTetrahedronType);

}

TEST_CASE("Test BoundTetrahedron", "[BoundTetrahedron]") {

  VertexList3D<double> vcl = {
      {0.0, 0.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {0.0, 0.0, 1.0}
  };

  IndexTupleList<4> til = {
      {0, 1, 2, 3}
  };

  Tetrahedron<double> *tet = new BoundTetrahedron<double> {vcl, til, 0};

  REQUIRE(tet->det() == Approx(-1.0));
  REQUIRE(tet->signed_volume() == Approx(-1.0 / 6.0));
  REQUIRE(tet->volume() == Approx(1.0 / 6.0));

  auto centroid = tet->centroid();
  REQUIRE(centroid.x() == Approx(0.25));
  REQUIRE(centroid.y() == Approx(0.25));
  REQUIRE(centroid.z() == Approx(0.25));

  REQUIRE(tet->type() == BoundTetrahedronType);

  // Since we know this is a BoundTetrahedron, cast it to a BoundTetrahedron
  // and make sure the index is correct.
  REQUIRE(((BoundTetrahedron<double>*)tet)->index() == 0);

}
