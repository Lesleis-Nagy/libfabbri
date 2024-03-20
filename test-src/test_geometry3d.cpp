//
// Created by Lesleis Nagy on 20/03/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <geometry3d.hpp>
#include "mpreal.h"

//###########################################################################//
//# Test geometry edge length                                               #//
//###########################################################################//

TEST_CASE("Test edge_length() function for 'double' type.",
          "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    double eps = 1E-14;
    double expected = sqrt(27.0);
    double actual_d1 = edge_length(u, v);
    double actual_d2 = edge_length(v, u);

    REQUIRE(fabs(actual_d1 - expected) < eps);
    REQUIRE(fabs(actual_d2 - expected) < eps);

}

TEST_CASE("Test edge_length() function for 'multiprecision' type.",
          "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    mpreal eps = 1E-40;
    mpreal expected = mpfr::sqrt(27.0);
    mpreal actual_d1 = edge_length(u, v);
    mpreal actual_d2 = edge_length(v, u);

    REQUIRE(abs(actual_d1 - expected) < eps);
    REQUIRE(abs(actual_d2 - expected) < eps);

}

//###########################################################################//
//# Test geometry edge center                                               #//
//###########################################################################//

TEST_CASE("Test edge_center() function for 'double' type.",
          "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {5.0 / 2.0, 7.0 / 2.0, 9.0 / 2.0};

    Vec3D actual = edge_center(r1, r2);

    double eps = 1E-14;

    REQUIRE(fabs(expected.x() - actual.x()) < eps);
    REQUIRE(fabs(expected.y() - actual.y()) < eps);
    REQUIRE(fabs(expected.z() - actual.z()) < eps);

}

TEST_CASE("Test edge_center() function for 'multiprecision' type.",
          "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {mpreal(5.0) / mpreal(2.0),
                      mpreal(7.0) / mpreal(2.0),
                      mpreal(9.0) / mpreal(2.0)};
    Vec3D actual = edge_center(r1, r2);

    mpreal eps = 1E-40;

    REQUIRE(abs(expected.x() - actual.x()) < eps);
    REQUIRE(abs(expected.y() - actual.y()) < eps);
    REQUIRE(abs(expected.z() - actual.z()) < eps);

}

//###########################################################################//
//# Test geometry edge orientation                                          #//
//###########################################################################//

TEST_CASE("Test edge_orientation() function for 'double' type.",
          "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0 / sqrt(27.0),
                      3.0 / sqrt(27.0),
                      3.0 / sqrt(27.0)};

    Vec3D actual = edge_orientation(r1, r2);

    double eps = 1E-14;

    REQUIRE(fabs(expected.x() - actual.x()) < eps);
    REQUIRE(fabs(expected.y() - actual.y()) < eps);
    REQUIRE(fabs(expected.z() - actual.z()) < eps);

}

TEST_CASE("Test edge_orientation() function for 'multiprecision' type.",
          "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0 / mpfr::sqrt(27.0),
                      3.0 / mpfr::sqrt(27.0),
                      3.0 / mpfr::sqrt(27.0)};

    Vec3D actual = edge_orientation(r1, r2);

    mpreal eps = 1E-40;

    REQUIRE(abs(expected.x() - actual.x()) < eps);
    REQUIRE(abs(expected.y() - actual.y()) < eps);
    REQUIRE(abs(expected.z() - actual.z()) < eps);

}

//###########################################################################//
//# Test geometry triangle normal                                           #//
//###########################################################################//

TEST_CASE("Test triangle_normal() function for 'double' type.",
          "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    Vec3D expected = {1.0 / sqrt(3),
                      1.0 / sqrt(3.0),
                      1.0 / sqrt(3.0)};

    Vec3D actual = triangle_normal(r1, r2, r3);

    double eps = 1E-14;

    REQUIRE(fabs(expected.x() - actual.x()) < eps);
    REQUIRE(fabs(expected.y() - actual.y()) < eps);
    REQUIRE(fabs(expected.z() - actual.z()) < eps);

}

TEST_CASE("Test triangle_normal() function for 'multiprecision' type.",
          "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    mpreal eps = 1E-40;
    Vec3D expected = {1.0 / mpfr::sqrt(3.0),
                      1.0 / mpfr::sqrt(3.0),
                      1.0 / mpfr::sqrt(3.0)};

    Vec3D actual = triangle_normal(r1, r2, r3);

    REQUIRE(abs(expected.x() - actual.x()) < eps);
    REQUIRE(abs(expected.y() - actual.y()) < eps);
    REQUIRE(abs(expected.z() - actual.z()) < eps);

}

//###########################################################################//
//# Test geometry triangle center                                           #//
//###########################################################################//

TEST_CASE("Test triangle_center() function for 'double' type.",
          "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    Vec3D expected = {1.0 / 3.0,
                      1.0 / 3.0,
                      1.0 / 3.0};

    Vec3D actual = triangle_center(r1, r2, r3);

    double eps = 1E-14;

    REQUIRE(fabs(expected.x() - actual.x()) < eps);
    REQUIRE(fabs(expected.y() - actual.y()) < eps);
    REQUIRE(fabs(expected.z() - actual.z()) < eps);

}

TEST_CASE("Test triangle_center() function for 'multiprecision' type.",
          "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    mpreal eps = 1E-40;
    Vec3D expected = {mpreal(1.0) / mpreal(3.0),
                      mpreal(1.0) / mpreal(3.0),
                      mpreal(1.0) / mpreal(3.0)};

    Vec3D actual = triangle_center(r1, r2, r3);

    REQUIRE(abs(expected.x() - actual.x()) < eps);
    REQUIRE(abs(expected.y() - actual.y()) < eps);
    REQUIRE(abs(expected.z() - actual.z()) < eps);

}
