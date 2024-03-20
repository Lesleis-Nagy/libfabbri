//
// Created by Lesleis Nagy on 26/07/2022.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <vector3d.hpp>
#include "mpreal.h"

//###########################################################################//
//# Test addition                                                           #//
//###########################################################################//

TEST_CASE("Test vector addition for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {5.0, 7.0, 9.0};

    double eps = 1E-14;
    Vec3D actual = u + v;

    REQUIRE(fabs(actual.x() - expected.x()) < eps );
    REQUIRE(fabs(actual.y() - expected.y()) < eps );
    REQUIRE(fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test vector addition for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {5.0, 7.0, 9.0};

    mpreal eps = 1E-14;
    Vec3D actual = u + v;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test subtraction                                                        #//
//###########################################################################//

TEST_CASE("Test vector subtraction for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0, 3.0, 3.0};

    double eps = 1E-14;
    Vec3D actual = v - u;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test vector subtraction for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0, 3.0, 3.0};

    mpreal eps = 1E-14;
    Vec3D actual = v - u;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test vector-scalar multiplication                                       #//
//###########################################################################//

TEST_CASE("Test vector-scalar multiplication for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    double scalar = 2.0;

    Vec3D expected = {2.0, 4.0, 6.0};

    double eps = 1E-14;
    Vec3D actual = u * scalar;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar multiplication for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    mpreal scalar = 2.0;

    Vec3D expected = {2.0, 4.0, 6.0};

    mpreal eps = 1E-14;
    Vec3D actual = u * scalar;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test scalar-vector multiplication                                       #//
//###########################################################################//

TEST_CASE("Test scalar-vector multiplication for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    double scalar = 2.0;

    Vec3D expected = {2.0, 4.0, 6.0};

    double eps = 1E-14;
    Vec3D actual = scalar * u;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test scalar-vector multiplication for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    mpreal scalar = 2.0;

    Vec3D expected = {2.0, 4.0, 6.0};

    mpreal eps = 1E-14;
    Vec3D actual = scalar * u;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test vector-scalar division                                             #//
//###########################################################################//

TEST_CASE("Test vector-scalar division for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    double scalar = 2.0;

    Vec3D expected = {0.5, 1.0, 1.5};

    double eps = 1E-14;
    Vec3D actual = u / scalar;

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test vector-scalar division for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    mpreal scalar = 2.0;

    Vec3D expected = {0.5, 1.0, 1.5};

    mpreal eps = 1E-14;
    Vec3D actual = u / scalar;

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test vector dot product                                                 #//
//###########################################################################//

TEST_CASE("Test vector dot product for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    double expected = 32.0;

    double eps = 1E-14;
    double actual = dot(u, v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test vector dot product for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    mpreal expected = 32.0;

    mpreal eps = 1E-14;
    mpreal actual = dot(u, v);

    REQUIRE( mpfr::abs(actual - expected) < eps );

}

//###########################################################################//
//# Test vector cross product                                               #//
//###########################################################################//

TEST_CASE("Test vector cross product for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {-3.0, 6.0, -3.0};

    double eps = 1E-14;
    Vec3D actual = cross(u, v);

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test vector cross product for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    Vec3D expected = {-3.0, 6.0, -3.0};

    mpreal eps = 1E-14;
    Vec3D actual = cross(u, v);

    REQUIRE( mpfr::abs(actual.x() - expected.x()) < eps );
    REQUIRE( mpfr::abs(actual.y() - expected.y()) < eps );
    REQUIRE( mpfr::abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test vector norm                                                        #//
//###########################################################################//

TEST_CASE("Test regularized norm for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    // The double should fail for regularization-epsilon values (i.e. the values
    // used in regularizing the vector norm) if the test-eps is too high.
    // Whenever the regularization epsilon is set to 1E-8 or smaller the
    // regularization basically never happens because the value is so small it
    // doesn't affect the norm.
    Vec3D::set_eps(1E-7);
    Vec3D v = {1.0, 2.0, 3.0};

    // Note: because the regularization-norm is 1E-7 (see above), 1E-14 is an
    // acceptable choice for the test-eps, however 1E-15 is too small and the
    // test will fail.
    double eps = 1E-14;
    double expected = sqrt(14.0);
    double actual = norm(v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test regularized norm for 'multiprecision' type.", "Vector3D") {

    // In this test we crank up the precision using MPFR.
    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    // We now use a very high precision for the regularization-eps.
    Vec3D::set_eps(1E-20);
    Vec3D v = {1.0, 2.0, 3.0};

    // We expect the test-eps to work down to regularization-eps raised to the
    // 2nd power, in this case 1E-40 == (1E-20)^2 - any smaller value
    // (say 1E-41) should fail.
    mpreal eps = 1E-40;
    mpreal expected = mpfr::sqrt(14.0);
    mpreal actual = norm(v);

    REQUIRE (mpfr::abs(actual - expected) < eps);

}

//###########################################################################//
//# Test vector norm-squared                                                #//
//###########################################################################//

TEST_CASE("Test norm-squared for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D v = {1.0, 2.0, 3.0};

    double eps = 1E-14;
    double expected = 14.0;
    double actual = norm_squared(v);

    REQUIRE( fabs(actual - expected) < eps );

}

TEST_CASE("Test norm-squared for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D v = {1.0, 2.0, 3.0};

    mpreal eps = 1E-40;
    mpreal expected = 14.0;
    mpreal actual = norm_squared(v);

    REQUIRE (mpfr::abs(actual - expected) < eps);

}

//###########################################################################//
//# Test vector normalized                                                  #//
//###########################################################################//

TEST_CASE("Test normalised() function for 'double' type.", "Vector3D") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D v = {1.0, 2.0, 3.0};

    double eps = 1E-14;
    Vec3D expected(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0) );
    Vec3D actual = normalised(v);

    REQUIRE( fabs(actual.x() - expected.x()) < eps );
    REQUIRE( fabs(actual.y() - expected.y()) < eps );
    REQUIRE( fabs(actual.z() - expected.z()) < eps );

}

TEST_CASE("Test normalised() function for 'multiprecision' type.", "Vector3D") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D v = {1.0, 2.0, 3.0};

    mpreal eps = 1E-40;
    Vec3D expected(1.0 / mpfr::sqrt(14.0), 2.0 / mpfr::sqrt(14.0), 3.0 / mpfr::sqrt(14.0) );
    Vec3D actual = normalised(v);

    REQUIRE( abs(actual.x() - expected.x()) < eps );
    REQUIRE( abs(actual.y() - expected.y()) < eps );
    REQUIRE( abs(actual.z() - expected.z()) < eps );

}

//###########################################################################//
//# Test geometry edge length                                               #//
//###########################################################################//

TEST_CASE("Test edge_length() function for 'double' type.", "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D u = {1.0, 2.0, 3.0};
    Vec3D v = {4.0, 5.0, 6.0};

    double eps = 1E-14;
    double expected = sqrt(27.0);
    double actual_d1 = edge_length(u, v);
    double actual_d2 = edge_length(v, u);

    REQUIRE(fabs(actual_d1 - expected) < eps );
    REQUIRE(fabs(actual_d2 - expected) < eps );

}

TEST_CASE("Test edge_length() function for 'multiprecision' type.", "Vector3D geometry") {

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

    REQUIRE(abs(actual_d1 - expected) < eps );
    REQUIRE(abs(actual_d2 - expected) < eps );

}

//###########################################################################//
//# Test geometry edge center                                               #//
//###########################################################################//

TEST_CASE("Test edge_center() function for 'double' type.", "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {5.0/2.0, 7.0/2.0, 9.0/2.0};

    Vec3D actual = edge_center(r1, r2);

    double eps = 1E-14;

    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test edge_center() function for 'multiprecision' type.", "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {mpreal(5.0)/mpreal(2.0),
                      mpreal(7.0)/mpreal(2.0),
                      mpreal(9.0)/mpreal(2.0)};
    Vec3D actual = edge_center(r1, r2);

    mpreal eps = 1E-40;

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

//###########################################################################//
//# Test geometry edge orientation                                          #//
//###########################################################################//

TEST_CASE("Test edge_orientation() function for 'double' type.", "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0/sqrt(27.0),
                      3.0/sqrt(27.0),
                      3.0/sqrt(27.0)};

    Vec3D actual = edge_orientation(r1, r2);

    double eps = 1E-14;

    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test edge_orientation() function for 'multiprecision' type.", "Vector3D geometry") {

    using std::string;
    using mpfr::mpreal;

    using Vec3D = Vector3D<mpreal>;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    Vec3D::set_eps(1E-20);
    Vec3D r1 = {1.0, 2.0, 3.0};
    Vec3D r2 = {4.0, 5.0, 6.0};

    Vec3D expected = {3.0/mpfr::sqrt(27.0),
                      3.0/mpfr::sqrt(27.0),
                      3.0/mpfr::sqrt(27.0)};

    Vec3D actual = edge_orientation(r1, r2);

    mpreal eps = 1E-40;

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

//###########################################################################//
//# Test geometry triangle normal                                           #//
//###########################################################################//

TEST_CASE("Test triangle_normal() function for 'double' type.", "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    Vec3D expected = {1.0/sqrt(3),
                      1.0/sqrt(3.0),
                      1.0/sqrt(3.0)};

    Vec3D actual = triangle_normal(r1, r2, r3);

    double eps = 1E-14;

    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test triangle_normal() function for 'multiprecision' type.", "Vector3D geometry") {

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
    Vec3D expected = {1.0/mpfr::sqrt(3.0),
                      1.0/mpfr::sqrt(3.0),
                      1.0/mpfr::sqrt(3.0)};

    Vec3D actual = triangle_normal(r1, r2, r3);

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}

//###########################################################################//
//# Test geometry triangle center                                           #//
//###########################################################################//

TEST_CASE("Test triangle_center() function for 'double' type.", "Vector3D geometry") {

    using std::string;
    using Vec3D = Vector3D<double>;

    Vec3D::set_eps(1E-7);
    Vec3D r1 = {1.0, 0.0, 0.0};
    Vec3D r2 = {0.0, 1.0, 0.0};
    Vec3D r3 = {0.0, 0.0, 1.0};

    Vec3D expected = {1.0/3.0,
                      1.0/3.0,
                      1.0/3.0};

    Vec3D actual = triangle_center(r1, r2, r3);

    double eps = 1E-14;

    REQUIRE( fabs(expected.x() - actual.x()) < eps );
    REQUIRE( fabs(expected.y() - actual.y()) < eps );
    REQUIRE( fabs(expected.z() - actual.z()) < eps );

}

TEST_CASE("Test triangle_center() function for 'multiprecision' type.", "Vector3D geometry") {

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
    Vec3D expected = {mpreal(1.0)/mpreal(3.0),
                      mpreal(1.0)/mpreal(3.0),
                      mpreal(1.0)/mpreal(3.0)};

    Vec3D actual = triangle_center(r1, r2, r3);

    REQUIRE( abs(expected.x() - actual.x()) < eps );
    REQUIRE( abs(expected.y() - actual.y()) < eps );
    REQUIRE( abs(expected.z() - actual.z()) < eps );

}
