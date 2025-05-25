#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <amiga/matrix.hpp>
#include "mpreal.h"

//###############################################################################################//
//# Test addition                                                                               #//
//###############################################################################################//

TEST_CASE("Test matrix addition for 'double' type.", "Matrix") {
  using namespace amiga;

  Matrix<double, 2> matrix {
    {1.0, 2.0}, {3.0, 4.0}
  };

  std::cout << matrix << std::endl;

}