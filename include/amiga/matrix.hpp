//
// Created by Lesleis Nagy on 24/05/2025.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <iomanip>
#include <array>

namespace amiga {
template<typename T, size_t N>
class Matrix {
  public:
    static inline size_t width = 20;
    static inline size_t precision = 15;

    /**
     * Default constructor creates a zero matrix.
     */
    Matrix() {
    }

    /**
     * Constructor to create `value` on the diagona.
     * @param value the diagonal value.
     */
    explicit
    Matrix(T value) {
      data_ = {};
      for (size_t i = 0; i < N; i++) {
        data_[i][i] = value;
      }
    }

    /**
     * Constructor to create a matrix from an input array with N^2 values.
     * @param value the input array.
     */
    explicit
    Matrix(const std::array<T, N * N>& value) {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] = value[i * N + j];
        }
      }
    }

    /**
     * Constructor to create a matrix from an input N x N array.
     * @param value the input array.
     */
    explicit
    Matrix(const std::array<std::array<T, N>, N>& value)
      : data_(std::move(value)) {
    }

    /**
     * Constructor to create a matrix from a linear (N^2) initialiser list.
     * @param value the input initialiser list.
     */
    Matrix(std::initializer_list<T> value) {
      if (value.size() != N * N) {
        throw std::invalid_argument("Matrix initializer list must have exactly N*N elements");
      }
      auto it = value.begin();
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] = *it++;
        }
      }
    }

    /**
     * Constructor to create a matrix from an N by N initialiser list.
     * @param value the input initialiser list.
     */
    Matrix(std::initializer_list<std::initializer_list<T> > value) {
      if (value.size() != N)
        throw std::invalid_argument("Outer initializer_list must have N rows");
      std::size_t row = 0;
      for (const auto& r : value) {
        if (r.size() != N)
          throw std::invalid_argument("Each row must have N columns");
        std::copy(r.begin(), r.end(), data_[row].begin());
        ++row;
      }
    }

    /**
     * Copy constructor.
     * @param rhs the right value to copy.
     */
    Matrix(const Matrix& rhs) {
      data_ = rhs.data_;
    }

    /**
     * Assignment operator.
     * @param rhs the right value to copy.
     * @return reference to the copied object.
     */
    Matrix& operator=(const Matrix& rhs) {
      if (this != &rhs) {
        data_ = rhs.data_;
      }
      return *this;
    }

    Matrix operator+(const Matrix& rhs) const {
      Matrix result = *this;
      result += rhs;
      return result;
    }

    Matrix& operator+=(const Matrix& rhs) {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] += rhs.data_[i][j];
        }
      }
      return *this;
    }

    Matrix operator-(const Matrix& rhs) const {
      Matrix result = *this;
      result -= rhs;
      return result;
    }

    Matrix& operator-=(const Matrix& rhs) {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] -= rhs.data_[i][j];
        }
      }
      return *this;
    }

    Matrix& operator*=(T scalar) {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] *= scalar;
        }
      }
      return *this;
    }

    Matrix operator*(T scalar) const {
      Matrix result = *this;
      result *= scalar;
      return result;
    }

    Matrix& operator/=(T scalar) {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data_[i][j] /= scalar;
        }
      }
      return *this;
    }

    Matrix operator/(T scalar) const {
      Matrix result = *this;
      result /= scalar;
      return result;
    }

    Matrix operator*(const Matrix& rhs) const {
      Matrix result;

      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          result.data_[i][j] = T(0);
          for (std::size_t k = 0; k < N; ++k) {
            result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
          }
        }
      }

      return result;
    }

    Matrix transpose() const {
      Matrix result;
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          result.data_[i][j] = data_[j][i];
        }
      }
      return result;
    }

    Matrix<T, N - 1> minor(std::size_t row, std::size_t col) const {
      Matrix<T, N - 1> result;
      std::size_t r = 0;

      for (std::size_t i = 0; i < N; ++i) {
        if (i == row) continue;
        std::size_t c = 0;
        for (std::size_t j = 0; j < N; ++j) {
          if (j == col) continue;
          result[r][c] = data_[i][j];
          ++c;
        }
        ++r;
      }

      return result;
    }

    //*******************************************************************************************//
    //* Static member functions                                                                 *//
    //*******************************************************************************************//

    friend Matrix operator*(T scalar, const Matrix& mat) {
      return mat * scalar;
    }

    /**
     * Stream operator creates a stream version of this object.
     * @param os the output stream to write to.
     * @param matrix the matrix to write.
     * @return a reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
      using namespace std;

      for (const auto& row : matrix.data_) {
        for (const auto& val : row) {
          os << setw(Matrix::width)
              << setprecision(Matrix::precision)
              << std::scientific
              << val
              << "  ";
        }
        os << std::endl;
      }
      return os;
    }

  private:
    std::array<std::array<T, N>, N> data_ = {};
};
} // namespace amiga

#endif //MATRIX_HPP
