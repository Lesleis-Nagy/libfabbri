//
// Created by Lesleis Nagy on 19/03/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <amiga/matrix2x2.hpp>
#include "mpreal.h"

//###############################################################################################//
//# Test addition                                                                               #//
//###############################################################################################//

TEST_CASE("Test matrix addition for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {11.0, 13.0},
    {17.0, 19.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 + m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix addition for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {11.0, 13.0},
    {17.0, 19.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 + m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test subtraction                                                                            #//
//###############################################################################################//

TEST_CASE("Test matrix subtraction for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {9.0, 9.0},
    {9.0, 9.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m1 - m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix subtraction for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {9.0, 9.0},
    {9.0, 9.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m1 - m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test scalar-matrix multiplication                                                           #//
//###############################################################################################//

TEST_CASE("Test scalar-matrix multiplication for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  constexpr double lambda = 2.0;

  const Mat2x2 expected = {
    {2.0, 4.0},
    {8.0, 10.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = lambda * m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test scalar-matrix multiplication for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const mpreal lambda = 2.0;

  const Mat2x2 expected = {
    {2.0, 4.0},
    {8.0, 10.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = lambda * m0;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix-scalar multiplication                                                           #//
//###############################################################################################//

TEST_CASE("Test matrix-scalar multiplication for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  constexpr double lambda = 2.0;

  const Mat2x2 expected = {
    {2.0, 4.0},
    {8.0, 10.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 * lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix-scalar multiplication for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const mpreal lambda = 2.0;

  const Mat2x2 expected = {
    {2.0, 4.0},
    {8.0, 10.0},
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 * lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix-scalar division                                                                 #//
//###############################################################################################//

TEST_CASE("Test matrix-scalar division for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  constexpr double lambda = 2.0;

  const Mat2x2 expected = {
    {0.5, 1.0},
    {2.0, 2.5}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 / lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix-scalar division for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const mpreal lambda = 2.0;

  const Mat2x2 expected = {
    {0.5, 1.0},
    {2.0, 2.5}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 / lambda;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix-vector multiplication                                                           #//
//###############################################################################################//

TEST_CASE("Test matrix-vector multiplication for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Vec2 = Vector2D<double>;
  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 v = {1.0, 2.0};

  const Vec2 expected = {
    1.0 * 1.0 + 2.0 * 2.0,
    4.0 * 1.0 + 5.0 * 2.0,
  };

  constexpr double eps = 1E-14;

  const Vec2 actual = m0 * v;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test matrix-vector multiplication for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Vec2 = Vector2D<double>;
  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 v = {1.0, 2.0};

  const Vec2 expected = {
    1.0 * 1.0 + 2.0 * 2.0,
    4.0 * 1.0 + 5.0 * 2.0
  };

  constexpr double eps = 1E-14;

  const Vec2 actual = m0 * v;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

//###############################################################################################//
//# Test vector-matrix multiplication                                                           #//
//###############################################################################################//

TEST_CASE("Test vector-matrix multiplication for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Vec2 = Vector2D<double>;
  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 v = {1.0, 2.0};

  const Vec2 expected = {9.0, 12.0};

  constexpr double eps = 1E-14;

  const Vec2 actual = v * m0;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test vector-matrix multiplication for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Vec2 = Vector2D<double>;
  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 v = {1.0, 2.0};

  const Vec2 expected = {9.0, 12.0};

  const mpreal eps = 1E-14;

  const Vec2 actual = v * m0;

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

//###############################################################################################//
//# Test matrix-matrix multiplication                                                           #//
//###############################################################################################//

TEST_CASE("Test matrix-matrix multiplication for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {36.0, 39.0},
    {105.0, 114.0},
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = m0 * m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix-matrix multiplication for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  const Mat2x2 expected = {
    {36.0, 39.0},
    {105.0, 114.0},
  };

  const mpreal eps = 1E-14;

  const Mat2x2 actual = m0 * m1;

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix adjugate                                                                        #//
//###############################################################################################//

TEST_CASE("Test matrix adjugate for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 expected = {
    {5.0, -2.0},
    {-4.0, 1.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = adj(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix adjugate for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0},
  };

  const Mat2x2 expected = {
    {5.0, -2.0},
    {-4.0, 1.0}
  };

  const mpreal eps = 1E-14;

  const Mat2x2 actual = adj(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix determinant                                                                     #//
//###############################################################################################//

TEST_CASE("Test matrix determinant for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m = {
    {1.0, 2.0},
    {0.0, 5.0}
  };

  constexpr double expected = 5.0;

  constexpr double eps = 1E-14;

  const double actual = det(m);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix determinant for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m = {
    {1.0, 2.0},
    {0.0, 5.0}
  };

  const mpreal expected = 5.0;

  const mpreal eps = 1E-14;

  const mpreal actual = det(m);

  REQUIRE(fabs(actual - expected) < eps);
}

//###############################################################################################//
//# Test matrix transpose                                                                       #//
//###############################################################################################//

TEST_CASE("Test matrix transpose for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 expected = {
    {1.0, 4.0},
    {2.0, 5.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = tr(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test matrix transpose for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 expected = {
    {1.0, 4.0},
    {2.0, 5.0}
  };

  const mpreal eps = 1E-14;

  const Mat2x2 actual = tr(m);

  REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test matrix-matrix Frobenius multiplication                                                 #//
//###############################################################################################//

TEST_CASE("Test matrix-matrix Frobenius product for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  constexpr double expected = 1.0 * 10.0 + 2.0 * 11.0 + 4.0 * 13.0 + 5.0 * 14.0;

  constexpr double eps = 1E-14;

  const double actual = dot(m0, m1);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix-matrix Frobenius product for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<double>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Mat2x2 m1 = {
    {10.0, 11.0},
    {13.0, 14.0}
  };

  constexpr double expected = 1.0 * 10.0 + 2.0 * 11.0 + 4.0 * 13.0 + 5.0 * 14.0;

  constexpr double eps = 1E-14;

  const double actual = dot(m0, m1);

  REQUIRE(fabs(actual - expected) < eps);
}

//###############################################################################################//
//# Test matrix Frobenius norm                                                                  #//
//###############################################################################################//

TEST_CASE("Test matrix Frobenius norm for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const double expected = sqrt(1.0 * 1.0 + 2.0 * 2.0 + 4.0 * 4.0 + 5.0 * 5.0);

  constexpr double eps = 1E-14;

  const double actual = norm(m0);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix Frobenius norm for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;

  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m0 = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const auto expected = mpfr::sqrt(1.0 * 1.0 + 2.0 * 2.0 + 4.0 * 4.0 + 5.0 * 5.0);

  const mpreal eps = 1E-14;

  const mpreal actual = norm(m0);

  REQUIRE(fabs(actual - expected) < eps);
}

//###############################################################################################//
//# Test matrix diagonal                                                                        #//
//###############################################################################################//

TEST_CASE("Test matrix diagonal for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;
  using Vec2 = Vector2D<double>;

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 expected = {1.0, 5.0};

  constexpr double eps = 1E-14;

  const Vec2 actual = diag(m);

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test matrix diagonal for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;
  using Vec2 = Vector2D<mpreal>;

  constexpr int digits = 50;

  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const Vec2 expected = {1.0, 5.0};

  constexpr double eps = 1E-14;

  const Vec2 actual = diag(m);

  REQUIRE(fabs(actual.x() - expected.x()) < eps);
  REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

//###############################################################################################//
//# Test matrix trace                                                                           #//
//###############################################################################################//

TEST_CASE("Test matrix trace for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  constexpr double expected = 6.0;

  constexpr double eps = 1E-14;

  const double actual = trace(m);

  REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test matrix trace for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Mat2x2 m = {
    {1.0, 2.0},
    {4.0, 5.0}
  };

  const mpreal expected = 6.0;

  const mpreal eps = 1E-14;

  const mpreal actual = trace(m);

  REQUIRE(fabs(actual - expected) < eps);
}

//###############################################################################################//
//# Test column matrix construction                                                             #//
//###############################################################################################//

TEST_CASE("Test column matrix for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;
  using Vec2 = Vector2D<double>;

  const Vec2 v1 = {1.0, 3.0};
  const Vec2 v2 = {2.0, 4.0};

  const Mat2x2 expected = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = column_matrix(v1, v2);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test column matrix for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;
  using Vec2 = Vector2D<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Vec2 v1 = {1.0, 3.0};
  const Vec2 v2 = {2.0, 4.0};

  const Mat2x2 expected = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = column_matrix(v1, v2);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
}

//###############################################################################################//
//# Test row matrix construction                                                                #//
//###############################################################################################//

TEST_CASE("Test row matrix for 'double' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;

  using Mat2x2 = Matrix2x2<double>;
  using Vec2 = Vector2D<double>;

  const Vec2 v1 = {1.0, 3.0};
  const Vec2 v2 = {2.0, 4.0};

  const Mat2x2 expected = {
    {1.0, 3.0},
    {2.0, 4.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = row_matrix(v1, v2);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
}

TEST_CASE("Test row matrix for 'multiprecision' type.", "Matrix2x2") {
  using namespace amiga;
  using std::string;
  using mpfr::mpreal;

  using Mat2x2 = Matrix2x2<mpreal>;
  using Vec2 = Vector2D<mpreal>;

  constexpr int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  const Vec2 v1 = {1.0, 3.0};
  const Vec2 v2 = {2.0, 4.0};

  const Mat2x2 expected = {
    {1.0, 3.0},
    {2.0, 4.0}
  };

  constexpr double eps = 1E-14;

  const Mat2x2 actual = row_matrix(v1, v2);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps);

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps);
}
