//
// Created by Lesleis Nagy on 26/05/2025.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>

namespace amiga {
template<typename T, size_t N>
class Matrix {
  public:
    explicit
    Matrix(const std::array<std::array<T, N>, N>& m)
      : data_(m) {
    }
  private:
    std::array<std::array<T, N>, N> data_;
};
} // namespace amiga

#endif //MATRIX_HPP
