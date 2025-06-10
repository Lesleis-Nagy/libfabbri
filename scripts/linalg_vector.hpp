#include <array>
#include <cstddef>


/*-----------------------------------------------------------------------------------------------*/
/* Regularization class                                                                          */
/*-----------------------------------------------------------------------------------------------*/


template<typename T, size_t REG>
struct RegularizationEps {
  static T value() {
    if constexpr (std::is_arithmetic_v<T>) {
      return static_cast<T>(std::pow(10.0, -static_cast<int>(REG)));
    } else {
      return T(1) / pow(T(10), REG);
    }
  }
};


/*-----------------------------------------------------------------------------------------------*/
/* Primary class declaration                                                                     */
/*-----------------------------------------------------------------------------------------------*/


template <typename T, size_t N, size_t REG_PREC=10, typename Enable = void>
class Vector;


/*-----------------------------------------------------------------------------------------------*/
/* Constexpr class for arithmetic types                                                          */
/*-----------------------------------------------------------------------------------------------*/


template <typename T, size_t REG_PREC>
class Vector<T, 2, REG_PREC, std::enable_if_t<std::is_arithmetic_v<T>>> {

  // Make sure T is an arithmetic type otherwise fail to compile.
  static_assert(
    std::is_arithmetic_v<T>,
    "T must be an arithmetic type (int, float, double...)"
  );

public:
  /**
   * Default constructor generates the 2 component zero vector.
   */
  constexpr Vector() {
    for(size_t i = 0; i < 2; ++i)
      data_[i] = 0;
  }

  /**
   * Initializer constructor generates the 2 component vector.
   * @param initializer list the components of the new vector.
   */
  constexpr Vector(std::initializer_list<T> list) {
    if (list.size() != 2) {
      throw std::invalid_argument("Initializer list must have exactly N elements");
    }
    size_t i = 0;
    for (T value : list) {
      data_[i++] = value;
    }
  }

  /**
   * Vector element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  constexpr T&
  operator()(size_t i) {
    return data_[i];
  }

  /**
   * Vector element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  constexpr const T&
  operator()(size_t i) const {
    return data_[i];
  }

  /**
   * Vector (array-style) element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  constexpr T&
  operator[](size_t i) {
    return data_[i];
  }

  /**
   * Vector (array-style) element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  constexpr const T&
  operator[](size_t i) const {
    return data_[i];
  }

  /**
   * Vector copy-assignment.
   * @param other the right-hand side vector of the assignment.
   * @return a constant reference to the assigned value.
   */
  constexpr Vector&
  operator=(const Vector& other) {
    if (this != &other) {
      for (size_t i = 0; i < 2; ++i)
        data_[i] = other(i);
    }
    return *this;
  }

  /**
   * Vector-vector sum operator.
   * @param u the vector on the left-hand side of the sum.
   * @param v the vector on the right-hand side of the sum.
   * @return the sum of vectors u + v.
   */
  friend constexpr Vector
  operator+(const Vector& u, const Vector& v) {
    Vector w;
    w(0) = u(0) + v(0);
    w(1) = u(1) + v(1);
    return w;
  }

  /**
   * Vector-vector difference operator.
   * @param u the vector on the left-hand side of the difference.
   * @param v the vector on the right-hand side of the difference.
   * @return the vector difference u - v.
   */
  friend constexpr Vector
  operator-(const Vector& u, const Vector& v) {
    Vector w;
    w(0) = u(0) - v(0);
    w(1) = u(1) - v(1);
    return w;
  }

  /**
   * Vector negation operator.
   * @param u the vector to negate.
   * @return the vector negation -u.
   */
  friend constexpr Vector
  operator-(const Vector& u) {
    Vector v;
    v(0) = -u(0);
    v(1) = -u(1);
    return v;
  }

  /**
   * Scalar-vector product operator.
   * @param alpha the scalar on the left-hand side of the product.
   * @param u the vector on the right-hand side of the product.
   * @return the scalar-vector alpha*u.
   */
  friend constexpr Vector
  operator*(T alpha, const Vector& u) {
    Vector v;
    v(0) = alpha*u(0);
    v(1) = alpha*u(1);
    return v;
  }

  /**
   * Vector-scalar product operator.
   * @param u the vector on the left-hand side of the product.
   * @param alpha the scalar on the right-hand side of the product.
   * @return the vector-scalar product u*alpha.
   */
  friend constexpr Vector
  operator*(const Vector& u, T alpha) {
    return alpha * u;
  }

  /**
   * Vector-scalar division operator.
   * @param u the vector on the left-hand side of the division.
   * @param alpha the scalar on the right-hand side of the division.
   * @return the vector-scalar division u / alpha.
   */
  friend constexpr Vector
  operator/(const Vector& u, T alpha) {
    Vector v;
    v(0) = u(0)/alpha;
    v(1) = u(1)/alpha;
    return v;
  }

