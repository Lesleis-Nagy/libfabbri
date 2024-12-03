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

TEST_CASE("Test matrix addition for 'multiprecision' type.", "Matrix4x4") {

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

    mpreal eps = 1E-14;

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

//###########################################################################//
//# Test subtraction                                                        #//
//###########################################################################//

TEST_CASE("Test matrix subtraction for 'double' type.", "Matrix4x4") {

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
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0}};

    double eps = 1E-14;

    Mat4x4 actual = m1 - m0;

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

TEST_CASE("Test matrix subtraction for 'multiprecision' type.", "Matrix4x4") {

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
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0},
            {16.0, 16.0, 16.0, 16.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = m1 - m0;

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

//###########################################################################//
//# Test scalar-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test scalar-matrix multiplication for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    double lambda = 2.0;

    Mat4x4 expected = {
            { 2.0,  4.0,  6.0,  8.0},
            {10.0, 12.0, 14.0, 16.0},
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0}};

    double eps = 1E-14;

    Mat4x4 actual = lambda * m0;

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

TEST_CASE("Test scalar-matrix multiplication for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4= Matrix4x4<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    mpreal lambda = 2.0;

    Mat4x4 expected = {
            { 2.0,  4.0,  6.0,  8.0},
            {10.0, 12.0, 14.0, 16.0},
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = lambda * m0;

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

//###########################################################################//
//# Test matrix-scalar multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-scalar multiplication for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    double lambda = 2.0;

    Mat4x4 expected = {
            { 2.0,  4.0,  6.0,  8.0},
            {10.0, 12.0, 14.0, 16.0},
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0}};

    double eps = 1E-14;

    Mat4x4 actual = m0 * lambda;

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

TEST_CASE("Test matrix-scalar multiplication for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4= Matrix4x4<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    mpreal lambda = 2.0;

    Mat4x4 expected = {
            { 2.0,  4.0,  6.0,  8.0},
            {10.0, 12.0, 14.0, 16.0},
            {18.0, 20.0, 22.0, 24.0},
            {26.0, 28.0, 30.0, 32.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = m0 * lambda;

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

//###########################################################################//
//# Test matrix-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test matrix-scalar division for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    double lambda = 2.0;

    Mat4x4 expected = {
            { 0.5,  1.0,  1.5,  2.0},
            { 2.5,  3.0,  3.5,  4.0},
            { 4.5,  5.0,  5.5,  6.0},
            { 6.5,  7.0,  7.5,  8.0}};

    double eps = 1E-14;

    Mat4x4 actual = m0 / lambda;

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

TEST_CASE("Test matrix-scalar division for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4= Matrix4x4<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    mpreal lambda = 2.0;

    Mat4x4 expected = {
            { 0.5,  1.0,  1.5,  2.0},
            { 2.5,  3.0,  3.5,  4.0},
            { 4.5,  5.0,  5.5,  6.0},
            { 6.5,  7.0,  7.5,  8.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = m0 / lambda;

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

//###########################################################################//
//# Test matrix-vector multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-vector multiplication for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;
    using Vec4 = Vector4D<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 v = {17.0, 18.0, 19.0, 20.0};

    Vec4 expected = {190.0, 486.0, 782.0, 1078.0};

    double eps = 1E-14;

    Vec4 actual = m0 * v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test matrix-vector multiplication for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4= Matrix4x4<mpreal>;
    using Vec4 = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 v = {17.0, 18.0, 19.0, 20.0};

    Vec4 expected = {190.0, 486.0, 782.0, 1078.0};

    mpreal eps = 1E-14;

    Vec4 actual = m0 * v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test vector-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test vector-matrix multiplication for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;
    using Vec4 = Vector4D<double>;

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 v = {17.0, 18.0, 19.0, 20.0};

    Vec4 expected = {190.0, 486.0, 782.0, 1078.0};

    double eps = 1E-14;

    Vec4 actual = m0 * v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test vector-matrix multiplication for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4= Matrix4x4<mpreal>;
    using Vec4 = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m0 = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 v = {17.0, 18.0, 19.0, 20.0};

    Vec4 expected = {190.0, 486.0, 782.0, 1078.0};

    mpreal eps = 1E-14;

    Vec4 actual = m0 * v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test matrix-matrix multiplication                                       #//
//###########################################################################//

TEST_CASE("Test matrix-matrix multiplication for 'double' type.", "Matrix4x4") {

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
            { 250.0,  260.0,  270.0,  280.0},
            { 618.0,  644.0,  670.0,  696.0},
            { 986.0, 1028.0, 1070.0, 1112.0},
            {1354.0, 1412.0, 1470.0, 1528.0}};

    double eps = 1E-14;

    Mat4x4 actual = m0 * m1;

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

TEST_CASE("Test matrix-matrix multiplication for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<double>;

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
            { 250.0,  260.0,  270.0,  280.0},
            { 618.0,  644.0,  670.0,  696.0},
            { 986.0, 1028.0, 1070.0, 1112.0},
            {1354.0, 1412.0, 1470.0, 1528.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = m0 * m1;

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

//###########################################################################//
//# Test matrix adjugate                                                    #//
//###########################################################################//

TEST_CASE("Test matrix adjugate for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m = {
            {1.0, 2.0, 3.0, 4.0},
            {2.0, 2.0, 2.0, 2.0},
            {0.0, 1.0, 1.0, 0.0},
            {1.0, 0.0, 2.0, 4.0}};

    Mat4x4 expected = {
            { 4.0, -4.0,  0.0,  -2.0},
            {-6.0,  0.0,  6.0,   6.0},
            { 6.0,  0.0, -12.0, -6.0},
            {-4.0,  1.0,  6.0,   2.0}};

    double eps = 1E-14;

    Mat4x4 actual = adj(m);

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

TEST_CASE("Test matrix adjugate for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<double>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            {1.0, 2.0, 3.0, 4.0},
            {2.0, 2.0, 2.0, 2.0},
            {0.0, 1.0, 1.0, 0.0},
            {1.0, 0.0, 2.0, 4.0}};

    Mat4x4 expected = {
            { 4.0, -4.0,  0.0,  -2.0},
            {-6.0,  0.0,  6.0,   6.0},
            { 6.0,  0.0, -12.0, -6.0},
            {-4.0,  1.0,  6.0,   2.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = adj(m);

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

//###########################################################################//
//# Test matrix determinant                                                 #//
//###########################################################################//

TEST_CASE("Test matrix determinant for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m = {
            {1.0, 2.0, 3.0, 4.0},
            {0.0, 2.0, 2.0, 2.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 4.0}};

    double expected = 8.0;

    double eps = 1E-14;

    double actual = det(m);

    REQUIRE(fabs(actual - expected) < eps );

}

TEST_CASE("Test matrix determinant for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<double>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            {1.0, 2.0, 3.0, 4.0},
            {0.0, 2.0, 2.0, 2.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 4.0}};

    mpreal expected = 8.0;

    mpreal eps = 1E-14;

    mpreal actual = det(m);

    REQUIRE(fabs(actual - expected) < eps );

}

//###########################################################################//
//# Test matrix transpose                                                   #//
//###########################################################################//

TEST_CASE("Test matrix transpose for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Mat4x4 expected = {
            {1.0, 5.0,  9.0, 13.0},
            {2.0, 6.0, 10.0, 14.0},
            {3.0, 7.0, 11.0, 15.0},
            {4.0, 8.0, 12.0, 16.0}};

    double eps = 1E-14;

    Mat4x4 actual = tr(m);

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

TEST_CASE("Test matrix transpose for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<double>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Mat4x4 expected = {
            {1.0, 5.0,  9.0, 13.0},
            {2.0, 6.0, 10.0, 14.0},
            {3.0, 7.0, 11.0, 15.0},
            {4.0, 8.0, 12.0, 16.0}};

    mpreal eps = 1E-14;

    Mat4x4 actual = tr(m);

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

//###########################################################################//
//# Test matrix-matrix Frobenius multiplication                             #//
//###########################################################################//

TEST_CASE("Test matrix-matrix Frobenius product for 'double' type.", "Matrix4x4") {

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

    double expected = 3672.0;

    double eps = 1E-14;

    double actual = dot(m0, m1);

    REQUIRE(fabs(actual - expected) < eps);

}

TEST_CASE("Test matrix-matrix Frobenius product for 'multiprecision' type.", "Matrix4x4") {

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

    mpreal expected = 3672.0;

    mpreal eps = 1E-14;

    mpreal actual = dot(m0, m1);

    REQUIRE(fabs(actual - expected) < eps);

}

//###########################################################################//
//# Test matrix Frobenius norm                                              #//
//###########################################################################//

TEST_CASE("Test matrix Frobenius norm for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    double expected = sqrt(1496.0);

    double eps = 1E-14;

    double actual = norm(m);

    REQUIRE(fabs(actual - expected) < eps);

}

TEST_CASE("Test matrix Frobenius norm for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<mpreal>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    mpreal expected = sqrt(1496.0);

    mpreal eps = 1E-14;

    mpreal actual = norm(m);

    REQUIRE(fabs(actual - expected) < eps);

}

//###########################################################################//
//# Test matrix diagonal                                                    #//
//###########################################################################//

TEST_CASE("Test matrix diagonal for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;
    using Vec4 = Vector4D<double>;

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 expected = {1.0, 6.0, 11.0, 16.0};

    double eps = 1E-14;

    Vec4 actual = diag(m);

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test matrix diagonal for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<mpreal>;
    using Vec4 = Vector4D<mpreal>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    Vec4 expected = {1.0, 6.0, 11.0, 16.0};

    double eps = 1E-14;

    Vec4 actual = diag(m);

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );
    REQUIRE(fabs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test matrix trace                                                       #//
//###########################################################################//

TEST_CASE("Test matrix trace for 'double' type.", "Matrix4x4") {

    using std::string;
    using Mat4x4 = Matrix4x4<double>;

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    double expected = 34.0;

    double eps = 1E-14;

    double actual = trace(m);

    REQUIRE(fabs(actual - expected) < eps );

}

TEST_CASE("Test matrix trace for 'multiprecision' type.", "Matrix4x4") {

    using std::string;
    using mpfr::mpreal;

    using Mat4x4 = Matrix4x4<mpreal>;
    using Vec4 = Vector4D<mpreal>;

    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Mat4x4 m = {
            { 1.0,  2.0,  3.0,  4.0},
            { 5.0,  6.0,  7.0,  8.0},
            { 9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}};

    mpreal expected = 34.0;

    mpreal eps = 1E-14;

    mpreal actual = trace(m);

    REQUIRE(fabs(actual - expected) < eps );

}

//###########################################################################//
//# Test column matrix construction                                         #//
//###########################################################################//

TEST_CASE("Test column matrix for 'double' type.", "Matrix4x4") {
  using std::string;
  using Mat4x4 = Matrix4x4<double>;
  using Vec4 = Vector4D<double>;

  Vec4 v1 = { 1.0,  2.0,  3.0,  4.0};
  Vec4 v2 = { 5.0,  6.0,  7.0,  8.0};
  Vec4 v3 = { 9.0, 10.0, 11.0, 12.0};
  Vec4 v4 = {13.0, 14.0, 15.0, 16.0};

  Mat4x4 expected = {
      { 1.0, 5.0,  9.0, 13.0},
      { 2.0, 6.0, 10.0, 14.0},
      { 3.0, 7.0, 11.0, 15.0},
      { 4.0, 8.0, 12.0, 16.0}
  };

  double eps = 1E-14;

  Mat4x4 actual = column_matrix(v1, v2, v3, v4);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps );
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps );
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps );
  REQUIRE(abs(actual(0, 3) - expected(0, 3)) < eps );

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps );
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps );
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps );
  REQUIRE(abs(actual(1, 3) - expected(1, 3)) < eps );

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps );
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps );
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps );
  REQUIRE(abs(actual(2, 3) - expected(2, 3)) < eps );

  REQUIRE(abs(actual(3, 0) - expected(3, 0)) < eps );
  REQUIRE(abs(actual(3, 1) - expected(3, 1)) < eps );
  REQUIRE(abs(actual(3, 2) - expected(3, 2)) < eps );
  REQUIRE(abs(actual(3, 3) - expected(3, 3)) < eps );

}

TEST_CASE("Test column matrix for 'multiprecision' type.", "Matrix4x4") {

  using std::string;
  using mpfr::mpreal;

  using Mat4x4 = Matrix4x4<mpreal>;
  using Vec4 = Vector4D<mpreal>;

  const int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Vec4 v1 = { 1.0,  2.0,  3.0,  4.0};
  Vec4 v2 = { 5.0,  6.0,  7.0,  8.0};
  Vec4 v3 = { 9.0, 10.0, 11.0, 12.0};
  Vec4 v4 = {13.0, 14.0, 15.0, 16.0};

  Mat4x4 expected = {
      { 1.0, 5.0,  9.0, 13.0},
      { 2.0, 6.0, 10.0, 14.0},
      { 3.0, 7.0, 11.0, 15.0},
      { 4.0, 8.0, 12.0, 16.0}
  };

  double eps = 1E-14;

  Mat4x4 actual = column_matrix(v1, v2, v3, v4);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps );
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps );
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps );
  REQUIRE(abs(actual(0, 3) - expected(0, 3)) < eps );

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps );
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps );
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps );
  REQUIRE(abs(actual(1, 3) - expected(1, 3)) < eps );

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps );
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps );
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps );
  REQUIRE(abs(actual(2, 3) - expected(2, 3)) < eps );

  REQUIRE(abs(actual(3, 0) - expected(3, 0)) < eps );
  REQUIRE(abs(actual(3, 1) - expected(3, 1)) < eps );
  REQUIRE(abs(actual(3, 2) - expected(3, 2)) < eps );
  REQUIRE(abs(actual(3, 3) - expected(3, 3)) < eps );

}

