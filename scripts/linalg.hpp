#include <array>
#include <cstddef>


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


/**
 * The primary class declaration for Vector.
 */
template <typename T, size_t N, size_t REG_PREC=10, typename Enable = void>
class Vector;


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
   * Vector assignment.
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
   * Vector assignment.
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
