#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <mpreal.h>

#include "linalg_vector.hpp"

TEST_CASE("Test vector addition for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B, C;
  A(0) = 2;
  A(1) = 2;
  B(0) = 5;
  B(1) = 10;
  C = A + B;
  REQUIRE(abs(C(0) - 7) < eps);
  REQUIRE(abs(C(1) - 12) < eps);
}

TEST_CASE("Test vector difference for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B, C;
  A(0) = 4;
  A(1) = 7;
  B(0) = 4;
  B(1) = 3;
  C = A - B;
  REQUIRE(abs(C(0) - 0) < eps);
  REQUIRE(abs(C(1) - 4) < eps);
}

TEST_CASE("Test vector-scalar product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 3;
  A(0) = 10;
  A(1) = 3;
  B = A * alpha;
  REQUIRE(abs(B(0) - 30) < eps);
  REQUIRE(abs(B(1) - 9) < eps);
}

TEST_CASE("Test scalar-vector product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 10;
  A(0) = 7;
  A(1) = 4;
  B = alpha * A;
  REQUIRE(abs(B(0) - 70) < eps);
  REQUIRE(abs(B(1) - 40) < eps);
}

TEST_CASE("Test vector-scalar division for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B;
  mpfr::mpreal alpha = 8;
  A(0) = 5;
  A(1) = 1;
  B = A / alpha;
  REQUIRE(abs(B(0) - 0.625000000000000) < eps);
  REQUIRE(abs(B(1) - 0.125000000000000) < eps);
}

TEST_CASE("Test vector dot product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> u, v;
  u(0) = 1;
  u(1) = 2;
  v(0) = 9;
  v(1) = 7;
  mpfr::mpreal w = dot(u, v);
  REQUIRE(abs(w - 23.0000000000000) < eps);
}

TEST_CASE("Test vector cross product for 'mpfr::mpreal'", "Vector") {
  mpfr::mpreal eps(1E-7);
  Vector<mpfr::mpreal, 2> A, B, C;
  Vector<mpfr::mpreal, 2> u0;
  u0(0) = 7;
  u0(1) = 5;
  Vector<mpfr::mpreal, 2> result = cross(u0);
  REQUIRE(abs(result(0) - -5) < eps);
  REQUIRE(abs(result(1) - 7) < eps);
}

TEST_CASE("Test vector addition for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B, C;
  A(0) = 1;
  A(1) = 8;
  B(0) = 5;
  B(1) = 3;
  C = A + B;
  REQUIRE(abs(C(0) - 6) < eps);
  REQUIRE(abs(C(1) - 11) < eps);
}

TEST_CASE("Test vector difference for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B, C;
  A(0) = 6;
  A(1) = 4;
  B(0) = 7;
  B(1) = 3;
  C = A - B;
  REQUIRE(abs(C(0) - -1) < eps);
  REQUIRE(abs(C(1) - 1) < eps);
}

TEST_CASE("Test vector-scalar product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 10;
  A(0) = 4;
  A(1) = 8;
  B = A * alpha;
  REQUIRE(abs(B(0) - 40) < eps);
  REQUIRE(abs(B(1) - 80) < eps);
}

TEST_CASE("Test scalar-vector product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 1;
  A(0) = 4;
  A(1) = 10;
  B = alpha * A;
  REQUIRE(abs(B(0) - 4) < eps);
  REQUIRE(abs(B(1) - 10) < eps);
}

TEST_CASE("Test vector-scalar division for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B;
  double alpha = 7;
  A(0) = 3;
  A(1) = 7;
  B = A / alpha;
  REQUIRE(abs(B(0) - 0.428571428571429) < eps);
  REQUIRE(abs(B(1) - 1.00000000000000) < eps);
}

TEST_CASE("Test vector dot product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> u, v;
  u(0) = 5;
  u(1) = 10;
  v(0) = 5;
  v(1) = 8;
  double w = dot(u, v);
  REQUIRE(abs(w - 105.000000000000) < eps);
}

TEST_CASE("Test vector cross product for 'double'", "Vector") {
  double eps(1E-7);
  Vector<double, 2> A, B, C;
  Vector<double, 2> u0;
  u0(0) = 7;
  u0(1) = 7;
  Vector<double, 2> result = cross(u0);
  REQUIRE(abs(result(0) - -7) < eps);
  REQUIRE(abs(result(1) - 7) < eps);
}
