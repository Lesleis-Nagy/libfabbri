//
// Created by Lesleis Nagy on 29/06/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <array>

#include "sample_plane.hpp"
#include "writer_micromag.hpp"
#include "writer_xdmf.hpp"

std::vector<std::array<double, 3>>
test_field_rand(size_t n) {

  std::random_device dev;
  std::mt19937 rng(dev());

  // distribution in range [-1, 1]
  std::uniform_real_distribution<> d(-1.0, 1.0);

  std::vector<std::array<double, 3>> output(n);
  for (size_t i = 0; i < n; ++i) {
    output[i] = {d(rng), d(rng), d(rng)};
  }

  return output;

}

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

  FieldList fields;
  fields.add_field({"30.0 mT", test_field_rand(8)});
  fields.add_field({"40.0 mT", test_field_rand(8)});

  double eps = 1E-14;

  size_t exp_idx = 0;

  auto vcl = sample_plane.vcl();
  auto cil = sample_plane.cil();
  auto sml = sample_plane.sml();

  for (size_t i = 0; i < vcl.size(); ++i) {

      REQUIRE(abs(vcl[i][0] - expected[i].x()) < eps);
      REQUIRE(abs(vcl[i][1] - expected[i].y()) < eps);
      REQUIRE(abs(vcl[i][2] - expected[i].z()) < eps);

  }

  Mesh<2> mesh{sample_plane};
  Model<2> model{mesh, fields};

  std::string mmf_file = "sample_plane.mmf";
  std::string xdmf_file = "sample_plane.xdmf";

  MicromagFileWriter<2>::write(mmf_file, model);
  XDMFFileWriter<2>::write(xdmf_file, mmf_file, model);

}