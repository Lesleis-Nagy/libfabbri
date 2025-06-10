#!/bin/zsh

# 
# This is a code to generate a linear algebra library for small dense matrices.
#

import re
import sys
import textwrap

import sympy as sy


def mat_indexify(name: str) -> str:
    regex_symbol = re.compile(r"^([A-Za-z0-9]+)_([0-9]+)_([0-9]+)$")
    match_symbol = regex_symbol.match(name)
    if match_symbol:
        base, i, j = match_symbol.groups()
        return f"{base}({i}, {j})"
    return name


def vec_indexify(name: str) -> str:
    regex_symbol = re.compile(r"^([A-Za-z0-9]+)_([0-9]+)$")
    match_symbol = regex_symbol.match(name)
    if match_symbol:
        base, i = match_symbol.groups()
        return f"{base}({i})"
    return name


##################################################################################################
# Includes                                                                                       #
##################################################################################################


def gen_includes(prefix="  "):
    code = ""

    code += f"{0*prefix}#include <array>\n"
    code += f"{0*prefix}#include <cstddef>"

    code += "\n\n"

    return code


##################################################################################################
# Regularization                                                                                 #
##################################################################################################


def gen_regularization(prefix="  "):
    code = ""

    code += f"{0*prefix}template<typename T, size_t REG>\n"
    code += f"{0*prefix}struct RegularizationEps {{\n"
    code += f"{1*prefix}static T value() {{\n"
    code += f"{2*prefix}if constexpr (std::is_arithmetic_v<T>) {{\n"
    code += f"{3*prefix}return static_cast<T>(std::pow(10.0, -static_cast<int>(REG)));\n"
    code += f"{2*prefix}}} else {{\n"
    code += f"{3*prefix}return T(1) / pow(T(10), REG);\n"
    code += f"{2*prefix}}}\n"
    code += f"{1*prefix}}}\n"
    code += f"{0*prefix}}};"

    code += "\n\n"

    return code


##################################################################################################
# vector generation                                                                              #
##################################################################################################


def gen_vector_class_primary(prefix="  "):
    code = ""

    code += f"{0*prefix}template <typename T, size_t N, size_t REG_PREC=10, typename Enable = void>\n"
    code += f"{0*prefix}class Vector;"

    code += "\n\n"

    return code


##################################################################################################
# vector generation                                                                              #
##################################################################################################


