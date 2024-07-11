//
// Created by Lesleis Nagy on 02/07/2024.
//

#include "writer_micromag.hpp"

#include "b_field_calculator.hpp"
#include "loader_micromag.hpp"
#include "sample_plane.hpp"
#include "writer_micromag.hpp"
#include "writer_xdmf.hpp"

int
main(int argc, char *argv[]) {

  auto model = MicromagFileLoader<3>::read(
      "/Users/lnagy2/Projects/libfabbri/test001.mmf");

  auto regular_grid = SamplePlane<double>{
      {0.08, 0.08, 0.08},
      0.0, 0.100, 0.100, 0.001};

}