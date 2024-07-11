//
// Created by Lesleis Nagy on 05/07/2024.
//

#ifndef LIBFABBRI_INCLUDE_B_FIELD_CALCULATOR_HPP_
#define LIBFABBRI_INCLUDE_B_FIELD_CALCULATOR_HPP_

#include "fabbri.hpp"
#include "model.hpp"

class BFieldCalculator {

 public:

  BFieldCalculator(const Model<3> &model) {

    _b_field_parts.resize(model.mesh().cil().size());

    for (int i = 0; i < model.mesh().cil().size(); ++i) {

      const auto &tet = model.mesh().cil()[i];

      // Get tet corner vertices.
      const auto &r0 = model.mesh().vcl()[tet[0]];
      const auto &r1 = model.mesh().vcl()[tet[1]];
      const auto &r2 = model.mesh().vcl()[tet[2]];
      const auto &r3 = model.mesh().vcl()[tet[3]];

      // Get tet corner (magnetization) fields.
      const auto &m0 = model.field_list().fields()[0].vectors()[tet[0]];
      const auto &m1 = model.field_list().fields()[0].vectors()[tet[1]];
      const auto &m2 = model.field_list().fields()[0].vectors()[tet[2]];
      const auto &m3 = model.field_list().fields()[0].vectors()[tet[3]];

      std::array<double, 3> m = {
          (m0[0] + m1[0] + m2[0] + m3[0]) / 4.0,
          (m0[1] + m1[1] + m2[1] + m3[1]) / 4.0,
          (m0[2] + m1[2] + m2[2] + m3[2]) / 4.0
      };

      double len = sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);

      m[0] /= len;
      m[1] /= len;
      m[2] /= len;

      _b_field_parts[i] = new_uni_tet_B_fun<double>(
          {m[0], m[1], m[2]},
          {r0[0], r0[1], r0[2]},
          {r1[0], r1[1], r1[2]},
          {r2[0], r1[1], r1[2]},
          {r3[0], r1[1], r1[2]}
      );

    }

  }

  Vector3D<double> operator()(const Vector3D<double> &r) {

    Vector3D<double> b = {0.0, 0.0, 0.0};

    for (const auto &b_field_part : _b_field_parts) {

      b = b + b_field_part(r);

    }

    return b;

  }

 private:

  std::vector<PosToVectorMap<double>> _b_field_parts;

};

#endif //LIBFABBRI_INCLUDE_B_FIELD_CALCULATOR_HPP_
