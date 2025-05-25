//
// Created by Lesleis Nagy on 27/07/2022.
//

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>

#include <iostream>

#include <amiga/fabbri.hpp>
#include "mpreal.h"

#ifdef WIN32
#define M_PI 3.14159265358979323846
#endif

// Rest of your code

//###############################################################################################//
//# Test curl of of linearly varying vector function.                                           #//
//###############################################################################################//

TEST_CASE("double precision curl (linear V over tetrahedron)", "fabbri") {
    using namespace amiga;
    using Vec3 = Vector3D<double>;

    const Vec3 p1 = {2.0, 2.0, 2.0};
    const Vec3 p2 = {3.0, 2.0, 2.0};
    const Vec3 p3 = {2.0, 3.0, 2.0};
    const Vec3 p4 = {2.0, 2.0, 3.0};

    const Vec3 V1 = {-0.1565641612315334, 1.7821671181752250, 1.9944723610252080};
    const Vec3 V2 = {-1.9257910014689320, 0.7612252626710410, -1.0077627432982960};
    const Vec3 V3 = {0.2256064112579468, -0.1888455597153094, -0.2105891754636273};
    const Vec3 V4 = {-1.1114604340590310, -1.0774739798266670, 1.2392878553570320};

    const Vec3 curlV_expected = {
        0.6545795615130547,
        2.0473388314960030,
        -1.4031124279936660
    };

    const Vec3 curlV_actual = curl<double>(p1, p2, p3, p4, V1, V2, V3, V4);

    constexpr double eps = 1E-10;

    REQUIRE(fabs(curlV_expected(0) - curlV_actual(0)) < eps);
    REQUIRE(fabs(curlV_expected(1) - curlV_actual(1)) < eps);
    REQUIRE(fabs(curlV_expected(2) - curlV_actual(2)) < eps);
}

TEST_CASE("multiprecision curl (linear V over tetrahedron)", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    using Vec3 = Vector3D<mpreal>;

    const Vec3 p1 = {2.0, 2.0, 2.0};
    const Vec3 p2 = {3.0, 2.0, 2.0};
    const Vec3 p3 = {2.0, 3.0, 2.0};
    const Vec3 p4 = {2.0, 2.0, 3.0};

    const Vec3 V1 = {-0.1565641612315334, 1.7821671181752250, 1.9944723610252080};
    const Vec3 V2 = {-1.9257910014689320, 0.7612252626710410, -1.0077627432982960};
    const Vec3 V3 = {0.2256064112579468, -0.1888455597153094, -0.2105891754636273};
    const Vec3 V4 = {-1.1114604340590310, -1.0774739798266670, 1.2392878553570320};

    const Vec3 curlV_expected = {
        0.6545795615130547,
        2.0473388314960030,
        -1.4031124279936660
    };

    const Vec3 curlV_actual = curl<mpreal>(p1, p2, p3, p4, V1, V2, V3, V4);

    constexpr double eps = 1E-10;

    REQUIRE(fabs(curlV_expected(0) - curlV_actual(0)) < eps);
    REQUIRE(fabs(curlV_expected(1) - curlV_actual(1)) < eps);
    REQUIRE(fabs(curlV_expected(2) - curlV_actual(2)) < eps);
}

//###############################################################################################//
//# Test curl of of linearly varying vector function.                                           #//
//###############################################################################################//

