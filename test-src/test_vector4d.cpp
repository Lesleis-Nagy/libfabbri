//
// Created by Lesleis Nagy on 26/07/2022.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <vector4d.hpp>
#include "mpreal.h"

//###########################################################################//
//# Test addition                                                           #//
//###########################################################################//

TEST_CASE("Test vector addition for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    Vec4D expected = {6.0, 8.0, 10.0, 12.0};

    double eps = 1E-14;
    Vec4D actual = u + v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
    REQUIRE(fabs(actual.z() - expected.z()) < eps);
    REQUIRE(fabs(actual.w() - expected.w()) < eps);

}

TEST_CASE("Test vector addition for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    Vec4D expected = {6.0, 8.0, 10.0, 12.0};

    mpreal eps = 1E-14;
    Vec4D actual = u + v;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );
    REQUIRE( mpfr::abs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test subtraction                                                        #//
//###########################################################################//

TEST_CASE("Test vector subtraction for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    Vec4D expected = {4.0, 4.0, 4.0, 4.0};

    double eps = 1E-14;
    Vec4D actual = v - u;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );
    REQUIRE( fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test vector subtraction for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    Vec4D expected = {4.0, 4.0, 4.0, 4.0};

    mpreal eps = 1E-14;
    Vec4D actual = v - u;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );
    REQUIRE( mpfr::abs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test vector-scalar multiplication                                       #//
//###########################################################################//

TEST_CASE("Test vector-scalar multiplication for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;

    Vec4D expected = {2.0, 4.0, 6.0, 8.0};

    double eps = 1E-14;
    Vec4D actual = u * scalar;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );
    REQUIRE( fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test vector-scalar multiplication for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    mpreal scalar = 2.0;

    Vec4D expected = {2.0, 4.0, 6.0, 8.0};

    mpreal eps = 1E-14;
    Vec4D actual = u * scalar;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );
    REQUIRE( mpfr::abs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test scalar-vector multiplication                                       #//
//###########################################################################//

TEST_CASE("Test scalar-vector multiplication for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;

    Vec4D expected = {2.0, 4.0, 6.0, 8.0};

    double eps = 1E-14;
    Vec4D actual = scalar * u;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );
    REQUIRE( fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test scalar-vector multiplication for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    mpreal scalar = 2.0;

    Vec4D expected = {2.0, 4.0, 6.0, 8.0};

    mpreal eps = 1E-14;
    Vec4D actual = scalar * u;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );
    REQUIRE( mpfr::abs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test vector-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test vector-scalar division for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;

    Vec4D expected = {0.5, 1.0, 1.5, 2.0};

    double eps = 1E-14;
    Vec4D actual = u / scalar;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );
    REQUIRE( fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test vector-scalar division for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    mpreal scalar = 2.0;

    Vec4D expected = {0.5, 1.0, 1.5, 2.0};

    mpreal eps = 1E-14;
    Vec4D actual = u / scalar;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );
    REQUIRE( mpfr::abs(actual.w() - expected.w()) < eps );

}

//###########################################################################//
//# Test vector-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test vector dot product for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    double expected = 70.0;

    double eps = 1E-14;
    double actual = dot(u, v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test vector dot product for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D u = {1.0, 2.0, 3.0, 4.0};
    Vec4D v = {5.0, 6.0, 7.0, 8.0};

    mpreal expected = 70.0;

    mpreal eps = 1E-14;
    mpreal actual = dot(u, v);

    REQUIRE( mpfr::abs(actual - expected) < eps );

}

//###########################################################################//
//# Test vector norm                                                        #//
//###########################################################################//

TEST_CASE("Test regularized norm for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    // The double should fail for regularization-epsilon values (i.e. the values
    // used in regularizing the vector norm) if the test-eps is too high.
    // Whenever the regularization epsilon is set to 1E-8 or smaller the
    // regularization basically never happens because the value is so small it
    // doesn't affect the norm.
    Vec4D::set_eps(1E-7);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    // Note: because the regularization-norm is 1E-7 (see above), 1E-14 is an
    // acceptable choice for the test-eps, however 1E-15 is too small and the
    // test will fail.
    double eps = 1E-14;
    double expected = sqrt(30.0);
    double actual = norm(v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test regularized norm for 'multiprecision' type.", "Vector4D") {

    // In this test we crank up the precision using MPFR.
    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    // We now use a very high precision for the regularization-eps.
    Vec4D::set_eps(1E-20);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    // We expect the test-eps to work down to regularization-eps raised to the
    // 2nd power, in this case 1E-40 == (1E-20)^2 - any smaller value
    // (say 1E-41) should fail.
    mpreal eps = 1E-40;
    mpreal expected = mpfr::sqrt(30.0);
    mpreal actual = norm(v);

    REQUIRE (mpfr::abs(actual - expected) < eps);

}

//###########################################################################//
//# Test vector norm-squared                                                #//
//###########################################################################//

TEST_CASE("Test norm-squared for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D::set_eps(1E-7);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    double eps = 1E-14;
    double expected = 30.0;
    double actual = norm_squared(v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test norm-squared for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D::set_eps(1E-20);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    mpreal eps = 1E-40;
    mpreal expected = 30.0;
    mpreal actual = norm_squared(v);

    REQUIRE (mpfr::abs(actual - expected) < eps);

}

//###########################################################################//
//# Test vector normalized                                                  #//
//###########################################################################//

TEST_CASE("Test normalised() function for 'double' type.", "Vector4D") {

    using std::string;
    using Vec4D = Vector4D<double>;

    Vec4D::set_eps(1E-7);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    double eps = 1E-14;

    Vec4D expected(1.0 / sqrt(30.0),
                   2.0 / sqrt(30.0),
                   3.0 / sqrt(30.0),
                   4.0 / sqrt(30.0) );

    Vec4D actual = normalised(v);

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );
    REQUIRE( fabs(actual.w() - expected.w()) < eps );

}

TEST_CASE("Test normalised() function for 'multiprecision' type.", "Vector4D") {

    using std::string;
    using mpfr::mpreal;

    using Vec4D = Vector4D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec4D::set_eps(1E-20);
    Vec4D v = {1.0, 2.0, 3.0, 4.0};

    mpreal eps = 1E-40;

    Vec4D expected(1.0 / mpfr::sqrt(30.0),
                   2.0 / mpfr::sqrt(30.0),
                   3.0 / mpfr::sqrt(30.0),
                   4.0 / mpfr::sqrt(30.0));

    Vec4D actual = normalised(v);

    REQUIRE( abs(actual.x() - expected.x()) < eps );
    REQUIRE( abs(actual.y() - expected.y()) < eps );
    REQUIRE( abs(actual.z() - expected.z()) < eps );
    REQUIRE( abs(actual.w() - expected.w()) < eps );

}