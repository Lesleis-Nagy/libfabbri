//
// Created by Lesleis Nagy on 20/03/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

#include <geometry.hpp>
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

//###########################################################################//
//# Test geometry 3D axis/angle rotation.                                   #//
//###########################################################################//

TEST_CASE("rotation3x3_double",
          "Test the rotation3x3 function for 'double' precision.") {

  double eps = 1E-14;

  Vector3D<double> v = {1.0, 2.0, 3.0};
  double theta = M_PI / 3.0;

  auto mat = rotation3x3(v, theta);

  Matrix3x3<double> expected = {

      // First row
      {0.535714285714285714290,
       -0.62293650340084216760,
       0.570052907029132873640},

      // Second row
      {0.765793646257985024750,
       0.64285714285714285714,
       -0.017169310657423579677},

      // Third row
      {-0.35576719274341858793,
       0.44574073922885215111,
       0.821428571428571428570}

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);

}

TEST_CASE("rotation3x3_mpreal",
          "Test the rotation3x3 function for 'mpreal [50]' precision.") {

  using mpfr::mpreal;

  const int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  mpreal eps{1E-16};

  Vector3D<mpreal>::set_eps(0.0);
  Vector3D<mpreal> v = {mpreal{1.0}, mpreal{2.0}, mpreal{3.0}};
  mpreal theta = mpreal{mpfr::const_pi()} / mpreal{3.0};

  auto mat = rotation3x3(v, theta);

  Matrix3x3<mpreal> expected = {

      // First row
      {mpreal{0.535714285714285714290},
       mpreal{-0.62293650340084216760},
       mpreal{0.570052907029132873640}},

      // Second row
      {mpreal{0.765793646257985024750},
       mpreal{0.64285714285714285714},
       mpreal{-0.017169310657423579677}},

      // third row
      {mpreal{-0.35576719274341858793},
       mpreal{0.44574073922885215111},
       mpreal{0.821428571428571428570}}

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);

}

//###########################################################################//
//# Test geometry 3D axis/angle rotation (homogenous matrix).               #//
//###########################################################################//