//###########################################################################//
//# Test row matrix construction                                            #//
//###########################################################################//

TEST_CASE("Test row matrix for 'double' type.", "Matrix4x4") {
  using std::string;
  using Mat4x4 = Matrix4x4<double>;
  using Vec4 = Vector4D<double>;

  Vec4 v1 = { 1.0,  2.0,  3.0,  4.0};
  Vec4 v2 = { 5.0,  6.0,  7.0,  8.0};
  Vec4 v3 = { 9.0, 10.0, 11.0, 12.0};
  Vec4 v4 = {13.0, 14.0, 15.0, 16.0};

  Mat4x4 expected = {
      { 1.0,  2.0,  3.0,  4.0},
      { 5.0,  6.0,  7.0,  8.0},
      { 9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0}
  };

  double eps = 1E-14;

  Mat4x4 actual = row_matrix(v1, v2, v3, v4);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps );
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps );
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps );
  REQUIRE(abs(actual(0, 3) - expected(0, 3)) < eps );

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps );
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps );
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps );
  REQUIRE(abs(actual(1, 3) - expected(1, 3)) < eps );

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps );
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps );
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps );
  REQUIRE(abs(actual(2, 3) - expected(2, 3)) < eps );

  REQUIRE(abs(actual(3, 0) - expected(3, 0)) < eps );
  REQUIRE(abs(actual(3, 1) - expected(3, 1)) < eps );
  REQUIRE(abs(actual(3, 2) - expected(3, 2)) < eps );
  REQUIRE(abs(actual(3, 3) - expected(3, 3)) < eps );

}

