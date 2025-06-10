#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <mpreal.h>

#include "linalg_vector.hpp"

TEST_CASE("Test list initializer list 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u = {10, 5};
  REQUIRE(abs(u(0) - 10) < eps);
  REQUIRE(abs(u(1) - 5) < eps);
}

TEST_CASE("Test vector addition for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v, w;
  u(0) = 9;
  u(1) = 2;
  v(0) = 2;
  v(1) = 7;
  w = u + v;
  REQUIRE(abs(w(0) - 11) < eps);
  REQUIRE(abs(w(1) - 9) < eps);
}

TEST_CASE("Test vector difference for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v, w;
  u(0) = 4;
  u(1) = 6;
  v(0) = 7;
  v(1) = 5;
  w = u -v;
  REQUIRE(abs(w(0) - -3) < eps);
  REQUIRE(abs(w(1) - 1) < eps);
}

TEST_CASE("Test vector-scalar product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  mpfr::mpreal alpha = 3;
  u(0) = 6;
  u(1) = 3;
  v = u * alpha;
  REQUIRE(abs(v(0) - 18) < eps);
  REQUIRE(abs(v(1) - 9) < eps);
}

TEST_CASE("Test scalar-vector product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  mpfr::mpreal alpha = 8;
  u(0) = 3;
  u(1) = 7;
  v = alpha * u;
  REQUIRE(abs(v(0) - 24) < eps);
  REQUIRE(abs(v(1) - 56) < eps);
}