TEST_CASE("double precision DV", "fabbri") {
    using namespace amiga;
    using Vec3 = Vector3D<double>;
    using Mat3x3 = Matrix3x3<double>;

    Vec3 p0 = {1.0, 1.0, 1.0};
    Vec3 p1 = {2.0, 1.0, 1.0};
    Vec3 p2 = {1.0, 2.0, 1.0};
    Vec3 p3 = {1.0, 1.0, 2.0};

    Vec3 V0 = {-0.07828208061576669, 0.891083559087613, 0.997236180512604};
    Vec3 V1 = {-0.962895500734466, 0.3806126313355205, -0.5038813716491481};
    Vec3 V2 = {0.1128032056289734, -0.0944227798576547, -0.1052945877318137};
    Vec3 V3 = {-0.5557302170295157, -0.5387369899133336, 0.6196439276785162};

    Mat3x3 expected = {
        {-0.884613420118699, 0.1910852862447401, -0.4774481364137491},
        {-0.5104709277520922, -0.985506338945267, -1.429820549000946},
        {-1.501117552161752, -1.102530768244418, -0.3775922528340874}
    };

    double eps = 1E-14;

    Mat3x3 actual = DV(p0, p1, p2, p3, V0, V1, V2, V3);

    REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
    REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
    REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

    REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
    REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
    REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

    REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
    REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
    REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

TEST_CASE("multiprecision DV", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    using Vec3 = Vector3D<mpreal>;
    using Mat3x3 = Matrix3x3<mpreal>;

    Vec3 p0 = {1.0, 1.0, 1.0};
    Vec3 p1 = {2.0, 1.0, 1.0};
    Vec3 p2 = {1.0, 2.0, 1.0};
    Vec3 p3 = {1.0, 1.0, 2.0};

    Vec3 V0 = {-0.07828208061576669, 0.891083559087613, 0.997236180512604};
    Vec3 V1 = {-0.962895500734466, 0.3806126313355205, -0.5038813716491481};
    Vec3 V2 = {0.1128032056289734, -0.0944227798576547, -0.1052945877318137};
    Vec3 V3 = {-0.5557302170295157, -0.5387369899133336, 0.6196439276785162};

    Mat3x3 expected = {
        {-0.884613420118699, 0.1910852862447401, -0.4774481364137491},
        {-0.5104709277520922, -0.985506338945267, -1.429820549000946},
        {-1.501117552161752, -1.102530768244418, -0.3775922528340874}
    };

    mpreal eps = 1E-15;

    Mat3x3 actual = DV(p0, p1, p2, p3, V0, V1, V2, V3);

    REQUIRE(fabs(actual(0, 0) - expected(0, 0)) < eps);
    REQUIRE(fabs(actual(0, 1) - expected(0, 1)) < eps);
    REQUIRE(fabs(actual(0, 2) - expected(0, 2)) < eps);

    REQUIRE(fabs(actual(1, 0) - expected(1, 0)) < eps);
    REQUIRE(fabs(actual(1, 1) - expected(1, 1)) < eps);
    REQUIRE(fabs(actual(1, 2) - expected(1, 2)) < eps);

    REQUIRE(fabs(actual(2, 0) - expected(2, 0)) < eps);
    REQUIRE(fabs(actual(2, 1) - expected(2, 1)) < eps);
    REQUIRE(fabs(actual(2, 2) - expected(2, 2)) < eps);
}

//###############################################################################################//
//# Test omega function.                                                                        #//
//###############################################################################################//

TEST_CASE("double precision omega (triangular) function", "fabbri") {
    using namespace amiga;

    Vector3D<double>::set_eps(1E-7);
    const Vector3D r1(1.0, 0.0, -1.0 / sqrt(2.0));
    const Vector3D r2(-1.0, 0.0, -1.0 / sqrt(2.0));
    const Vector3D r3(0.0, 1.0, 1.0 / sqrt(2.0));

    const Vector3D r(0.0, -1.0, 1.0 / sqrt(2.0));

    const double expected = 2.0 * M_PI - 6.0 * asin(sqrt(2.0 / 3.0));
    const auto omega = new_omega_tri_fun(r1, r2, r3);

    constexpr double eps = 1E-14;

    REQUIRE(fabs(omega(r) - expected) < eps);
}

TEST_CASE("multiprecision omega (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const mpreal expected = 2.0 * mpfr::const_pi() - 6.0 * mpfr::asin(
        mpfr::sqrt(mpreal(2.0) / mpreal(3.0)));
    const auto omega = new_omega_tri_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    REQUIRE(abs(omega(r) - expected) < eps);
}

// Test we function.

TEST_CASE("double precision we function", "fabbri") {
    using namespace amiga;

    Vector3D<double>::set_eps(1E-6);
    const Vector3D r1(1.0, 0.0, -1.0 / sqrt(2.0));
    const Vector3D r2(-1.0, 0.0, -1.0 / sqrt(2.0));

    const Vector3D r(0.0, 1.0, 1.0 / sqrt(2.0));

    const auto we = new_we_fun(r1, r2);

    constexpr double eps = 1E-14;

    const double expected = log(3.0);

    REQUIRE(fabs(we(r) - expected) < eps);
}

