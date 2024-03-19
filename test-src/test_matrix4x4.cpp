//
// Created by Lesleis Nagy on 19/03/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <matrix4x4.hpp>
#include "mpreal.h"

//###########################################################################//
//# Test addition                                                           #//
//###########################################################################//

TEST_CASE("Test matrix addition for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Mat4x4 m1 = {
            {17.0, 18.0, 19.0, 20.0},
            {21.0, 22.0, 23.0, 24.0},
            {25.0, 26.0, 27.0, 28.0},
            {29.0, 30.0, 31.0, 32.0}};

    Mat4x4 expected = {
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0},
            {34.0, 36.0, 38.0, 40.0},
            {42.0, 44.0, 46.0, 48.0}};

    double eps = 1E-14;

    Mat4x4 actual = m0 + m1;

    REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps );
    REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps );
    REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps );
    REQUIRE(fabs(actual(0, 3) - expected(0, 3)) < eps );

    REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps );
    REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps );
    REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps );
    REQUIRE(fabs(actual(1, 3) - expected(1, 3)) < eps );

    REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps );
    REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps );
    REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps );
    REQUIRE(fabs(actual(2, 3) - expected(2, 3)) < eps );

    REQUIRE(fabs(actual(3, 0) - expected(3, 0)) < eps );
    REQUIRE(fabs(actual(3, 1) - expected(3, 1)) < eps );
    REQUIRE(fabs(actual(3, 2) - expected(3, 2)) < eps );
    REQUIRE(fabs(actual(3, 3) - expected(3, 3)) < eps );

}

TEST_CASE("Test matrix addition for 'multiprecision' type.", "Matrix3x3") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Mat4x4 m1 = {
            {17.0, 18.0, 19.0, 20.0},
            {21.0, 22.0, 23.0, 24.0},
            {25.0, 26.0, 27.0, 28.0},
            {29.0, 30.0, 31.0, 32.0}};

    Mat4x4 expected = {
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0},
            {34.0, 36.0, 38.0, 40.0},
            {42.0, 44.0, 46.0, 48.0}};

    double eps = 1E-14;

    Mat4x4 actual = m0 + m1;

    REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps );
    REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps );
    REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps );
    REQUIRE(fabs(actual(0, 3) - expected(0, 3)) < eps );

    REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps );
    REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps );
    REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps );
    REQUIRE(fabs(actual(1, 3) - expected(1, 3)) < eps );

    REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps );
    REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps );
    REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps );
    REQUIRE(fabs(actual(2, 3) - expected(2, 3)) < eps );

    REQUIRE(fabs(actual(3, 0) - expected(3, 0)) < eps );
    REQUIRE(fabs(actual(3, 1) - expected(3, 1)) < eps );
    REQUIRE(fabs(actual(3, 2) - expected(3, 2)) < eps );
    REQUIRE(fabs(actual(3, 3) - expected(3, 3)) < eps );

}
