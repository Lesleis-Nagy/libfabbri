//
// Created by Lesleis Nagy on 27/07/2022.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <fabbri.hpp>
#include "mpreal.h"

// Test omega function.

TEST_CASE("double precision omega function", "fabbri") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1( 1.0,  0.0, -1.0/sqrt(2.0));
    Vector3D<double> r2(-1.0,  0.0, -1.0/sqrt(2.0));
    Vector3D<double> r3( 0.0,  1.0,  1.0/sqrt(2.0));

    Vector3D<double>  r( 0.0, -1.0,  1.0/sqrt(2.0));

    double expected = 2.0*M_PI - 6.0*asin(sqrt(2.0/3.0));
    auto omega = new_omega_fun(r1, r2, r3);

    double eps = 1E-14;

    std::cout.precision(50);
    std::cout << "Expected (double precision) solid angle at test point: " << expected << std::endl;
    std::cout << "Actual (double precision) solid angle at test point:    " << omega(r) << std::endl;

    REQUIRE( fabs(omega(r) - expected) < eps );

}

TEST_CASE("multiprecision omega function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1( 1.0,  0.0, -1.0/mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0,  0.0, -1.0/mpfr::sqrt(2.0));
    Vector3D<mpreal> r3( 0.0,  1.0,  1.0/mpfr::sqrt(2.0));

    Vector3D<mpreal>  r( 0.0, -1.0,  1.0/mpfr::sqrt(2.0));

    mpreal expected = 2.0*mpfr::const_pi() - 6.0*mpfr::asin(mpfr::sqrt(mpreal(2.0)/mpreal(3.0)));
    auto omega = new_omega_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    std::cout.precision(digits);
    std::cout << "Expected (multiprecision) solid angle at test point:   " << expected << std::endl;
    std::cout << "Actual (multiprecision) solid angle at test point:      " << omega(r) << std::endl;

    REQUIRE( abs(omega(r) - expected) < eps );

}

// Test we function.

TEST_CASE("double precision we function", "fabbri") {

    Vector3D<double>::set_eps(1E-6);
    Vector3D<double> r1( 1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r2(-1.0, 0.0, -1.0 / sqrt(2.0));

    Vector3D<double>  r( 0.0, 1.0,  1.0 / sqrt(2.0));

    auto we = new_we_fun(r1, r2);

    double eps = 1E-14;

    double expected = log(3.0);

    std::cout.precision(50);
    std::cout << "Expected (double precision) we at test point:          " << expected << std::endl;
    std::cout << "Actual (double precision) we at test point:             " << we(r)    << std::endl;

    REQUIRE( fabs(we(r) - expected) < eps );

}

TEST_CASE("multiprecision we function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1( 1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal>  r( 0.0, 1.0,  1.0 / mpfr::sqrt(2.0));

    auto we = new_we_fun(r1, r2);

    mpreal eps = 1E-40;

    mpreal expected = mpfr::log(3.0);

    std::cout.precision(digits);
    std::cout << "Expected (multiprecision) we at test point:            " << expected << std::endl;
    std::cout << "Actual (multiprecision) we at test point:               " << we(r)    << std::endl;

    REQUIRE( abs(we(r) - expected) < eps );

}











TEST_CASE("multiprecision Wf function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1( 1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3( 0.0,  1.0,  1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal>  r( 0.0, -1.0,  1.0 / mpfr::sqrt(2.0));

    auto Wf = new_Wf_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    mpreal expected = mpreal(-4) * mpfr::sqrt(mpreal(2)/mpreal(3)) *  mpfr::acot(mpreal(5)/mpfr::sqrt(2))
            + mpfr::sqrt(3) * mpfr::log(3);

    std::cout.precision(digits);
    std::cout << "Expected (multiprecision) Wf at test point: " << expected << std::endl;
    std::cout << "Actual (multiprecision) Wf at test point:   " << Wf(r)    << std::endl;

    REQUIRE( abs(Wf(r) - expected) < eps );

}






TEST_CASE("multiprecision DWf function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1( 1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3( 0.0,  1.0,  1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal>  r( 0.0, -1.0,  1.0 / mpfr::sqrt(2.0));

    auto DWf = new_DWf_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    Vector3D<mpreal> expected(
            0.0,
            mpfr::sqrt(6)*(mpreal(-6)*mpfr::asin(mpfr::sqrt(mpreal(2)/mpreal(3))) + mpreal(2)*mpfr::const_pi()),
            -mpfr::sqrt(3)*(mpreal(-6)*mpfr::asin(mpfr::sqrt(mpreal(2)/mpreal(3))) + mpreal(2)*mpfr::const_pi()));
    Vector3D<mpreal> actual = DWf(r);

    std::cout.precision(digits);
    std::cout << "Expected (multiprecision) DWf at test point:            " << expected << std::endl;
    std::cout << "Actual (multiprecision) DWf at test point:              " << DWf(r)    << std::endl;

    REQUIRE( abs(actual.x() - expected.x()) < eps );
    REQUIRE( abs(actual.y() - expected.y()) < eps );
    REQUIRE( abs(actual.z() - expected.z()) < eps );

}


TEST_CASE("Multiprecision A from uniformly magnetised source", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;

    mpreal::set_default_prec(mpfr::digits2bits(digits));
    mpreal eps = 1E-30;

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal>  m( 1.0,  0.0,  0.0);
    Vector3D<mpreal> r1( 1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0,  0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3( 0.0,  1.0,  1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r4( 0.0, -1.0,  1.0 / mpfr::sqrt(2.0));

    auto A_fun = new_uni_A_fun(m, r1, r2, r3, r4);

    mpreal Ax(" 0", 100);
    mpreal Ay("-0.1802646089889424362532873483685731463465467473379141661995425990010651217986515576976558718907103713", 100);
    mpreal Az(" 0.1745086799793474937269608369966009429768446333009068741867504155052808398622806399265615297942247554", 100);

    Vector3D<mpreal> A_actual = A_fun({1,1,1});

    std::cout.precision(digits);
    std::cout << "Expected (multiprecision) A at test point:  <" << Ax << ", " << Ay << ", " << Az << ">" << std::endl;
    std::cout << "Actual (multiprecision) A at test point:    " << A_actual << std::endl;

    REQUIRE( abs(A_actual.x() - Ax) < eps );
    REQUIRE( abs(A_actual.y() - Ay) < eps );
    REQUIRE( abs(A_actual.z() - Az) < eps );

}
