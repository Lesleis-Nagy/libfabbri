//
// Created by Lesleis Nagy on 27/07/2022.
//

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>

#include <iostream>

#include <fabbri.hpp>
#include "mpreal.h"

// Test omega function.

TEST_CASE("double precision omega (triangular) function", "fabbri") {

    Vector3D<double>::set_eps(1E-7);
    Vector3D<double> r1(1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r2(-1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r3(0.0, 1.0, 1.0 / sqrt(2.0));

    Vector3D<double> r(0.0, -1.0, 1.0 / sqrt(2.0));

    double expected = 2.0 * M_PI - 6.0 * asin(sqrt(2.0 / 3.0));
    auto omega = new_omega_tri_fun(r1, r2, r3);

    double eps = 1E-14;

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "double precision omega (triangular) function" << std::endl;
    std::cout << "Expected (double precision) solid angle at test point: " << expected << std::endl;
    std::cout << "Actual   (double precision) solid angle at test point: " << omega(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(fabs(omega(r) - expected) < eps);

}

TEST_CASE("multiprecision omega (triangular) function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    mpreal expected = 2.0 * mpfr::const_pi() - 6.0 * mpfr::asin(mpfr::sqrt(mpreal(2.0) / mpreal(3.0)));
    auto omega = new_omega_tri_fun(r1, r2, r3);

    mpreal eps = 1E-40;

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision omega (triangular) function" << std::endl;
    std::cout << "Expected (multiprecision) solid angle at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) solid angle at test point: " << omega(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(omega(r) - expected) < eps);

}

// Test we function.

TEST_CASE("double precision we function", "fabbri") {

    Vector3D<double>::set_eps(1E-6);
    Vector3D<double> r1(1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r2(-1.0, 0.0, -1.0 / sqrt(2.0));

    Vector3D<double> r(0.0, 1.0, 1.0 / sqrt(2.0));

    auto we = new_we_fun(r1, r2);

    double eps = 1E-14;

    double expected = log(3.0);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "double precision we function" << std::endl;
    std::cout << "Expected (double precision) we at test point: " << expected << std::endl;
    std::cout << "Actual   (double precision) we at test point: " << we(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(fabs(we(r) - expected) < eps);

}

TEST_CASE("multiprecision we function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    auto we = new_we_fun(r1, r2);

    mpreal eps = 1E-40;

    mpreal expected = mpfr::log(3.0);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision we function" << std::endl;
    std::cout << "Expected (multiprecision) we at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) we at test point: " << we(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(we(r) - expected) < eps);

}

TEST_CASE("multiprecision lambda_e function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto lambda_e = new_lambda_e_fun(r1, r2);

    mpreal eps = 1E-40;

    mpreal expected = (mpreal(3) / mpreal(2)) * mpfr::log(3.0);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision lambda_e function" << std::endl;
    std::cout << "Expected (multiprecision) lambda_e at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) lambda_e at test point: " << lambda_e(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(lambda_e(r) - expected) < eps);

}

TEST_CASE("multiprecision D_lambda_e function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto D_lambda_e = new_D_lambda_e_fun(r1, r2);

    mpreal eps = 1E-40;

    Vector3D<mpreal> expected{0, -mpfr::log(3), mpfr::sqrt(2) * mpfr::log(3.0)};

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision D_lambda_e function" << std::endl;
    std::cout << "Expected (multiprecision) D_lambda_e at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) D_lambda_e at test point: " << D_lambda_e(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(D_lambda_e(r).x() - expected.x()) < eps);
    REQUIRE(abs(D_lambda_e(r).y() - expected.y()) < eps);
    REQUIRE(abs(D_lambda_e(r).z() - expected.z()) < eps);

}

TEST_CASE("multiprecision d_lambda_e_by_dm function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> m(0.0, 0.0, 1.0);
    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto d_lambda_e_by_dm = new_d_lambda_e_by_dm_fun(r1, r2);

    mpreal eps = 1E-40;

    mpreal expected = mpfr::sqrt(2) * mpfr::log(3);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision d_lambda_e_by_dm function" << std::endl;
    std::cout << "Expected (multiprecision) d_lambda_e_by_dm at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) d_lambda_e_by_dm at test point: " << d_lambda_e_by_dm(m, r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(d_lambda_e_by_dm(m, r) - expected) < eps);

}

TEST_CASE("multiprecision Wf (triangular) function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto Wf = new_Wf_tri_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    mpreal expected = mpreal(-4) * mpfr::sqrt(mpreal(2) / mpreal(3)) * mpfr::acot(mpreal(5) / mpfr::sqrt(2))
                      + mpfr::sqrt(3) * mpfr::log(3);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision Wf (triangular) function" << std::endl;
    std::cout << "Expected (multiprecision) Wf at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) Wf at test point: " << Wf(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(Wf(r) - expected) < eps);

}

TEST_CASE("multiprecision DWf (triangular) function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto DWf = new_DWf_tri_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    Vector3D<mpreal> expected(
            0.0,
            mpreal(2) * mpfr::sqrt(mpreal(2) / mpreal(3)) * mpfr::atan(mpfr::sqrt(2) / mpreal(5)),
            mpreal(-2) * mpfr::atan(mpfr::sqrt(2) / mpreal(5)) / mpfr::sqrt(3));
    Vector3D<mpreal> actual = DWf(r);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision DWf (triangular) function" << std::endl;
    std::cout << "Expected (multiprecision) DWf at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) DWf at test point: " << DWf(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(actual.x() - expected.x()) < eps);
    REQUIRE(abs(actual.y() - expected.y()) < eps);
    REQUIRE(abs(actual.z() - expected.z()) < eps);

}

TEST_CASE("multiprecision d_Wf_by_dm_tri_fun (triangular) function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> m(0.0, 0.0, 1.0);
    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto d_Wf_by_dm = new_d_Wf_by_dm_tri_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    mpreal expected = -mpreal(2) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) / mpfr::sqrt(3);

    mpreal actual = d_Wf_by_dm(m, r);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision DWf (triangular) function" << std::endl;
    std::cout << "Expected (multiprecision) d_Wf_by_dm at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) d_Wf_by_dm at test point: " << d_Wf_by_dm(m, r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(actual - expected) < eps);

}

TEST_CASE("double precision Lambda (triangular) function", "fabbri") {

    Vector3D<double> r1(1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r2(-1.0, 0.0, -1.0 / sqrt(2.0));
    Vector3D<double> r3(0.0, 1.0, 1.0 / sqrt(2.0));

    Vector3D<double> r(0.0, -1.0, 1.0 / sqrt(2.0));

    auto Lambda = new_Lambda_fun(r1, r2, r3);

    double eps = 1E-14;

    double expected = 1.8426320969612156532708703220925032742357173038995;

    double actual = Lambda(r);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(50);
    std::cout << "multiprecision Lambda (triangular) function" << std::endl;
    std::cout << "Expected (double precision) Lambda at test point: " << expected << std::endl;
    std::cout << "Actual   (double precision) Lambda at test point: " << Lambda(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(actual - expected) < eps);

}

TEST_CASE("multiprecision Lambda (triangular) function", "fabbri") {

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto Lambda = new_Lambda_fun(r1, r2, r3);

    mpreal eps = 1E-40;

    mpreal expected = (mpreal(1) / mpreal(54)) * (mpreal(-64) * mpfr::sqrt(6) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) +
                                                  mpreal(75) * mpfr::sqrt(3) * mpfr::log(3));

    mpreal actual = Lambda(r);

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "multiprecision Lambda (triangular) function" << std::endl;
    std::cout << "Expected (multiprecision) Lambda at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) Lambda at test point: " << Lambda(r) << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(actual - expected) < eps);

}


TEST_CASE("Multiprecision phi from uniformly magnetised tetrahedron", "fabbri") {

    using mpfr::mpreal;

    const int digits = 50;

    mpreal::set_default_prec(mpfr::digits2bits(digits));
    mpreal eps = 1E-30; // Drop the test epsilon (usually 1E-40).


    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> m(1.0, 0.0, 0.0);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r4(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    mpreal expected(
            "0.1883374544194754824794298630740097166729418160020970191303603027101965340715416180490514550107932100",
            100);
    auto phi_fun = new_uni_tet_phi_fun(m, r1, r2, r3, r4);
    mpreal actual = phi_fun({1, 1, 1});

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "Multiprecision phi from uniformly magnetised tetrahedral source" << std::endl;
    std::cout << "Expected (multiprecision) phi at test point: " << expected << std::endl;
    std::cout << "Actual   (multiprecision) phi at test point: " << actual << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(actual - expected) < eps);

}

TEST_CASE("Multiprecision A from uniformly magnetised source", "fabbri") {

    // Note: this test is suboptimal since it wasn't possible to derive a nice form for the expected values and just
    //       used a numeric value based on my mathematica code (ramped up to 100 digits of precision).

    using mpfr::mpreal;
    const int digits = 50;

    mpreal::set_default_prec(mpfr::digits2bits(digits));
    mpreal eps = 1E-30; // Drop the test epsilon (usually 1E-40).

    Vector3D<mpreal>::set_eps(1E-20);
    Vector3D<mpreal> m(1.0, 0.0, 0.0);
    Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));
    Vector3D<mpreal> r4(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    auto A_fun = new_uni_tet_A_fun(m, r1, r2, r3, r4);

    mpreal Ax(" 0", 100);
    mpreal Ay("-0.1802646089889424362532873483685731463465467473379141661995425990010651217986515576976558718907103713",
              100);
    mpreal Az(" 0.1745086799793474937269608369966009429768446333009068741867504155052808398622806399265615297942247554",
              100);

    Vector3D<mpreal> A_actual = A_fun({1, 1, 1});

#ifdef TEST_DEBUG_MESSAGES
    std::cout.precision(digits);
    std::cout << "Multiprecision A from uniformly magnetised source" << std::endl;
    std::cout << "Expected (multiprecision) A at test point:  <" << Ax << ", " << Ay << ", " << Az << ">" << std::endl;
    std::cout << "Actual   (multiprecision) A at test point:  " << A_actual << std::endl;
#endif // TEST_DEBUG_MESSAGES

    REQUIRE(abs(A_actual.x() - Ax) < eps);
    REQUIRE(abs(A_actual.y() - Ay) < eps);
    REQUIRE(abs(A_actual.z() - Az) < eps);

}