  /**
   * In-place vector addition.
   * @param v the vector that will be added to this vector.
   * @return a reference to the updated vector (*this).
   */
  constexpr Vector& operator+=(const Vector& v) {
    data_[0] += v(0);
    data_[1] += v(1);
    return *this;
  }

  /**
   * In-place vector difference.
   * @param v the vector that will be subtracted from this vector.
   * @return a reference to the updated vector (*this).
   */
  constexpr Vector& operator-=(const Vector& v) {
    data_[0] -= v(0);
    data_[1] -= v(1);
    return *this;
  }

  /**
   * In-place vector-scalar product.
   * @param alpha the scalar that will multiply this vector.
   * @return a reference to the updated vector (*this).
   */
  constexpr Vector& operator*=(T alpha) {
    data_[0] *= alpha;
    data_[1] *= alpha;
    return *this;
  }

  /**
   * In-place vector-scalar division.
   * @param alpha the scalar that will divide this vector.
   * @return a reference to the updated vector (*this).
   */
  constexpr Vector& operator/=(T alpha) {
    data_[0] /= alpha;
    data_[1] /= alpha;
    return *this;
  }

  const T eps = RegularizationEps<T, REG_PREC>::value();
  const T eps_squared = eps * eps;

private:
  std::array<T, 2> data_{};
};

/**
 * Vector dot product.
 * @param u the vector on the left-hand side of the dot product.
 * @param v the vector on the right-hand side of the dot product.
 * @return the vector dot product u . v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr T
dot(const Vector<T, 2, REG_PREC>& u, const Vector<T, 2, REG_PREC>& v) {
  return u(0)*v(0) + u(1)*v(1);
}

/**
 * Vector cross-product.
 * @param u0 the 0th vector of the cross-product.
 * @return the vector cross-product u0.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr Vector<T, 2, REG_PREC>
cross(const Vector<T, 2, REG_PREC>& u0) {
  Vector<T, 2, REG_PREC> cross;
  cross(0) = -u0(1);
  cross(1) = u0(0);
  return cross;
}

/**
 * Vector norm.
 * @param u the vector for which we seek the norm/length.
 * @return the vector norm. v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr T
norm(const Vector<T, 2, REG_PREC>& u) {
  return sqrt(dot(u,u));
}

/**
 * Regularized vector norm.
 * @param u the vector for which we seek the regularlised norm/length.
 * @return the regularised vector norm. v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr T
rnorm(const Vector<T, 2, REG_PREC>& u) {
  return sqrt(dot(u,u) + u.eps_squared);
}

/**
 * Normalize a vector.
 * @param u the vector which we seek to normalize.
 * @return the normalized vector.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr Vector<T, 2, REG_PREC>
normalize(const Vector<T, 2, REG_PREC>& u) {
  return u / norm(u);
}

/**
 * Normalize (with regularization) a vector.
 * @param u the vector which we seek to normalize.
 * @return the normalized vector.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr Vector<T, 2, REG_PREC>
rnormalize(const Vector<T, 2, REG_PREC>& u) {
  return u / rnorm(u);
}


/*-----------------------------------------------------------------------------------------------*/
/* Class for general types                                                                       */
/*-----------------------------------------------------------------------------------------------*/


template <typename T, size_t REG_PREC>
class Vector<T, 2, REG_PREC, std::enable_if_t<!std::is_arithmetic_v<T>>> {

public:
  /**
   * Default constructor generates the 2 component zero vector.
   */
  Vector() {
    for(size_t i = 0; i < 2; ++i)
      data_[i] = 0;
  }

  /**
   * Initializer constructor generates the 2 component vector.
   * @param initializer list the components of the new vector.
   */
  Vector(std::initializer_list<T> list) {
    if (list.size() != 2) {
      throw std::invalid_argument("Initializer list must have exactly N elements");
    }
    size_t i = 0;
    for (T value : list) {
      data_[i++] = value;
    }
  }

  /**
   * Vector element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  T&
  operator()(size_t i) {
    return data_[i];
  }

  /**
   * Vector element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  const T&
  operator()(size_t i) const {
    return data_[i];
  }

  /**
   * Vector (array-style) element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  T&
  operator[](size_t i) {
    return data_[i];
  }

  /**
   * Vector (array-style) element access.
   * @param i the i-th element of the vector.
   * @return the vector element at index i.
   */
  const T&
  operator[](size_t i) const {
    return data_[i];
  }

  /**
   * Vector copy-assignment.
   * @param other the right-hand side vector of the assignment.
   * @return a constant reference to the assigned value.
   */
  Vector&
  operator=(const Vector& other) {
    if (this != &other) {
      for (size_t i = 0; i < 2; ++i)
        data_[i] = other(i);
    }
    return *this;
  }

  /**
   * Vector-vector sum operator.
   * @param u the vector on the left-hand side of the sum.
   * @param v the vector on the right-hand side of the sum.
   * @return the sum of vectors u + v.
   */
  friend Vector
  operator+(const Vector& u, const Vector& v) {
    Vector w;
    w(0) = u(0) + v(0);
    w(1) = u(1) + v(1);
    return w;
  }

