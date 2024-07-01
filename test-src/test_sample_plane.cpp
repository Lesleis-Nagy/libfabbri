//
// Created by Lesleis Nagy on 29/06/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <array>

#include "sample_plane.hpp"

TEST_CASE("sample_plane_01", "Generate a sample plane") {

  SamplePlane<double> sample_plane{
      {1, 1, 1},
      0.0 * M_PI/180.0,
      2.0,
      1.0,
      0.5
  };

  std::vector<Vector3D<double>> expected = {
      {1.1830127018922190, 1.6830127018922190, 0.1339745962155614},
      {1.2886751345948130, 1.2886751345948130, 0.4226497308103743},
      {1.3943375672974060, 0.8943375672974060, 0.7113248654051871},
      {               1.5,                0.5,                1.0},
      {0.7886751345948129, 1.7886751345948130, 0.4226497308103743},
      {0.8943375672974060, 1.3943375672974060, 0.7113248654051871},
      {               1.0,                1.0,                1.0},
      {1.1056624327025930, 0.6056624327025935, 1.2886751345948130}
  };

  double eps = 1E-14;

  size_t exp_idx = 0;
  for (size_t i = 0; i < sample_plane.ny(); ++i) {
    for (size_t j = 0; j < sample_plane.nx(); ++j) {
      auto r = sample_plane(i, j);

      REQUIRE(abs(r.x() - expected[exp_idx].x()) < eps);
      REQUIRE(abs(r.y() - expected[exp_idx].y()) < eps);
      REQUIRE(abs(r.z() - expected[exp_idx].z()) < eps);

      ++exp_idx;

    }
  }

}