def gen_vector_default_constructor(n, arithmetic, prefix="  "):
    code = ""

    # The default constructor creates the unit matrix
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Default constructor generates the {n} component zero vector.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector() {{\n"
    else:
        code += f"{0*prefix}Vector() {{\n"

    code += f"{1*prefix}for(size_t i = 0; i < {n}; ++i)\n"
    code += f"{2*prefix}data_[i] = 0;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_initializer_constructor(n, arithmetic, prefix="  "):
    code = ""

    # The default initializer creates a user specified vector
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Initializer constructor generates the {n} component vector.\n"
    code += f"{0*prefix} * @param initializer list the components of the new vector.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector(std::initializer_list<T> list) {{\n"
    else:
        code += f"{0*prefix}Vector(std::initializer_list<T> list) {{\n"

    code += f"{1*prefix}if (list.size() != {n}) {{\n"
    code += f"{2*prefix}throw std::invalid_argument(\"Initializer list must have exactly N elements\");\n"
    code += f"{1*prefix}}}\n"


    code += f"{1*prefix}size_t i = 0;\n"
    code += f"{1*prefix}for (T value : list) {{\n"
    code += f"{2*prefix}data_[i++] = value;\n"
    code += f"{1*prefix}}}\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_access(n, arithmetic, prefix="  "):
    code = ""

    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector element access.\n"
    code += f"{0*prefix} * @param i the i-th element of the vector.\n"
    code += f"{0*prefix} * @return the vector element at index i.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr T&\n"
    else:
        code += f"{0*prefix}T&\n"

    code += f"{0*prefix}operator()(size_t i) {{\n"
    code += f"{1*prefix}return data_[i];\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_array_access(n, arithmetic, prefix="  "):
    code = ""

    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector (array-style) element access.\n"
    code += f"{0*prefix} * @param i the i-th element of the vector.\n"
    code += f"{0*prefix} * @return the vector element at index i.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr T&\n"
    else:
        code += f"{0*prefix}T&\n"

    code += f"{0*prefix}operator[](size_t i) {{\n"
    code += f"{1*prefix}return data_[i];\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_const_access(n, arithmetic, prefix="  "):
    code = ""

    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector element access.\n"
    code += f"{0*prefix} * @param i the i-th element of the vector.\n"
    code += f"{0*prefix} * @return the vector element at index i.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr const T&\n"
    else:
        code += f"{0*prefix}const T&\n"

    code += f"{0*prefix}operator()(size_t i) const {{\n"
    code += f"{1*prefix}return data_[i];\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_array_const_access(n, arithmetic, prefix="  "):
    code = ""

    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector (array-style) element access.\n"
    code += f"{0*prefix} * @param i the i-th element of the vector.\n"
    code += f"{0*prefix} * @return the vector element at index i.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr const T&\n"
    else:
        code += f"{0*prefix}const T&\n"

    code += f"{0*prefix}operator[](size_t i) const {{\n"
    code += f"{1*prefix}return data_[i];\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_assign(n, arithmetic, prefix="  "):
    code = ""

    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector copy-assignment.\n"
    code += f"{0*prefix} * @param other the right-hand side vector of the assignment.\n"
    code += f"{0*prefix} * @return a constant reference to the assigned value.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector&\n"
    else:
        code += f"{0*prefix}Vector&\n"

    code += f"{0*prefix}operator=(const Vector& other) {{\n"
    code += f"{1*prefix}if (this != &other) {{\n"
    code += f"{2*prefix}for (size_t i = 0; i < {n}; ++i)\n"
    code += f"{3*prefix}data_[i] = other(i);\n"
    code += f"{1*prefix}}}\n"
    code += f"{1*prefix}return *this;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_vector_sum(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))
    v = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"v_{i}"))

    w = u + v

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector-vector sum operator.\n"
    code += f"{0*prefix} * @param u the vector on the left-hand side of the sum.\n"
    code += f"{0*prefix} * @param v the vector on the right-hand side of the sum.\n"
    code += f"{0*prefix} * @return the sum of vectors u + v.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator+(const Vector& u, const Vector& v) {{\n"
    code += f"{1*prefix}Vector w;\n"

    for i in range(n):
        expr = w[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code += f"{1*prefix}w({i}) = {c_str};\n"

    code += f"{1*prefix}return w;\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_vector_difference(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))
    v = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"v_{i}"))

    w = u - v

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector-vector difference operator.\n"
    code += f"{0*prefix} * @param u the vector on the left-hand side of the difference.\n"
    code += f"{0*prefix} * @param v the vector on the right-hand side of the difference.\n"
    code += f"{0*prefix} * @return the vector difference u - v.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator-(const Vector& u, const Vector& v) {{\n"
    code += f"{1*prefix}Vector w;\n"

    for i in range(n):
        expr = w[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code += f"{1*prefix}w({i}) = {c_str};\n"

    code += f"{1*prefix}return w;\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_negation(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))

    v = -u

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector negation operator.\n"
    code += f"{0*prefix} * @param u the vector to negate.\n"
    code += f"{0*prefix} * @return the vector negation -u.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator-(const Vector& u) {{\n"
    code += f"{1*prefix}Vector v;\n"

    for i in range(n):
        expr = v[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code += f"{1*prefix}v({i}) = {c_str};\n"

    code += f"{1*prefix}return v;\n"

    code += f"{0*prefix}}}"

    return code


def gen_scalar_vector_prod(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))
    alpha = sy.symbols('alpha')

    v = alpha * u

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Scalar-vector product operator.\n"
    code += f"{0*prefix} * @param alpha the scalar on the left-hand side of the product.\n"
    code += f"{0*prefix} * @param u the vector on the right-hand side of the product.\n"
    code += f"{0*prefix} * @return the scalar-vector alpha*u.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator*(T alpha, const Vector& u) {{\n"
    code += f"{1*prefix}Vector v;\n"

    for i in range(n):
        expr = v[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code += f"{1*prefix}v({i}) = {c_str};\n"

    code += f"{1*prefix}return v;\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_prod(n, arithmetic, prefix="  "):
    code = ""

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector-scalar product operator.\n"
    code += f"{0*prefix} * @param u the vector on the left-hand side of the product.\n"
    code += f"{0*prefix} * @param alpha the scalar on the right-hand side of the product.\n"
    code += f"{0*prefix} * @return the vector-scalar product u*alpha.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator*(const Vector& u, T alpha) {{\n"

    code += f"{1*prefix}return alpha * u;\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_div(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))
    alpha = sy.symbols('alpha')

    v = u / alpha

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector-scalar division operator.\n"
    code += f"{0*prefix} * @param u the vector on the left-hand side of the division.\n"
    code += f"{0*prefix} * @param alpha the scalar on the right-hand side of the division.\n"
    code += f"{0*prefix} * @return the vector-scalar division u / alpha.\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}friend constexpr Vector\n"
    else:
        code += f"{0*prefix}friend Vector\n"

    code += f"{0*prefix}operator/(const Vector& u, T alpha) {{\n"
    code += f"{1*prefix}Vector v;\n"

    for i in range(n):
        expr = v[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code += f"{1*prefix}v({i}) = {c_str};\n"

    code += f"{1*prefix}return v;\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_inplace_sum(n, arithmetic, prefix="  "):
    code = ""

    # Generate c code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * In-place vector addition.\n"
    code += f"{0*prefix} * @param v the vector that will be added to this vector.\n"
    code += f"{0*prefix} * @return a reference to the updated vector (*this).\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector& operator+=(const Vector& v) {{\n"
    else:
        code += f"{0*prefix}Vector& operator+=(const Vector& v) {{\n"

    for i in range(n):
        code += f"{1*prefix}data_[{i}] += v({i});\n"

    code += f"{1*prefix}return *this;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_inplace_difference(n, arithmetic, prefix="  "):
    code = ""

    # Generate c code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * In-place vector difference.\n"
    code += f"{0*prefix} * @param v the vector that will be subtracted from this vector.\n"
    code += f"{0*prefix} * @return a reference to the updated vector (*this).\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector& operator-=(const Vector& v) {{\n"
    else:
        code += f"{0*prefix}Vector& operator-=(const Vector& v) {{\n"

    for i in range(n):
        code += f"{1*prefix}data_[{i}] -= v({i});\n"

    code += f"{1*prefix}return *this;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_product(n, arithmetic, prefix="  "):
    code = ""

    # Generate c code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * In-place vector-scalar product.\n"
    code += f"{0*prefix} * @param alpha the scalar that will multiply this vector.\n"
    code += f"{0*prefix} * @return a reference to the updated vector (*this).\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector& operator*=(T alpha) {{\n"
    else:
        code += f"{0*prefix}Vector& operator*=(T alpha) {{\n"

    for i in range(n):
        code += f"{1*prefix}data_[{i}] *= alpha;\n"

    code += f"{1*prefix}return *this;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_division(n, arithmetic, prefix="  "):
    code = ""

    # Generate c code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * In-place vector-scalar division.\n"
    code += f"{0*prefix} * @param alpha the scalar that will divide this vector.\n"
    code += f"{0*prefix} * @return a reference to the updated vector (*this).\n"
    code += f"{0*prefix} */\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector& operator/=(T alpha) {{\n"
    else:
        code += f"{0*prefix}Vector& operator/=(T alpha) {{\n"

    for i in range(n):
        code += f"{1*prefix}data_[{i}] /= alpha;\n"

    code += f"{1*prefix}return *this;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_dot_prod(n, arithmetic, prefix="  "):
    code = ""

    u = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"u_{i}"))
    v = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"v_{i}"))

    w = u.dot(v)

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector dot product.\n"
    code += f"{0*prefix} * @param u the vector on the left-hand side of the dot product.\n"
    code += f"{0*prefix} * @param v the vector on the right-hand side of the dot product.\n"
    code += f"{0*prefix} * @return the vector dot product u . v\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr T\n"
    else:
        code += f"{0*prefix}T\n"

    code += f"{0*prefix}dot(const Vector<T, {n}, REG_PREC>& u, const Vector<T, {n}, REG_PREC>& v) {{\n"

    c_str = sy.ccode(w)
    # Apply indexify to each variable
    for s in w.free_symbols:
        c_str = c_str.replace(str(s), vec_indexify(str(s)))

    code += f"{1*prefix}return {c_str};\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_cross_prod(n, arithmetic, prefix="  "):

    def generalized_cross_product(vectors):
        """
        Compute the (n−1)-dimensional cross-product in R^n using SymPy. vectors: list of (n−1)
        linearly independent n-dimensional vectors
        Returns: a single n-dimensional vector orthogonal to all of them
        """
        n = len(vectors[0])
        if len(vectors) != n - 1:
            raise ValueError("Need n-1 vectors in R^n")

        # Build n×n matrix by appending standard basis vectors to the input vectors
        standard_basis = [sy.eye(n).col(i) for i in range(n)]
        result = []

        id = sy.eye(n)

        for i in range(n):

            mat = sy.eye(n)

            # Form the matrix
            #   v0_0   v0_1   v0_2   ..  v0_n-1
            #   v1_0   v1_1   v1_2   ..  v1_n-1
            #    ..     ..     ..    ..    ..
            #   vn-2_0 vn-2_1 vn-2_2 ..  vn-2_n-1
            #   I_{i,:}

            # The first n-1 rows
            for ii in range(n-1):
                for jj in range(n):
                    mat[ii, jj] = vectors[ii][jj]

            # The last row (which is the ith row of the identity matrix)
            for ii in range(n):
                mat[n-1, ii] = id[i, ii]

            #mat = sy.Matrix(vectors + [standard_basis[i]])
            result.append(mat.det())

        return sy.Matrix(result)

    vectors = []
    for i in range(n-1):
        symbols = [sy.symbols(f"u{i}_{j}") for j in range(n)]
        vectors.append(sy.Matrix(symbols))

    v = generalized_cross_product(vectors)

    code = ""

    parameters = []
    for i in range(n-1):
        parameters.append(f"{0*prefix}const Vector<T, {n}, REG_PREC>& u{i}")

    comments = []
    for i in range(n-1):
        comments.append(f"{0*prefix} * @param u{i} the {i}th vector of the cross-product.")

    parameters_raw = []
    for i in range(n-1):
        parameters_raw.append(f"u{i}")

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector cross-product.\n"
    code += "\n".join(comments) + "\n"
    code += f"{0*prefix} * @return the vector cross-product " + " x ".join(parameters_raw) + ".\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector<T, {n}, REG_PREC>\n"
    else:
        code += f"{0*prefix}Vector<T, {n}, REG_PREC>\n"

    code += f"{0*prefix}cross({', '.join(parameters)}) {{\n"
    code += f"{1*prefix}Vector<T, {n}, REG_PREC> cross;\n"

    for i in range(n):
        expr = v[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable name
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
        code = code + f"{1*prefix}cross({i}) = {c_str};" + "\n"

    code += f"{1*prefix}return cross;\n"
    code += f"{0*prefix}}}"

    return code


def gen_vector_norm(n, arithmetic, prefix="  "):
    code = ""

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Vector norm.\n"
    code += f"{0*prefix} * @param u the vector for which we seek the norm/length.\n"
    code += f"{0*prefix} * @return the vector norm. v\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr T\n"
    else:
        code += f"{0*prefix}T\n"

    code += f"{0*prefix}norm(const Vector<T, {n}, REG_PREC>& u) {{\n"

    code += f"{1*prefix}return sqrt(dot(u,u));\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_rnorm(n, arithmetic, prefix="  "):
    code = ""

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Regularized vector norm.\n"
    code += f"{0*prefix} * @param u the vector for which we seek the regularlised norm/length.\n"
    code += f"{0*prefix} * @return the regularised vector norm. v\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr T\n"
    else:
        code += f"{0*prefix}T\n"

    code += f"{0*prefix}rnorm(const Vector<T, {n}, REG_PREC>& u) {{\n"

    code += f"{1*prefix}return sqrt(dot(u,u) + u.eps_squared);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_normalize(n, arithmetic, prefix="  "):
    code = ""

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Normalize a vector.\n"
    code += f"{0*prefix} * @param u the vector which we seek to normalize.\n"
    code += f"{0*prefix} * @return the normalized vector.\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector<T, {n}, REG_PREC>\n"
    else:
        code += f"{0*prefix}Vector<T, {n}, REG_PREC>\n"

    code += f"{0*prefix}normalize(const Vector<T, {n}, REG_PREC>& u) {{\n"

    code += f"{1*prefix}return u / norm(u);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_rnormalize(n, arithmetic, prefix="  "):
    code = ""

    # Generate C code
    code += f"{0*prefix}/**\n"
    code += f"{0*prefix} * Normalize (with regularization) a vector.\n"
    code += f"{0*prefix} * @param u the vector which we seek to normalize.\n"
    code += f"{0*prefix} * @return the normalized vector.\n"
    code += f"{0*prefix} */\n"

    code += f"{0*prefix}template <typename T, size_t REG_PREC,\n"

    if arithmetic:
        code += f"{0*prefix}          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>\n"
    else:
        code += f"{0*prefix}          std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>\n"

    if arithmetic:
        code += f"{0*prefix}constexpr Vector<T, {n}, REG_PREC>\n"
    else:
        code += f"{0*prefix}Vector<T, {n}, REG_PREC>\n"

    code += f"{0*prefix}rnormalize(const Vector<T, {n}, REG_PREC>& u) {{\n"

    code += f"{1*prefix}return u / rnorm(u);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_class(n, arithmetic=True, prefix="  "):
    code = ""

    code += f"{0*prefix}template <typename T, size_t REG_PREC>\n"
    code += f"{0*prefix}class Vector<T, {n}, REG_PREC, "

    if arithmetic:
        code += f"{0*prefix}std::enable_if_t<std::is_arithmetic_v<T>>> {{"
    else:
        code += f"{0*prefix}std::enable_if_t<!std::is_arithmetic_v<T>>> {{"

    code += "\n\n"

    if arithmetic:
        code += f'{1*prefix}// Make sure T is an arithmetic type otherwise fail to compile.\n'
        code += f'{1*prefix}static_assert(\n'
        code += f'{2*prefix}std::is_arithmetic_v<T>,\n'
        code += f'{2*prefix}"T must be an arithmetic type (int, float, double...)"\n'
        code += f'{1*prefix});'

        code += "\n\n"

    code += f"{0*prefix}public:\n"

    code += textwrap.indent(gen_vector_default_constructor(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_initializer_constructor(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_access(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_const_access(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_array_access(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_array_const_access(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_assign(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_vector_sum(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_vector_difference(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_negation(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_scalar_vector_prod(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_scalar_prod(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_scalar_div(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_inplace_sum(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_inplace_difference(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_scalar_inplace_product(n, arithmetic), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_vector_scalar_inplace_division(n, arithmetic), prefix=prefix)

    code += "\n\n"

    if arithmetic:
        code += f"{1*prefix}const T eps = RegularizationEps<T, REG_PREC>::value();\n"
        code += f"{1*prefix}const T eps_squared = eps * eps;\n"
    else:
        code += f"{1*prefix}const T eps = RegularizationEps<T, REG_PREC>::value();\n"
        code += f"{1*prefix}const T eps_squared = eps * eps;\n"

    code += "\n"

    code += f"{0*prefix}private:\n"
    code += f"{1*prefix}std::array<T, {n}> data_{{}};\n"

    code += f"{0*prefix}}};"

    code += "\n\n"

    code += gen_vector_dot_prod(n, arithmetic)

    code += "\n\n"

    code += gen_vector_cross_prod(n, arithmetic)

    code += "\n\n"

    code += gen_vector_norm(n, arithmetic)

    code += "\n\n"

    code += gen_vector_rnorm(n, arithmetic)

    code += "\n\n"

    code += gen_vector_normalize(n, arithmetic)

    code += "\n\n"

    code += gen_vector_rnormalize(n, arithmetic)

    return code


if __name__ == "__main__":
    dim = 2
    prefix = "  "
    print(gen_includes())

    print(f"{0*prefix}/*" + 95*"-" + "*/")
    print(f"{0*prefix}/* Regularization class" + 74 * " " + "*/")
    print(f"{0*prefix}/*" + 95*"-" + "*/\n\n")

    print(gen_regularization())

    print(f"{0*prefix}/*" + 95*"-" + "*/")
    print(f"{0*prefix}/* Primary class declaration" + 69 * " " + "*/")
    print(f"{0*prefix}/*" + 95*"-" + "*/\n\n")

    print(gen_vector_class_primary())

    print(f"{0*prefix}/*" + 95*"-" + "*/")
    print(f"{0*prefix}/* Constexpr class for arithmetic types" + 58 * " " + "*/")
    print(f"{0*prefix}/*" + 95*"-" + "*/\n\n")

    print(gen_vector_class(dim, arithmetic=True))

    print("\n")
    print(f"{0*prefix}/*" + 95*"-" + "*/")
    print(f"{0*prefix}/* Class for general types" + 71 * " " + "*/")
    print(f"{0*prefix}/*" + 95*"-" + "*/\n\n")

    print(gen_vector_class(dim, arithmetic=False))
