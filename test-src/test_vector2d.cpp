//
// Created by Lesleis Nagy on 26/07/2022.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <amiga/vector2d.hpp>
#include "mpreal.h"

//###########################################################################//
//# Test addition                                                           #//
//###########################################################################//

TEST_CASE("Test vector addition for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const Vec2D expected = {5.0, 7.0};

    constexpr double eps = 1E-14;
    const Vec2D actual = u + v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test vector addition for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const Vec2D expected = {5.0, 7.0};

    const mpreal eps = 1E-14;
    const Vec2D actual = u + v;

    REQUIRE(mpfr::abs(actual.x() - expected.x()) < eps);
    REQUIRE(mpfr::abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test subtraction                                                        #//
//###########################################################################//

TEST_CASE("Test vector subtraction for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const Vec2D expected = {3.0, 3.0};

    constexpr double eps = 1E-14;
    const Vec2D actual = v - u;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test vector subtraction for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const Vec2D expected = {3.0, 3.0};

    const mpreal eps = 1E-14;
    const Vec2D actual = v - u;

    REQUIRE(mpfr::abs(actual.x() - expected.x()) < eps);
    REQUIRE(mpfr::abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test vector-scalar multiplication                                       #//
//###########################################################################//

TEST_CASE("Test vector-scalar multiplication for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    constexpr double scalar = 2.0;

    const Vec2D expected = {2.0, 4.0};

    constexpr double eps = 1E-14;
    const Vec2D actual = u * scalar;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test vector-scalar multiplication for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const mpreal scalar = 2.0;

    const Vec2D expected = {2.0, 4.0};

    const mpreal eps = 1E-14;
    const Vec2D actual = u * scalar;

    REQUIRE(mpfr::abs(actual.x() - expected.x()) < eps);
    REQUIRE(mpfr::abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test scalar-vector multiplication                                       #//
//###########################################################################//

TEST_CASE("Test scalar-vector multiplication for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    constexpr double scalar = 2.0;

    const Vec2D expected = {2.0, 4.0};

    constexpr double eps = 1E-14;
    const Vec2D actual = scalar * u;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test scalar-vector multiplication for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const mpreal scalar = 2.0;

    const Vec2D expected = {2.0, 4.0};

    const mpreal eps = 1E-14;
    const Vec2D actual = scalar * u;

    REQUIRE(mpfr::abs(actual.x() - expected.x()) < eps);
    REQUIRE(mpfr::abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test vector-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test vector-scalar division for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    constexpr double scalar = 2.0;

    const Vec2D expected = {0.5, 1.0};

    constexpr double eps = 1E-14;
    const Vec2D actual = u / scalar;

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test vector-scalar division for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const mpreal scalar = 2.0;

    const Vec2D expected = {0.5, 1.0};

    const mpreal eps = 1E-14;
    const Vec2D actual = u / scalar;

    REQUIRE(mpfr::abs(actual.x() - expected.x()) < eps);
    REQUIRE(mpfr::abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test vector dot product                                                 #//
//###########################################################################//

TEST_CASE("Test vector dot product for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    constexpr double expected = 14.0;

    constexpr double eps = 1E-14;
    const double actual = dot(u, v);

    REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test vector dot product for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const mpreal expected = 14.0;

    const mpreal eps = 1E-14;
    const mpreal actual = dot(u, v);

    REQUIRE(mpfr::abs(actual - expected) < eps);
}

//###########################################################################//
//# Test vector cross product                                               #//
//###########################################################################//

TEST_CASE("Test vector cross product for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    constexpr double expected = -3.0;

    constexpr double eps = 1E-14;
    const double actual = cross(u, v);

    REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test vector cross product for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vec2D u = {1.0, 2.0};
    const Vec2D v = {4.0, 5.0};

    const mpreal expected = -3.0;

    const mpreal eps = 1E-14;
    const mpreal actual = cross(u, v);

    REQUIRE(mpfr::abs(actual - expected) < eps);
}

//###########################################################################//
//# Test vector norm                                                        #//
//###########################################################################//

TEST_CASE("Test regularized norm for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    // The double should fail for regularisation-epsilon values (i.e. the values
    // used in regularising the vector norm) if the test-eps is too high.
    // Whenever the regularisation epsilon is set to 1E-8 or smaller, the
    // regularisation basically never happens because the value is so small it
    // doesn't affect the norm.
    Vec2D::set_eps(1E-7);
    const Vec2D v = {1.0, 2.0};

    // Note: because the regularization-norm is 1E-7 (see above), 1E-14 is an
    // acceptable choice for the test-eps, however 1E-15 is too small and the
    // test will fail.
    constexpr double eps = 1E-14;
    const double expected = sqrt(5.0);
    const double actual = norm(v);

    REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test regularized norm for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    // We now use a very high precision for the regularization-eps.
    Vec2D::set_eps(1E-20);
    const Vec2D v = {1.0, 2.0};

    // We expect the test-eps to work down to regularization-eps raised to the
    // 2nd power, in this case 1E-40 == (1E-20)^2 - any smaller value
    // (say 1E-41) should fail.
    const mpreal eps = 1E-40;
    const mpreal expected = mpfr::sqrt(5.0);
    const mpreal actual = norm(v);

    REQUIRE(mpfr::abs(actual - expected) < eps);
}

//###########################################################################//
//# Test vector norm-squared                                                #//
//###########################################################################//

TEST_CASE("Test norm-squared for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    Vec2D::set_eps(1E-7);
    const Vec2D v = {1.0, 2.0};

    constexpr double eps = 1E-14;
    constexpr double expected = 5.0;
    const double actual = norm_squared(v);

    REQUIRE(fabs(actual - expected) < eps);
}

TEST_CASE("Test norm-squared for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec2D::set_eps(1E-20);
    const Vec2D v = {1.0, 2.0};

    const mpreal eps = 1E-40;
    const mpreal expected = 5.0;
    const mpreal actual = norm_squared(v);

    REQUIRE(mpfr::abs(actual - expected) < eps);
}

//###########################################################################//
//# Test vector normalized                                                  #//
//###########################################################################//

TEST_CASE("Test normalised() function for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    Vec2D::set_eps(1E-7);
    const Vec2D v = {1.0, 2.0};

    constexpr double eps = 1E-14;
    const Vec2D expected(1.0 / sqrt(5.0), 2.0 / sqrt(5.0));
    const Vec2D actual = normalised(v);

    REQUIRE(fabs(actual.x() - expected.x()) < eps);
    REQUIRE(fabs(actual.y() - expected.y()) < eps);
}

TEST_CASE("Test normalised() function for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec2D::set_eps(1E-20);
    const Vec2D v = {1.0, 2.0};

    const mpreal eps = 1E-40;
    const Vec2D expected(1.0 / mpfr::sqrt(5.0), 2.0 / mpfr::sqrt(5.0));
    const Vec2D actual = normalised(v);

    REQUIRE(abs(actual.x() - expected.x()) < eps);
    REQUIRE(abs(actual.y() - expected.y()) < eps);
}

//###########################################################################//
//# Test additive fold                                                      #//
//###########################################################################//

TEST_CASE("Test afold() function for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    Vec2D::set_eps(1E-7);
    const Vec2D v = {1.0, 2.0};

    constexpr double eps = 1E-14;
    constexpr double expected = 3.0;

    REQUIRE(abs(afold(v) - expected) < eps);
}

TEST_CASE("Test afold() function for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec2D::set_eps(1E-20);
    const Vec2D v = {1.0, 2.0};

    const mpreal eps = 1E-40;
    const mpreal expected = 3.0;

    REQUIRE(abs(afold(v) - expected) < eps);
}

//###########################################################################//
//# Test multiplicative fold                                                #//
//###########################################################################//

TEST_CASE("Test mfold() function for 'double' type.", "Vector2D") {
    using namespace amiga;
    using std::string;

    using Vec2D = Vector2D<double>;

    Vec2D::set_eps(1E-7);
    const Vec2D v = {1.0, 2.0};

    constexpr double eps = 1E-14;
    constexpr double expected = 2.0;

    REQUIRE(abs(mfold(v) - expected) < eps);
}

TEST_CASE("Test mfold() function for 'multiprecision' type.", "Vector2D") {
    using namespace amiga;
    using std::string;
    using mpfr::mpreal;

    using Vec2D = Vector2D<mpreal>;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec2D::set_eps(1E-20);
    const Vec2D v = {1.0, 2.0};

    const mpreal eps = 1E-40;
    const mpreal expected = 2.0;

    REQUIRE(abs(mfold(v) - expected) < eps);
}