  /**
   * Vector-vector difference operator.
   * @param u the vector on the left-hand side of the difference.
   * @param v the vector on the right-hand side of the difference.
   * @return the vector difference u - v.
   */
  friend Vector
  operator-(const Vector& u, const Vector& v) {
    Vector w;
    w(0) = u(0) - v(0);
    w(1) = u(1) - v(1);
    return w;
  }

  /**
   * Vector negation operator.
   * @param u the vector to negate.
   * @return the vector negation -u.
   */
  friend Vector
  operator-(const Vector& u) {
    Vector v;
    v(0) = -u(0);
    v(1) = -u(1);
    return v;
  }

  /**
   * Scalar-vector product operator.
   * @param alpha the scalar on the left-hand side of the product.
   * @param u the vector on the right-hand side of the product.
   * @return the scalar-vector alpha*u.
   */
  friend Vector
  operator*(T alpha, const Vector& u) {
    Vector v;
    v(0) = alpha*u(0);
    v(1) = alpha*u(1);
    return v;
  }

  /**
   * Vector-scalar product operator.
   * @param u the vector on the left-hand side of the product.
   * @param alpha the scalar on the right-hand side of the product.
   * @return the vector-scalar product u*alpha.
   */
  friend Vector
  operator*(const Vector& u, T alpha) {
    return alpha * u;
  }

  /**
   * Vector-scalar division operator.
   * @param u the vector on the left-hand side of the division.
   * @param alpha the scalar on the right-hand side of the division.
   * @return the vector-scalar division u / alpha.
   */
  friend Vector
  operator/(const Vector& u, T alpha) {
    Vector v;
    v(0) = u(0)/alpha;
    v(1) = u(1)/alpha;
    return v;
  }

  /**
   * In-place vector addition.
   * @param v the vector that will be added to this vector.
   * @return a reference to the updated vector (*this).
   */
  Vector& operator+=(const Vector& v) {
    data_[0] += v(0);
    data_[1] += v(1);
    return *this;
  }

  /**
   * In-place vector difference.
   * @param v the vector that will be subtracted from this vector.
   * @return a reference to the updated vector (*this).
   */
  Vector& operator-=(const Vector& v) {
    data_[0] -= v(0);
    data_[1] -= v(1);
    return *this;
  }

  /**
   * In-place vector-scalar product.
   * @param alpha the scalar that will multiply this vector.
   * @return a reference to the updated vector (*this).
   */
  Vector& operator*=(T alpha) {
    data_[0] *= alpha;
    data_[1] *= alpha;
    return *this;
  }

  /**
   * In-place vector-scalar division.
   * @param alpha the scalar that will divide this vector.
   * @return a reference to the updated vector (*this).
   */
  Vector& operator/=(T alpha) {
    data_[0] /= alpha;
    data_[1] /= alpha;
    return *this;
  }

  const T eps = RegularizationEps<T, REG_PREC>::value();
  const T eps_squared = eps * eps;

private:
  std::array<T, 2> data_{};
};

/**
 * Vector dot product.
 * @param u the vector on the left-hand side of the dot product.
 * @param v the vector on the right-hand side of the dot product.
 * @return the vector dot product u . v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
T
dot(const Vector<T, 2, REG_PREC>& u, const Vector<T, 2, REG_PREC>& v) {
  return u(0)*v(0) + u(1)*v(1);
}

/**
 * Vector cross-product.
 * @param u0 the 0th vector of the cross-product.
 * @return the vector cross-product u0.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
Vector<T, 2, REG_PREC>
cross(const Vector<T, 2, REG_PREC>& u0) {
  Vector<T, 2, REG_PREC> cross;
  cross(0) = -u0(1);
  cross(1) = u0(0);
  return cross;
}

/**
 * Vector norm.
 * @param u the vector for which we seek the norm/length.
 * @return the vector norm. v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
T
norm(const Vector<T, 2, REG_PREC>& u) {
  return sqrt(dot(u,u));
}

/**
 * Regularized vector norm.
 * @param u the vector for which we seek the regularlised norm/length.
 * @return the regularised vector norm. v
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
T
rnorm(const Vector<T, 2, REG_PREC>& u) {
  return sqrt(dot(u,u) + u.eps_squared);
}

/**
 * Normalize a vector.
 * @param u the vector which we seek to normalize.
 * @return the normalized vector.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
Vector<T, 2, REG_PREC>
normalize(const Vector<T, 2, REG_PREC>& u) {
  return u / norm(u);
}

/**
 * Normalize (with regularization) a vector.
 * @param u the vector which we seek to normalize.
 * @return the normalized vector.
 */
template <typename T, size_t REG_PREC,
          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
Vector<T, 2, REG_PREC>
rnormalize(const Vector<T, 2, REG_PREC>& u) {
  return u / rnorm(u);
}
