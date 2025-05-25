//
// Created by Lesleis Nagy on 19/03/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <amiga/matrix3x3.hpp>
#include "mpreal.h"

//###############################################################################################//
//# Test addition                                                                               #//
//###############################################################################################//

TEST_CASE("Test matrix addition for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {11.0, 13.0, 15.0},
    {17.0, 19.0, 21.0},
    {23.0, 25.0, 27.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 + m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix addition for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {11.0, 13.0, 15.0},
    {17.0, 19.0, 21.0},
    {23.0, 25.0, 27.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 + m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###############################################################################################//
//# Test subtraction                                                                            #//
//###############################################################################################//

TEST_CASE("Test matrix subtraction for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {9.0, 9.0, 9.0},
    {9.0, 9.0, 9.0},
    {9.0, 9.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m1 - m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix subtraction for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {9.0, 9.0, 9.0},
    {9.0, 9.0, 9.0},
    {9.0, 9.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m1 - m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test scalar-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test scalar-matrix multiplication for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double lambda = 2.0;

  Mat3x3 expected = {
    {2.0, 4.0, 6.0},
    {8.0, 10.0, 12.0},
    {14.0, 16.0, 18.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = lambda * m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test scalar-matrix multiplication for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  mpreal lambda = 2.0;

  Mat3x3 expected = {
    {2.0, 4.0, 6.0},
    {8.0, 10.0, 12.0},
    {14.0, 16.0, 18.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = lambda * m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix-scalar multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-scalar multiplication for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double lambda = 2.0;

  Mat3x3 expected = {
    {2.0, 4.0, 6.0},
    {8.0, 10.0, 12.0},
    {14.0, 16.0, 18.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 * lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix-scalar multiplication for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  mpreal lambda = 2.0;

  Mat3x3 expected = {
    {2.0, 4.0, 6.0},
    {8.0, 10.0, 12.0},
    {14.0, 16.0, 18.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 * lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test matrix-scalar division for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double lambda = 2.0;

  Mat3x3 expected = {
    {0.5, 1.0, 1.5},
    {2.0, 2.5, 3.0},
    {3.5, 4.0, 4.5}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 / lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix-scalar division for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  mpreal lambda = 2.0;

  Mat3x3 expected = {
    {0.5, 1.0, 1.5},
    {2.0, 2.5, 3.0},
    {3.5, 4.0, 4.5}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 / lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix-vector multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-vector multiplication for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Vec3 = Vector3D<double>;
  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 v = {1.0, 2.0, 3.0};

  const Vec3 expected = {
    1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0, // 14.0
    4.0 * 1.0 + 5.0 * 2.0 + 6.0 * 3.0, // 32.0
    7.0 * 1.0 + 8.0 * 2.0 + 9.0 * 3.0 // 50.0
  };

  constexpr double eps = 1E-14;

  const Vec3 actual = m0 * v;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

TEST_CASE("Test matrix-vector multiplication for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Vec3 = Vector3D<double>;
  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 v = {1.0, 2.0, 3.0};

  const Vec3 expected = {
    1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0, // 14.0
    4.0 * 1.0 + 5.0 * 2.0 + 6.0 * 3.0, // 32.0
    7.0 * 1.0 + 8.0 * 2.0 + 9.0 * 3.0 // 50.0
  };

  constexpr double eps = 1E-14;

  const Vec3 actual = m0 * v;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

//###########################################################################//
//# Test vector-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test vector-matrix multiplication for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Vec3 = Vector3D<double>;
  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 v = {1.0, 2.0, 3.0};

  const Vec3 expected = {30.0, 36.0, 42.0};

  constexpr double eps = 1E-14;

  const Vec3 actual = v * m0;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

TEST_CASE("Test vector-matrix multiplication for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Vec3 = Vector3D<double>;
  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 v = {1.0, 2.0, 3.0};

  const Vec3 expected = {30.0, 36.0, 42.0};

  const mpreal eps = 1E-14;

  const Vec3 actual = v * m0;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

//###########################################################################//
//# Test matrix-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-matrix multiplication for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {84.0, 90.0, 96.0},
    {201.0, 216.0, 231.0},
    {318.0, 342.0, 366.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = m0 * m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix-matrix multiplication for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  Mat3x3 expected = {
    {84.0, 90.0, 96.0},
    {201.0, 216.0, 231.0},
    {318.0, 342.0, 366.0}
  };

  mpreal eps = 1E-14;

  Mat3x3 actual = m0 * m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix adjugate                                                    #//
//###########################################################################//

TEST_CASE("Test matrix adjugate for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 expected = {
    {-3.0, 6.0, -3.0},
    {6.0, -12.0, 6.0},
    {-3.0, 6.0, -3.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = adj(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix adjugate for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 expected = {
    {-3.0, 6.0, -3.0},
    {6.0, -12.0, 6.0},
    {-3.0, 6.0, -3.0}
  };

  mpreal eps = 1E-14;

  Mat3x3 actual = adj(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix determinant                                                 #//
//###########################################################################//

TEST_CASE("Test matrix determinant for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {0.0, 5.0, 6.0},
    {0.0, 0.0, 9.0}
  };

  constexpr double expected = 45.0;

  constexpr double eps = 1E-14;

  const double actual = det(m);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix determinant for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {0.0, 5.0, 6.0},
    {0.0, 0.0, 9.0}
  };

  const mpreal expected = 45.0;

  const mpreal eps = 1E-14;

  const mpreal actual = det(m);

  REQUIRE(fabs(actual - expected) < eps);
}

//###########################################################################//
//# Test matrix transpose                                                   #//
//###########################################################################//

TEST_CASE("Test matrix transpose for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 expected = {
    {1.0, 4.0, 7.0},
    {2.0, 5.0, 8.0},
    {3.0, 6.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = tr(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test matrix transpose for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  Mat3x3 expected = {
    {1.0, 4.0, 7.0},
    {2.0, 5.0, 8.0},
    {3.0, 6.0, 9.0}
  };

  mpreal eps = 1E-14;

  Mat3x3 actual = tr(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test matrix-matrix Frobenius multiplication                             #//
//###########################################################################//

TEST_CASE("Test matrix-matrix Frobenius product for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  constexpr double expected =
      1.0 * 10.0 + 2.0 * 11.0 + 3.0 * 12.0 +
      4.0 * 13.0 + 5.0 * 14.0 + 6.0 * 15.0 +
      7.0 * 16.0 + 8.0 * 17.0 + 9.0 * 18.0; // 690.0

  constexpr double eps = 1E-14;

  const double actual = dot(m0, m1);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix-matrix Frobenius product for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Mat3x3 m1 = {
    {10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0},
    {16.0, 17.0, 18.0}
  };

  constexpr double expected =
      1.0 * 10.0 + 2.0 * 11.0 + 3.0 * 12.0 +
      4.0 * 13.0 + 5.0 * 14.0 + 6.0 * 15.0 +
      7.0 * 16.0 + 8.0 * 17.0 + 9.0 * 18.0; // 690.0

  constexpr double eps = 1E-14;

  const double actual = dot(m0, m1);

  REQUIRE(fabs(actual - expected) < eps);
}

//###########################################################################//
//# Test matrix Frobenius norm                                              #//
//###########################################################################//

TEST_CASE("Test matrix Frobenius norm for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const double expected = sqrt(
    1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0 +
    4.0 * 4.0 + 5.0 * 5.0 + 6.0 * 6.0 +
    7.0 * 7.0 + 8.0 * 8.0 + 9.0 * 9.0
  ); // 16.881943016134134

  constexpr double eps = 1E-14;

  const double actual = norm(m0);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix Frobenius norm for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m0 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const auto expected = mpfr::sqrt(
    1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0 +
    4.0 * 4.0 + 5.0 * 5.0 + 6.0 * 6.0 +
    7.0 * 7.0 + 8.0 * 8.0 + 9.0 * 9.0
  ); // 16.881943016134134

  const mpreal eps = 1E-14;

  const mpreal actual = norm(m0);

  REQUIRE(fabs(actual - expected) < eps);
}

//###########################################################################//
//# Test matrix diagonal                                                    #//
//###########################################################################//

TEST_CASE("Test matrix diagonal for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;
  using Vec3 = Vector3D<double>;

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 expected = {1.0, 5.0, 9.0};

  constexpr double eps = 1E-14;

  const Vec3 actual = diag(m);

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

TEST_CASE("Test matrix diagonal for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;
  using Vec3 = Vector3D<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const Vec3 expected = {1.0, 5.0, 9.0};

  constexpr double eps = 1E-14;

  const Vec3 actual = diag(m);

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
  REQUIRE(fabs(actual.z() - expected.z()) < eps);
}

//###########################################################################//
//# Test matrix trace                                                       #//
//###########################################################################//

TEST_CASE("Test matrix trace for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  constexpr double expected = 15.0;

  constexpr double eps = 1E-14;

  const double actual = trace(m);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix trace for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat3x3 m = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  const mpreal expected = 15.0;

  const mpreal eps = 1E-14;

  const mpreal actual = trace(m);

  REQUIRE(fabs(actual - expected) < eps);
}

//###########################################################################//
//# Test column matrix construction                                         #//
//###########################################################################//

TEST_CASE("Test column matrix for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;
  using Vec3 = Vector3D<double>;

  Vec3 v1 = {1.0, 2.0, 3.0};
  Vec3 v2 = {4.0, 5.0, 6.0};
  Vec3 v3 = {7.0, 8.0, 9.0};

  Mat3x3 expected = {
    {1.0, 4.0, 7.0},
    {2.0, 5.0, 8.0},
    {3.0, 6.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = column_matrix(v1, v2, v3);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test column matrix for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;
  using Vec3 = Vector3D<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Vec3 v1 = {1.0, 2.0, 3.0};
  Vec3 v2 = {4.0, 5.0, 6.0};
  Vec3 v3 = {7.0, 8.0, 9.0};

  Mat3x3 expected = {
    {1.0, 4.0, 7.0},
    {2.0, 5.0, 8.0},
    {3.0, 6.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = column_matrix(v1, v2, v3);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps);
}

//###########################################################################//
//# Test row matrix construction                                            #//
//###########################################################################//

TEST_CASE("Test row matrix for 'double' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;

  using Mat3x3 = Matrix3x3<double>;
  using Vec3 = Vector3D<double>;

  Vec3 v1 = {1.0, 2.0, 3.0};
  Vec3 v2 = {4.0, 5.0, 6.0};
  Vec3 v3 = {7.0, 8.0, 9.0};

  Mat3x3 expected = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = row_matrix(v1, v2, v3);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("Test row matrix for 'multiprecision' type.", "Matrix3x3") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat3x3 = Matrix3x3<mpreal>;
  using Vec3 = Vector3D<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Vec3 v1 = {1.0, 2.0, 3.0};
  Vec3 v2 = {4.0, 5.0, 6.0};
  Vec3 v3 = {7.0, 8.0, 9.0};

  Mat3x3 expected = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double eps = 1E-14;

  Mat3x3 actual = row_matrix(v1, v2, v3);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps);
}