TEST_CASE("Test row matrix for 'multiprecision' type.", "Matrix4x4") {

  using std::string;
  using mpfr::mpreal;

  using Mat4x4 = Matrix4x4<mpreal>;
  using Vec4 = Vector4D<mpreal>;

  const int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  Vec4 v1 = { 1.0,  2.0,  3.0,  4.0};
  Vec4 v2 = { 5.0,  6.0,  7.0,  8.0};
  Vec4 v3 = { 9.0, 10.0, 11.0, 12.0};
  Vec4 v4 = {13.0, 14.0, 15.0, 16.0};

  Mat4x4 expected = {
      { 1.0,  2.0,  3.0,  4.0},
      { 5.0,  6.0,  7.0,  8.0},
      { 9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0}
  };

  double eps = 1E-14;

  Mat4x4 actual = row_matrix(v1, v2, v3, v4);

  REQUIRE(abs(actual(0, 0) - expected(0, 0)) < eps );
  REQUIRE(abs(actual(0, 1) - expected(0, 1)) < eps );
  REQUIRE(abs(actual(0, 2) - expected(0, 2)) < eps );
  REQUIRE(abs(actual(0, 3) - expected(0, 3)) < eps );

  REQUIRE(abs(actual(1, 0) - expected(1, 0)) < eps );
  REQUIRE(abs(actual(1, 1) - expected(1, 1)) < eps );
  REQUIRE(abs(actual(1, 2) - expected(1, 2)) < eps );
  REQUIRE(abs(actual(1, 3) - expected(1, 3)) < eps );

  REQUIRE(abs(actual(2, 0) - expected(2, 0)) < eps );
  REQUIRE(abs(actual(2, 1) - expected(2, 1)) < eps );
  REQUIRE(abs(actual(2, 2) - expected(2, 2)) < eps );
  REQUIRE(abs(actual(2, 3) - expected(2, 3)) < eps );

  REQUIRE(abs(actual(3, 0) - expected(3, 0)) < eps );
  REQUIRE(abs(actual(3, 1) - expected(3, 1)) < eps );
  REQUIRE(abs(actual(3, 2) - expected(3, 2)) < eps );
  REQUIRE(abs(actual(3, 3) - expected(3, 3)) < eps );

}