TEST_CASE("rotation4x4_double",
          "Test the rotation4x4 function for 'double' precision.") {

  double eps = 1E-14;

  Vector3D<double> v = {1.0, 2.0, 3.0};
  double theta = M_PI / 3.0;

  auto mat = rotation4x4(v, theta);

  Matrix4x4<double> expected = {

      // First row
      {
          0.535714285714285714290,
          -0.62293650340084216760,
          0.570052907029132873640,
          0.0
      },


      // Second row
      {
          0.765793646257985024750,
          0.64285714285714285714,
          -0.017169310657423579677,
          0.0
      },

      // third row
      {
          -0.35576719274341858793,
          0.44574073922885215111,
          0.821428571428571428570,
          0.0
      },

      // Fourth row
      {
          0.0,
          0.0,
          0.0,
          1.0
      }

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);
  REQUIRE(abs(mat(0, 3) - expected(0, 3)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);
  REQUIRE(abs(mat(1, 3) - expected(1, 3)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);
  REQUIRE(abs(mat(2, 3) - expected(2, 3)) < eps);

  REQUIRE(abs(mat(3, 0) - expected(3, 0)) < eps);
  REQUIRE(abs(mat(3, 1) - expected(3, 1)) < eps);
  REQUIRE(abs(mat(3, 2) - expected(3, 2)) < eps);
  REQUIRE(abs(mat(3, 3) - expected(3, 3)) < eps);

}

TEST_CASE("rotation4x4_mpreal",
          "Test the rotation4x4 function for 'mpreal [50]' precision.") {

  using mpfr::mpreal;

  const int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  mpreal eps{1E-16};

  Vector3D<mpreal>::set_eps(0.0);
  Vector3D<mpreal> v = {mpreal{1.0}, mpreal{2.0}, mpreal{3.0}};
  mpreal theta = mpreal{mpfr::const_pi()} / mpreal{3.0};

  auto mat = rotation4x4(v, theta);

  Matrix4x4<mpreal> expected = {

      // First row
      {
          mpreal{0.535714285714285714290},
          mpreal{-0.62293650340084216760},
          mpreal{0.570052907029132873640},
          mpreal{0.0}
      },


      // Second row
      {
          mpreal{0.765793646257985024750},
          mpreal{0.64285714285714285714},
          mpreal{-0.017169310657423579677},
          mpreal{0.0}
      },

      // third row
      {
          mpreal{-0.35576719274341858793},
          mpreal{0.44574073922885215111},
          mpreal{0.821428571428571428570},
          mpreal{0.0}
      },

      // Fourth row
      {
          mpreal{0.0},
          mpreal{0.0},
          mpreal{0.0},
          mpreal{1.0}
      }

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);
  REQUIRE(abs(mat(0, 3) - expected(0, 3)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);
  REQUIRE(abs(mat(1, 3) - expected(1, 3)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);
  REQUIRE(abs(mat(2, 3) - expected(2, 3)) < eps);

  REQUIRE(abs(mat(3, 0) - expected(3, 0)) < eps);
  REQUIRE(abs(mat(3, 1) - expected(3, 1)) < eps);
  REQUIRE(abs(mat(3, 2) - expected(3, 2)) < eps);
  REQUIRE(abs(mat(3, 3) - expected(3, 3)) < eps);

}

TEST_CASE("rotation4x4_double_4d",
          "Test the rotation4x4 function for 'double' precision.") {

  double eps = 1E-14;

  Vector4D<double> v = {1.0, 2.0, 3.0, 1.0};
  double theta = M_PI / 3.0;

  auto mat = rotation4x4(v, theta);

  Matrix4x4<double> expected = {

      // First row
      {
          0.535714285714285714290,
          -0.62293650340084216760,
          0.570052907029132873640,
          0.0
      },


      // Second row
      {
          0.765793646257985024750,
          0.64285714285714285714,
          -0.017169310657423579677,
          0.0
      },

      // third row
      {
          -0.35576719274341858793,
          0.44574073922885215111,
          0.821428571428571428570,
          0.0
      },

      // Fourth row
      {
          0.0,
          0.0,
          0.0,
          1.0
      }

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);
  REQUIRE(abs(mat(0, 3) - expected(0, 3)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);
  REQUIRE(abs(mat(1, 3) - expected(1, 3)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);
  REQUIRE(abs(mat(2, 3) - expected(2, 3)) < eps);

  REQUIRE(abs(mat(3, 0) - expected(3, 0)) < eps);
  REQUIRE(abs(mat(3, 1) - expected(3, 1)) < eps);
  REQUIRE(abs(mat(3, 2) - expected(3, 2)) < eps);
  REQUIRE(abs(mat(3, 3) - expected(3, 3)) < eps);

}

TEST_CASE("rotation4x4_mpreal_4d",
          "Test the rotation4x4 function for 'mpreal [50]' precision.") {

  using mpfr::mpreal;

  const int digits = 50;
  mpreal::set_default_prec(mpfr::digits2bits(digits));

  mpreal eps{1E-16};

  Vector4D<mpreal>::set_eps(0.0);
  Vector4D<mpreal> v = {mpreal{1}, mpreal{2}, mpreal{3}, mpreal{1}};
  mpreal theta = mpreal{mpfr::const_pi()} / mpreal{3};

  auto mat = rotation4x4(v, theta);

  Matrix4x4<mpreal> expected = {

      // First row
      {
          mpreal{0.535714285714285714290},
          mpreal{-0.62293650340084216760},
          mpreal{0.570052907029132873640},
          mpreal{0.0}
      },


      // Second row
      {
          mpreal{0.765793646257985024750},
          mpreal{0.64285714285714285714},
          mpreal{-0.017169310657423579677},
          mpreal{0.0}
      },

      // third row
      {
          mpreal{-0.35576719274341858793},
          mpreal{0.44574073922885215111},
          mpreal{0.821428571428571428570},
          mpreal{0.0}
      },

      // Fourth row
      {
          mpreal{0.0},
          mpreal{0.0},
          mpreal{0.0},
          mpreal{1.0}
      }

  };

  REQUIRE(abs(mat(0, 0) - expected(0, 0)) < eps);
  REQUIRE(abs(mat(0, 1) - expected(0, 1)) < eps);
  REQUIRE(abs(mat(0, 2) - expected(0, 2)) < eps);
  REQUIRE(abs(mat(0, 3) - expected(0, 3)) < eps);

  REQUIRE(abs(mat(1, 0) - expected(1, 0)) < eps);
  REQUIRE(abs(mat(1, 1) - expected(1, 1)) < eps);
  REQUIRE(abs(mat(1, 2) - expected(1, 2)) < eps);
  REQUIRE(abs(mat(1, 3) - expected(1, 3)) < eps);

  REQUIRE(abs(mat(2, 0) - expected(2, 0)) < eps);
  REQUIRE(abs(mat(2, 1) - expected(2, 1)) < eps);
  REQUIRE(abs(mat(2, 2) - expected(2, 2)) < eps);
  REQUIRE(abs(mat(2, 3) - expected(2, 3)) < eps);

  REQUIRE(abs(mat(3, 0) - expected(3, 0)) < eps);
  REQUIRE(abs(mat(3, 1) - expected(3, 1)) < eps);
  REQUIRE(abs(mat(3, 2) - expected(3, 2)) < eps);
  REQUIRE(abs(mat(3, 3) - expected(3, 3)) < eps);

}
