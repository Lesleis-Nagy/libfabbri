#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <mpreal.h>

#include "linalg.hpp"

TEST_CASE("Test vector addition for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B, C;
  A(0) = 10;
  A(1) = 2;
  B(0) = 5;
  B(1) = 3;
  C = A + B;
  REQUIRE(abs(C(0) - 15) < eps);
  REQUIRE(abs(C(1) - 5) < eps);
}

TEST_CASE("Test vector difference for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B, C;
  A(0) = 6;
  A(1) = 7;
  B(0) = 5;
  B(1) = 9;
  C = A - B;
  REQUIRE(abs(C(0) - 1) < eps);
  REQUIRE(abs(C(1) - -2) < eps);
}

TEST_CASE("Test vector-scalar product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 2;
  A(0) = 1;
  A(1) = 2;
  B = A * alpha;
  REQUIRE(abs(B(0) - 2) < eps);
  REQUIRE(abs(B(1) - 4) < eps);
}

TEST_CASE("Test scalar-vector product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 6;
  A(0) = 3;
  A(1) = 1;
  B = alpha * A;
  REQUIRE(abs(B(0) - 18) < eps);
  REQUIRE(abs(B(1) - 6) < eps);
}

TEST_CASE("Test vector-scalar division for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 6;
  A(0) = 2;
  A(1) = 1;
  B = A / alpha;
  REQUIRE(abs(B(0) - 0.333333333333333) < eps);
  REQUIRE(abs(B(1) - 0.166666666666667) < eps);
}

TEST_CASE("Test vector dot product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  u(0) = 6;
  u(1) = 4;
  v(0) = 3;
  v(1) = 10;
  mpfr::mpreal w = dot(u, v);
  REQUIRE(abs(w - 58.0000000000000) < eps);
}

TEST_CASE("Test vector addition for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B, C;
  A(0) = 8;
  A(1) = 4;
  B(0) = 10;
  B(1) = 3;
  C = A + B;
  REQUIRE(abs(C(0) - 18) < eps);
  REQUIRE(abs(C(1) - 7) < eps);
}

TEST_CASE("Test vector difference for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B, C;
  A(0) = 7;
  A(1) = 8;
  B(0) = 9;
  B(1) = 9;
  C = A - B;
  REQUIRE(abs(C(0) - -2) < eps);
  REQUIRE(abs(C(1) - -1) < eps);
}

TEST_CASE("Test vector-scalar product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 4;
  A(0) = 8;
  A(1) = 2;
  B = A * alpha;
  REQUIRE(abs(B(0) - 32) < eps);
  REQUIRE(abs(B(1) - 8) < eps);
}

TEST_CASE("Test scalar-vector product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 8;
  A(0) = 5;
  A(1) = 8;
  B = alpha * A;
  REQUIRE(abs(B(0) - 40) < eps);
  REQUIRE(abs(B(1) - 64) < eps);
}

TEST_CASE("Test vector-scalar division for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 4;
  A(0) = 3;
  A(1) = 1;
  B = A / alpha;
  REQUIRE(abs(B(0) - 0.750000000000000) < eps);
  REQUIRE(abs(B(1) - 0.250000000000000) < eps);
}

TEST_CASE("Test vector dot product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  u(0) = 1;
  u(1) = 7;
  v(0) = 5;
  v(1) = 10;
  double w = dot(u, v);
  REQUIRE(abs(w - 75.0000000000000) < eps);
}