TEST_CASE("multiprecision we function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const auto we = new_we_fun(r1, r2);

    const mpreal eps = 1E-40;

    const mpreal expected = mpfr::log(3.0);

    REQUIRE(abs(we(r) - expected) < eps);
}

TEST_CASE("multiprecision lambda_e function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto lambda_e = new_lambda_e_fun(r1, r2);

    const mpreal eps = 1E-40;

    const mpreal expected = mpreal(3) / mpreal(2) * mpfr::log(3.0);

    REQUIRE(abs(lambda_e(r) - expected) < eps);
}

TEST_CASE("multiprecision D_lambda_e function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto D_lambda_e = new_D_lambda_e_fun(r1, r2);

    const mpreal eps = 1E-40;

    const Vector3D<mpreal> expected{0, -mpfr::log(3), mpfr::sqrt(2) * mpfr::log(3.0)};

    REQUIRE(abs(D_lambda_e(r).x() - expected.x()) < eps);
    REQUIRE(abs(D_lambda_e(r).y() - expected.y()) < eps);
    REQUIRE(abs(D_lambda_e(r).z() - expected.z()) < eps);
}

TEST_CASE("multiprecision d_lambda_e_by_dm function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> m(0.0, 0.0, 1.0);
    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto d_lambda_e_by_dm = new_d_lambda_e_by_dm_fun(r1, r2);

    const mpreal eps = 1E-40;

    const mpreal expected = mpfr::sqrt(2) * mpfr::log(3);

    REQUIRE(abs(d_lambda_e_by_dm(m, r) - expected) < eps);
}

TEST_CASE("multiprecision Wf (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto Wf = new_Wf_tri_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const mpreal expected = mpreal(-4) * mpfr::sqrt(mpreal(2) / mpreal(3)) * mpfr::acot(
                mpreal(5) / mpfr::sqrt(2))
            + mpfr::sqrt(3) * mpfr::log(3);

    REQUIRE(abs(Wf(r) - expected) < eps);
}

TEST_CASE("multiprecision DWf (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto DWf = new_DWf_tri_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const Vector3D<mpreal> expected(
        0.0,
        mpreal(2) * mpfr::sqrt(mpreal(2) / mpreal(3)) * mpfr::atan(mpfr::sqrt(2) / mpreal(5)),
        mpreal(-2) * mpfr::atan(mpfr::sqrt(2) / mpreal(5)) / mpfr::sqrt(3)
    );

    const Vector3D<mpreal> actual = DWf(r);

    REQUIRE(abs(actual.x() - expected.x()) < eps);
    REQUIRE(abs(actual.y() - expected.y()) < eps);
    REQUIRE(abs(actual.z() - expected.z()) < eps);
}

TEST_CASE("multiprecision d_Wf_by_dm_tri_fun (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> m(0.0, 0.0, 1.0);
    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto d_Wf_by_dm = new_d_Wf_by_dm_tri_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const mpreal expected = -mpreal(2) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) / mpfr::sqrt(3);

    const mpreal actual = d_Wf_by_dm(m, r);

    REQUIRE(abs(actual - expected) < eps);
}

TEST_CASE("double precision Lambda_f (triangular) function", "fabbri") {
    using namespace amiga;

    const Vector3D r1(1.0, 0.0, -1.0 / sqrt(2.0));
    const Vector3D r2(-1.0, 0.0, -1.0 / sqrt(2.0));
    const Vector3D r3(0.0, 1.0, 1.0 / sqrt(2.0));

    const Vector3D r(0.0, -1.0, 1.0 / sqrt(2.0));

    const auto Lambda_f = new_Lambda_f_fun(r1, r2, r3);

    constexpr double eps = 1E-12;

    constexpr double expected = 1.8426320969612156532708703220925032742357173038995;

    const double actual = Lambda_f(r);

    REQUIRE(abs(actual - expected) < eps);
}

TEST_CASE("multiprecision Lambda_f (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto Lambda_f = new_Lambda_f_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const mpreal expected = mpreal(1) / mpreal(54)
            * (
                mpreal(-64) * mpfr::sqrt(6) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) +
                mpreal(75) * mpfr::sqrt(3) * mpfr::log(3)
            );

    const mpreal actual = Lambda_f(r);

    REQUIRE(abs(actual - expected) < eps);
}

