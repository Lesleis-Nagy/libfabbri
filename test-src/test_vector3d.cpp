//
// Created by Lesleis Nagy on 26/07/2022.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <vector3d.hpp>
#include "mpreal.h"

TEST_CASE("Test vector addition for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    Vector3D<double> v(4.0, 5.0, 6.0);

    Vector3D<double> expected(5.0, 7.0, 9.0);

    double eps = 1E-14;
    Vector3D<double> result = u + v;

    REQUIRE( fabs(result.x() - expected.x()) < eps );
    REQUIRE( fabs(result.y() - expected.y()) < eps );
    REQUIRE( fabs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector addition for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    Vector3D<mpreal> v(4.0, 5.0, 6.0);

    Vector3D<mpreal> expected(5.0, 7.0, 9.0);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = u + v;

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector subtraction for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    Vector3D<double> v(4.0, 5.0, 6.0);

    Vector3D<double> expected(3.0, 3.0, 3.0);

    double eps = 1E-14;
    Vector3D<double> result = v - u;

    REQUIRE( fabs(result.x() - expected.x()) < eps );
    REQUIRE( fabs(result.y() - expected.y()) < eps );
    REQUIRE( fabs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector subtraction for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    Vector3D<mpreal> v(4.0, 5.0, 6.0);

    Vector3D<mpreal> expected(3.0, 3.0, 3.0);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = v - u;

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar multiplication for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    double scalar = 2.0;

    Vector3D<double> expected(2.0, 4.0, 6.0);

    double eps = 1E-14;
    Vector3D<double> result = u * scalar;

    REQUIRE( fabs(result.x() - expected.x()) < eps );
    REQUIRE( fabs(result.y() - expected.y()) < eps );
    REQUIRE( fabs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar multiplication for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    mpreal scalar = 2.0;

    Vector3D<mpreal> expected(2.0, 4.0, 6.0);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = u * scalar;

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test scalar-vector multiplication for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    double scalar = 2.0;

    Vector3D<double> expected(2.0, 4.0, 6.0);

    double eps = 1E-14;
    Vector3D<double> result = scalar * u;

    REQUIRE( fabs(result.x() - expected.x()) < eps );
    REQUIRE( fabs(result.y() - expected.y()) < eps );
    REQUIRE( fabs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test scalar-vector multiplication for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    mpreal scalar = 2.0;

    Vector3D<mpreal> expected(2.0, 4.0, 6.0);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = scalar * u;

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar division for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    double scalar = 2.0;

    Vector3D<double> expected(0.5, 1.0, 1.5);

    double eps = 1E-14;
    Vector3D<double> result = u / scalar;

    REQUIRE( fabs(result.x() - expected.x()) < eps );
    REQUIRE( fabs(result.y() - expected.y()) < eps );
    REQUIRE( fabs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar division for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    mpreal scalar = 2.0;

    Vector3D<mpreal> expected(0.5, 1.0, 1.5);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = u / scalar;

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector dot product for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    Vector3D<double> v(4.0, 5.0, 6.0);

    double expected = 32.0;

    double eps = 1E-14;
    double result = dot(u, v);

    REQUIRE( fabs(result - expected) < eps );

}

TEST_CASE("Test vector dot product for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    Vector3D<mpreal> v(4.0, 5.0, 6.0);

    mpreal expected = 32.0;

    mpreal eps = 1E-14;
    mpreal result = dot(u, v);

    REQUIRE( mpfr::abs(result - expected) < eps );

}

TEST_CASE("Test vector cross product for 'double' type.", "Vector3D") {

    Vector3D<double> u(1.0, 2.0, 3.0);
    Vector3D<double> v(4.0, 5.0, 6.0);

    Vector3D<double> expected(-3.0, 6.0, -3.0);

    double eps = 1E-14;
    Vector3D<double> result = cross(u, v);

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test vector cross product for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    Vector3D<mpreal> v(4.0, 5.0, 6.0);

    Vector3D<mpreal> expected(-3.0, 6.0, -3.0);

    mpreal eps = 1E-14;
    Vector3D<mpreal> result = cross(u, v);

    REQUIRE( mpfr::abs(result.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(result.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(result.z() - expected.z()) < eps );

}

TEST_CASE("Test regularized norm for 'double' type.", "Vector3D") {

    // The double should fail for regularization-epsilon values (i.e. the values used in
    // regularizing the vector norm) if the test-eps is too high. Whenever the
    // regularization epsilon is set to 1E-8 or smaller the regularization basically
    // never happens because the value is so small it doesn't affect the norm.
    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> v(1.0, 2.0, 3.0);

    // Note: because the regularization-norm is 1E-7 (see above), 1E-14 is an acceptable
    // choice for the test-eps, however 1E-15 is too small and the test will fail.
    double eps = 1E-14;
    double expected = sqrt(14.0);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                           double (norm)                                   |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected        | " << expected                                  << "     |" << std::endl;
    std::cout << "| actual          | " << norm(v)                                   << "     |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<double>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<double>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE( fabs(norm(v) - expected) < eps );

}

TEST_CASE("Test regularized norm for 'multiprecision' type.", "Vector3D") {

    // In this test we crank up the precision using MPFR.

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    // We now use a very high precision for the regularization-eps.
    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> v(1.0, 2.0, 3.0);

    // We expect the test-eps to work down to regularization-eps raised to the 2nd power,
    // in this case 1E-40 == (1E-20)^2 - any smaller value (say 1E-41) should fail.
    mpreal eps = 1E-40;
    mpreal expected = mpfr::sqrt(14.0);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                      multiprecision (norm)                                |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected        | " << expected                                  << "     |" << std::endl;
    std::cout << "| actual          | " << norm(v)                                   << "     |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<mpreal>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<mpreal>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE (mpfr::abs(norm(v) - expected) < eps);

}

TEST_CASE("Test normalised() function for 'double' type.", "Vector3D") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> v(1.0, 2.0, 3.0);

    double eps = 1E-14;
    Vector3D<double> expected(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0) );
    Vector3D<double> actual = normalised(v);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                        double (normalised)                                |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected x      | " << expected.x()                               << "    |" << std::endl;
    std::cout << "| actual x        | " << actual.x()                                 << "    |" << std::endl;
    std::cout << "| expected y      | " << expected.y()                               << "    |" << std::endl;
    std::cout << "| actual y        | " << actual.y()                                 << "    |" << std::endl;
    std::cout << "| expected z      | " << expected.z()                               << "    |" << std::endl;
    std::cout << "| actual z        | " << actual.z()                                 << "    |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<double>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<double>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test normalised() function for 'multiprecision' type.", "Vector3D") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> v(1.0, 2.0, 3.0);

    mpreal eps = 1E-40;
    Vector3D<mpreal> expected(1.0 / mpfr::sqrt(14.0), 2.0 / mpfr::sqrt(14.0), 3.0 / mpfr::sqrt(14.0) );
    Vector3D<mpreal> actual = normalised(v);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                   multiprecision (normalised)                             |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected x      | " << expected.x()                               << "    |" << std::endl;
    std::cout << "| actual x        | " << actual.x()                                << "     |" << std::endl;
    std::cout << "| expected y      | " << expected.y()                               << "    |" << std::endl;
    std::cout << "| actual y        | " << actual.y()                                << "     |" << std::endl;
    std::cout << "| expected z      | " << expected.z()                               << "    |" << std::endl;
    std::cout << "| actual z        | " << actual.z()                                << "     |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<mpreal>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<mpreal>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE( abs(actual.x() - expected.x()) < eps );
    REQUIRE( abs(actual.y() - expected.y()) < eps );
    REQUIRE( abs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test edge_length() function for 'double' type.", "Vector3D geometry") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> u(1.0, 2.0, 3.0);
    Vector3D<double> v(4.0, 5.0, 6.0);

    double eps = 1E-14;
    double expected = sqrt(27.0);
    double d1 = edge_length(u, v);
    double d2 = edge_length(v, u);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                          double (edge_length)                             |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected        | " << expected                            << "           |" << std::endl;
    std::cout << "| actual d1       | " << d1                                        << "     |" << std::endl;
    std::cout << "| actual d2       | " << d2                                        << "     |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<double>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<double>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE( fabs(d1 - expected) < eps );
    REQUIRE( fabs(d2 - expected) < eps );

}

TEST_CASE("Test edge_length() function for 'multiprecision' type.", "Vector3D geometry") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> u(1.0, 2.0, 3.0);
    Vector3D<mpreal> v(4.0, 5.0, 6.0);

    mpreal eps = 1E-40;
    mpreal expected = mpfr::sqrt(27.0);
    mpreal d1 = edge_length(u, v);
    mpreal d2 = edge_length(v, u);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                        multiprecision (edge_length)                       |" << std::endl;
    std::cout << "+---------------------------------------------------------------------------+" << std::endl;
    std::cout << "| variable        | value                                                   |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
    std::cout << "| expected        | " << expected                                  << "     |" << std::endl;
    std::cout << "| actual d1       | " << d1                                        << "     |" << std::endl;
    std::cout << "| actual d2       | " << d2                                        << "     |" << std::endl;
    std::cout << "| reg-eps         | " << Vector3D<mpreal>::eps << " |" << std::endl;
    std::cout << "| reg-eps squared | " << Vector3D<mpreal>::eps_squared << " |" << std::endl;
    std::cout << "+-----------------+---------------------------------------------------------+" << std::endl;
#endif

    REQUIRE( abs(d1 - expected) < eps );
    REQUIRE( abs(d2 - expected) < eps );

}

TEST_CASE("Test edge_center() function for 'double' type.", "Vector3D geometry") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1(1.0, 2.0, 3.0);
    Vector3D<double> r2(4.0, 5.0, 6.0);

    Vector3D<double> expected(5.0/2.0, 7.0/2.0, 9.0/2.0);
    Vector3D<double> actual = edge_center(r1, r2);

    double eps = 1E-14;
    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test edge_center() function for 'multiprecision' type.", "Vector3D geometry") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 2.0, 3.0);
    Vector3D<mpreal> r2(4.0, 5.0, 6.0);

    Vector3D<mpreal> expected(mpreal(5.0)/mpreal(2.0), mpreal(7.0)/mpreal(2.0), mpreal(9.0)/mpreal(2.0));
    Vector3D<mpreal> actual = edge_center(r1, r2);

    mpreal eps = 1E-40;
    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test edge_orientation() function for 'double' type.", "Vector3D geometry") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1(1.0, 2.0, 3.0);
    Vector3D<double> r2(4.0, 5.0, 6.0);

    Vector3D<double> expected(3.0/sqrt(27.0), 3.0/sqrt(27.0), 3.0/sqrt(27.0));
    Vector3D<double> actual = edge_orientation(r1, r2);

    double eps = 1E-14;
    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test edge_orientation() function for 'multiprecision' type.", "Vector3D geometry") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 2.0, 3.0);
    Vector3D<mpreal> r2(4.0, 5.0, 6.0);

    Vector3D<mpreal> expected(3.0/mpfr::sqrt(27.0), 3.0/mpfr::sqrt(27.0), 3.0/mpfr::sqrt(27.0));
    Vector3D<mpreal> actual = edge_orientation(r1, r2);

    mpreal eps = 1E-40;
    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test triangle_normal() function for 'double' type.", "Vector3D geometry") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1(1.0, 0.0, 0.0);
    Vector3D<double> r2(0.0, 1.0, 0.0);
    Vector3D<double> r3(0.0, 0.0, 1.0);

    Vector3D<double> expected(1.0/sqrt(3), 1.0/sqrt(3.0), 1.0/sqrt(3.0));
    Vector3D<double> actual = triangle_normal(r1, r2, r3);

    double eps = 1E-14;
    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test triangle_normal() function for 'multiprecision' type.", "Vector3D geometry") {
    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, 0.0);
    Vector3D<mpreal> r2(0.0, 1.0, 0.0);
    Vector3D<mpreal> r3(0.0, 0.0, 1.0);

    mpreal eps = 1E-40;
    Vector3D<mpreal> expected(1.0/mpfr::sqrt(3.0), 1.0/mpfr::sqrt(3.0), 1.0/mpfr::sqrt(3.0));
    Vector3D<mpreal> actual = triangle_normal(r1, r2, r3);

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test triangle_center() function for 'double' type.", "Vector3D geometry") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1(1.0, 0.0, 0.0);
    Vector3D<double> r2(0.0, 1.0, 0.0);
    Vector3D<double> r3(0.0, 0.0, 1.0);

    Vector3D<double> expected(1.0/3.0, 1.0/3.0, 1.0/3.0);
    Vector3D<double> actual = triangle_center(r1, r2, r3);

    double eps = 1E-14;
    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );
}

TEST_CASE("Test triangle_center() function for 'multiprecision' type.", "Vector3D geometry") {
    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, 0.0);
    Vector3D<mpreal> r2(0.0, 1.0, 0.0);
    Vector3D<mpreal> r3(0.0, 0.0, 1.0);

    mpreal eps = 1E-40;
    Vector3D<mpreal> expected(mpreal(1.0)/mpreal(3.0), mpreal(1.0)/mpreal(3.0), mpreal(1.0)/mpreal(3.0));
    Vector3D<mpreal> actual = triangle_center(r1, r2, r3);

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}