TEST_CASE("Test vector-scalar division for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  mpfr::mpreal alpha = 1;
  u(0) = 4;
  u(1) = 7;
  v = u / alpha;
  REQUIRE(abs(v(0) - 4.00000000000000) < eps);
  REQUIRE(abs(v(1) - 7.00000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace sum for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  u(0) = 6;
  v(0) = 8;
  u(1) = 4;
  v(1) = 4;
  u += v;
  REQUIRE(abs(u(0) - 14.0000000000000) < eps);
  REQUIRE(abs(u(1) - 8.00000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace difference for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  u(0) = 1;
  v(0) = 1;
  u(1) = 6;
  v(1) = 4;
  u -= v;
  REQUIRE(abs(u(0) - 0) < eps);
  REQUIRE(abs(u(1) - 2.00000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u;
  u(0) = 2;
  u(1) = 9;
  mpfr::mpreal alpha = 6;
  u *= alpha;
  REQUIRE(abs(u(0) - 12.0000000000000) < eps);
  REQUIRE(abs(u(1) - 54.0000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace division for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u;
  u(0) = 1;
  u(1) = 1;
  mpfr::mpreal alpha = 2;
  u /= alpha;
  REQUIRE(abs(u(0) - 0.500000000000000) < eps);
  REQUIRE(abs(u(1) - 0.500000000000000) < eps);
}

TEST_CASE("Test vector dot product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  u(0) = 3;
  u(1) = 10;
  v(0) = 8;
  v(1) = 6;
  mpfr::mpreal w = dot(u, v);
  REQUIRE(abs(w - 84.0000000000000) < eps);
}

TEST_CASE("Test vector cross product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u0;
  u0(0) = 10;
  u0(1) = 6;
  Vector<mpfr::mpreal, 2> result = cross(u0);
  REQUIRE(abs(result(0) - -6) < eps);
  REQUIRE(abs(result(1) - 10) < eps);
}

TEST_CASE("Test vector norm 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u;
  u(0) = 5;
  u(1) = 4;
  mpfr::mpreal w = norm(u);
  REQUIRE(abs(w - 6.40312423743285) < eps);
}

TEST_CASE("Test vector rnorm 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-12);
  Vector<mpfr::mpreal, 2, 2> u;
  u(0) = 5;
  u(1) = 8;
  mpfr::mpreal w = rnorm(u);
  REQUIRE(abs(w - 9.43398643204451) < eps);
}

TEST_CASE("Test vector normalize 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u;
  u(0) = 7;
  u(1) = 6;
  Vector v = normalize(u);
  REQUIRE(abs(v(0) - 0.759256602365297) < eps);
  REQUIRE(abs(v(1) - 0.650791373455968) < eps);
}

TEST_CASE("Test vector rnormalize 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2, 2> u;
  u(0) = 7;
  u(1) = 4;
  Vector v = rnormalize(u);
  REQUIRE(abs(v(0) - 0.868242474245890) < eps);
  REQUIRE(abs(v(1) - 0.496138556711937) < eps);
}

TEST_CASE("Test list initializer list 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u = {7, 1};
  REQUIRE(abs(u(0) - 7) < eps);
  REQUIRE(abs(u(1) - 1) < eps);
}

TEST_CASE("Test vector addition for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v, w;
  u(0) = 9;
  u(1) = 9;
  v(0) = 6;
  v(1) = 7;
  w = u + v;
  REQUIRE(abs(w(0) - 15) < eps);
  REQUIRE(abs(w(1) - 16) < eps);
}

TEST_CASE("Test vector difference for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v, w;
  u(0) = 5;
  u(1) = 1;
  v(0) = 6;
  v(1) = 7;
  w = u -v;
  REQUIRE(abs(w(0) - -1) < eps);
  REQUIRE(abs(w(1) - -6) < eps);
}

TEST_CASE("Test vector-scalar product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  double alpha = 6;
  u(0) = 10;
  u(1) = 1;
  v = u * alpha;
  REQUIRE(abs(v(0) - 60) < eps);
  REQUIRE(abs(v(1) - 6) < eps);
}

TEST_CASE("Test scalar-vector product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  double alpha = 7;
  u(0) = 7;
  u(1) = 3;
  v = alpha * u;
  REQUIRE(abs(v(0) - 49) < eps);
  REQUIRE(abs(v(1) - 21) < eps);
}

TEST_CASE("Test vector-scalar division for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  double alpha = 8;
  u(0) = 2;
  u(1) = 5;
  v = u / alpha;
  REQUIRE(abs(v(0) - 0.250000000000000) < eps);
  REQUIRE(abs(v(1) - 0.625000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace sum for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  u(0) = 7;
  v(0) = 2;
  u(1) = 10;
  v(1) = 5;
  u += v;
  REQUIRE(abs(u(0) - 9.00000000000000) < eps);
  REQUIRE(abs(u(1) - 15.0000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace difference for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  u(0) = 5;
  v(0) = 7;
  u(1) = 7;
  v(1) = 9;
  u -= v;
  REQUIRE(abs(u(0) - -2.00000000000000) < eps);
  REQUIRE(abs(u(1) - -2.00000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u;
  u(0) = 1;
  u(1) = 4;
  double alpha = 4;
  u *= alpha;
  REQUIRE(abs(u(0) - 4.00000000000000) < eps);
  REQUIRE(abs(u(1) - 16.0000000000000) < eps);
}

TEST_CASE("Test vector-scalar inplace division for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u;
  u(0) = 6;
  u(1) = 4;
  double alpha = 10;
  u /= alpha;
  REQUIRE(abs(u(0) - 0.600000000000000) < eps);
  REQUIRE(abs(u(1) - 0.400000000000000) < eps);
}

TEST_CASE("Test vector dot product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  u(0) = 9;
  u(1) = 9;
  v(0) = 1;
  v(1) = 1;
  double w = dot(u, v);
  REQUIRE(abs(w - 18.0000000000000) < eps);
}

TEST_CASE("Test vector cross product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u0;
  u0(0) = 8;
  u0(1) = 8;
  Vector<double, 2> result = cross(u0);
  REQUIRE(abs(result(0) - -8) < eps);
  REQUIRE(abs(result(1) - 8) < eps);
}

TEST_CASE("Test vector norm 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u;
  u(0) = 10;
  u(1) = 1;
  double w = norm(u);
  REQUIRE(abs(w - 10.0498756211209) < eps);
}

TEST_CASE("Test vector rnorm 'double'", "Vector") {
  double eps(1E-12);
  Vector<double, 2, 2> u;
  u(0) = 9;
  u(1) = 9;
  double w = rnorm(u);
  REQUIRE(abs(w - 12.7279259897283) < eps);
}

TEST_CASE("Test vector normalize 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u;
  u(0) = 7;
  u(1) = 2;
  Vector v = normalize(u);
  REQUIRE(abs(v(0) - 0.961523947640823) < eps);
  REQUIRE(abs(v(1) - 0.274721127897378) < eps);
}

TEST_CASE("Test vector rnormalize 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2, 2> u;
  u(0) = 3;
  u(1) = 5;
  Vector v = rnormalize(u);
  REQUIRE(abs(v(0) - 0.514494998817790) < eps);
  REQUIRE(abs(v(1) - 0.857491664696317) < eps);
}