TEST_CASE("multiprecision DLambda_f (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto DLambda_f = new_DLambda_f_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const Vector3D<mpreal> expected(
        0,
        mpreal(4) / mpreal(9) * (
            mpreal(4) * mpfr::sqrt(6) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) - mpreal(3) *
            mpfr::sqrt(3) * mpfr::log(3)
        ),
        mpreal(2) / mpreal(9) * (
            mpreal(-8) * mpfr::sqrt(3) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) + mpfr::sqrt(6) *
            mpfr::log(27)
        ));

    const auto actual = DLambda_f(r);

    REQUIRE(abs(actual.x() - expected.x()) < eps);
    REQUIRE(abs(actual.y() - expected.y()) < eps);
    REQUIRE(abs(actual.z() - expected.z()) < eps);
}

TEST_CASE("multiprecision m_dot_DDLambda_f (triangular) function", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));

    const Vector3D<mpreal> m(0.0, 0.0, 1.0);
    const Vector3D<mpreal> r(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto m_dot_DDLambda_f = new_m_dot_DDLambda_f_fun(r1, r2, r3);

    const mpreal eps = 1E-40;

    const Vector3D<mpreal> expected(
        0,
        mpreal(16) * mpfr::acot(mpreal(5) / mpfr::sqrt(2)) / (mpreal(3) * mpfr::sqrt(3)) -
        mpfr::log(3) / mpfr::sqrt(6),
        mpreal(1) / mpreal(9) * (mpreal(-8) * mpfr::sqrt(6) * mpfr::acot(mpreal(5) / mpfr::sqrt(2))
            + mpreal(6) * mpfr::sqrt(3) * mpfr::log(3))
    );

    const auto actual = m_dot_DDLambda_f(m, r);

    REQUIRE(abs(actual.x() - expected.x()) < eps);
    REQUIRE(abs(actual.y() - expected.y()) < eps);
    REQUIRE(abs(actual.z() - expected.z()) < eps);
}

TEST_CASE("Multiprecision phi from uniformly magnetised tetrahedron", "fabbri") {
    using namespace amiga;
    using mpfr::mpreal;

    constexpr int digits = 50;

    mpreal::set_default_prec(mpfr::digits2bits(digits));
    const mpreal eps = 1E-30; // Drop the test epsilon (usually 1E-40).

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> m(1.0, 0.0, 0.0);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r4(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const mpreal expected(
        "0.1883374544194754824794298630740097166729418160020970191303603027101965340715416180490514550107932100",
        100);
    const auto phi_fun = new_uni_tet_phi_fun(m, r1, r2, r3, r4);
    const mpreal actual = phi_fun({1, 1, 1});

    REQUIRE(abs(actual - expected) < eps);
}

TEST_CASE("Multiprecision A from uniformly magnetised source", "fabbri") {
    using namespace amiga;

    // Note: this test is suboptimal since it wasn't possible to derive a nice form for the
    //       expected values and just used a numeric value based on my mathematica code (ramped up
    //       to 100 digits of precision).

    using mpfr::mpreal;
    constexpr int digits = 50;

    mpreal::set_default_prec(mpfr::digits2bits(digits));
    const mpreal eps = 1E-30; // Drop the test epsilon (usually 1E-40).

    Vector3D<mpreal>::set_eps(1E-20);
    const Vector3D<mpreal> m(1.0, 0.0, 0.0);
    const Vector3D<mpreal> r1(1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r2(-1.0, 0.0, -1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r3(0.0, 1.0, 1.0 / mpfr::sqrt(2.0));
    const Vector3D<mpreal> r4(0.0, -1.0, 1.0 / mpfr::sqrt(2.0));

    const auto A_fun = new_uni_tet_A_fun(m, r1, r2, r3, r4);

    const mpreal Ax(" 0", 100);
    const mpreal Ay(
        "-0.1802646089889424362532873483685731463465467473379141661995425990010651217986515576976558718907103713",
        100);
    const mpreal Az(
        " 0.1745086799793474937269608369966009429768446333009068741867504155052808398622806399265615297942247554",
        100);

    const Vector3D<mpreal> A_actual = A_fun({1, 1, 1});

    REQUIRE(abs(A_actual.x() - Ax) < eps);
    REQUIRE(abs(A_actual.y() - Ay) < eps);
    REQUIRE(abs(A_actual.z() - Az) < eps);
}
