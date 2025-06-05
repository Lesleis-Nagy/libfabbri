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

    code += "#include <array>\n"
    code += "#include <cstddef>"

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
# Matrix generation                                                                              #
##################################################################################################


def gen_matrix_access(n, prefix="  "):
    code = ""

    code += f"/**\n"
    code += f" * Matrix element access.\n"
    code += f" * @param i the i-th (row) matrix index.\n"
    code += f" * @param j the j-th (column) matrix index.\n"
    code += f" * @return the matrix element at index (row) i, (column) j.\n"
    code += f" */\n"

    code += f"constexpr T&\n"
    code += f"operator()(size_t i, size_t j) {{\n"
    code += f"{prefix}return data_[i][j];\n"
    code += f"}}"

    return code


def gen_matrix_access_const(n, prefix="  "):
    code = ""

    code += f"/**\n"
    code += f" * Constant matrix element access.\n"
    code += f" * @param i the i-th (row) matrix index.\n"
    code += f" * @param j the j-th (column) matrix index.\n"
    code += f" * @return the matrix element at index (row) i, (column) j as an unchangeable value.\n"
    code += f" */\n"

    code += f"constexpr const T&\n"
    code += f"operator()(size_t i, size_t j) const {{\n"
    code += f"{prefix} return data_[i][j];\n"
    code += f"}}"

    return code


def gen_matrix_matrix_sum(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    B = sy.Matrix(n, n, lambda i, j: sy.symbols(f"B_{i}_{j}"))

    C = A + B

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-matrix sum operator.\n"
    code += f" * @param A the matrix on the left hand side of the sum.\n"
    code += f" * @param B the matrix on the right hand side of the sum.\n"
    code += f" * @return the matrix sum A + B.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator+(const Matrix<T, {n}>& A, const Matrix<T, {n}>& B) {{\n"
    code += f"{prefix}Matrix<T, {n}> C;\n"

    for i in range(n):
        for j in range(n):
            expr = C[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}C({i}, {j}) = {c_str};\n"

    code += f"{prefix}return C;\n"

    code += f"}}"

    return code


def gen_matrix_matrix_difference(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    B = sy.Matrix(n, n, lambda i, j: sy.symbols(f"B_{i}_{j}"))

    C = A - B

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-matrix difference operator.\n"
    code += f" * @param A the matrix on the left hand side of the difference.\n"
    code += f" * @param B the matrix on the right hand side of the difference.\n"
    code += f" * @return the matrix difference A - B.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator-(const Matrix<T, {n}>& A, const Matrix<T, {n}>& B) {{\n"
    code += f"{prefix}Matrix<T, {n}> C;\n"

    for i in range(n):
        for j in range(n):
            expr = C[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}C({i}, {j}) = {c_str};\n"

    code += f"{prefix}return C;\n"

    code += f"}}"

    return code


def gen_matrix_negation(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))

    B = -A

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix negation operator.\n"
    code += f" * @param A the matrix to negate.\n"
    code += f" * @return the matrix negation -A.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator-(const Matrix<T, {n}>& A) {{\n"
    code += f"{prefix}Matrix<T, {n}> B;\n"

    for i in range(n):
        for j in range(n):
            expr = B[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}B({i}, {j}) = {c_str};\n"

    code += f"{prefix}return B;\n"

    code += f"}}"

    return code


def gen_scalar_matrix_prod(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    alpha = sy.symbols('alpha')

    B = alpha * A

    # Generate C code
    code += f"/**\n"
    code += f" * Scalar-matrix product operator.\n"
    code += f" * @param alpha the scalar on the left hand side of the product.\n"
    code += f" * @param A the matrix on the right hand side of the product.\n"
    code += f" * @return the scalar-matrix product alpha*A.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator*(T alpha, const Matrix<T, {n}>& A) {{\n"
    code += f"{prefix}Matrix<T, {n}> B;\n"

    for i in range(n):
        for j in range(n):
            expr = B[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}B({i}, {j}) = {c_str};\n"

    code += f"{prefix}return B;\n"

    code += f"}}"

    return code


def gen_matrix_scalar_prod(n, prefix="  "):
    code = ""

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-scalar product operator.\n"
    code += f" * @param A the matrix on the left hand side of the product.\n"
    code += f" * @param alpha the scalar on the right hand side of the product.\n"
    code += f" * @return the matrix-scalar product A*alpha.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator*(const Matrix<T, {n}>& A, T alpha) {{\n"
    code += f"{prefix}Matrix<T, {n}> B;\n"

    code += f"{prefix}return alpha * A;\n"

    code += f"}}"

    return code


def gen_matrix_scalar_div(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    alpha = sy.symbols('alpha')

    B = A / alpha

    # Generate C code
    code += f"/**\n"
    code += f" * Scalar-matrix division operator.\n"
    code += f" * @param A the matrix on the left hand side of the division.\n"
    code += f" * @param alpha the scalar on the right hand side of the division.\n"
    code += f" * @return the matrix-scalar division A/alpha.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator/(const Matrix<T, {n}>& A, T alpha) {{\n"
    code += f"{prefix}Matrix<T, {n}> B;\n"

    for i in range(n):
        for j in range(n):
            expr = B[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}B({i}, {j}) = {c_str};\n"

    code += f"{prefix}return B;\n"

    code += f"}}"

    return code


def gen_matrix_matrix_prod(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    B = sy.Matrix(n, n, lambda i, j: sy.symbols(f"B_{i}_{j}"))

    C = A * B

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-matrix product operator.\n"
    code += f" * @param A the matrix on the left hand side of the product.\n"
    code += f" * @param B the matrix on the right hand side of the product.\n"
    code += f" * @return the matrix product AB.\n"
    code += f" */\n"

    code += f"friend constexpr Matrix<T, {n}>\n"
    code += f"operator*(const Matrix<T, {n}>& A, const Matrix<T, {n}>& B) {{\n"
    code += f"{prefix}Matrix<T, {n}> C;\n"

    for i in range(n):
        for j in range(n):
            expr = C[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code += f"{prefix}C({i}, {j}) = {c_str};\n"

    code += f"{prefix}return C;\n"

    code += f"}}"

    return code


def gen_matrix_vector_prod(n, prefix="  "):
    code = ""

    A = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))
    x = sy.Matrix(n, 1, lambda i, j: sy.symbols(f"x_{i}"))

    y = A * x

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-vector product operator.\n"
    code += f" * @param A the matrix on the left hand side of the product.\n"
    code += f" * @param x the vector on the right hand side of the product.\n"
    code += f" * @return the matrix-vector product Ax.\n"
    code += f" */\n"

    code += f"friend constexpr Vector<T, {n}>\n"
    code += f"operator*(const Matrix<T, {n}>& A, const Vector<T, {n}>& x) {{\n"
    code += f"{prefix}Vector<T, {n}> y;\n"

    for i in range(n):
        expr = y[i]
        c_str = sy.ccode(expr)
        # Apply indexify to each variable
        for s in expr.free_symbols:
            c_str = c_str.replace(str(s), vec_indexify(str(s)))
            c_str = c_str.replace(str(s), mat_indexify(str(s)))
        code += f"{prefix}y({i}) = {c_str};\n"

    code += f"{prefix}return y;\n"

    code += f"}}"

    return code


def gen_matrix_minor(n, prefix="  "):
    code = ""

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix-minor function.\n"
    code += f" * @param i the i-th row to remove from the matrix.\n"
    code += f" * @param j the j-th column to remove from the matrix.\n"
    code += f" * @return the minor matrix, i.e. this matrix but with row i and column j removed.\n"
    code += f" */\n"

    code += f"constexpr Matrix<T, {n-1}>\n"
    code += f"minor(const size_t i, const size_t j) const {{\n"
    code += f"{prefix}Matrix<T, {n-1}> result;\n"
    code += f"{prefix}size_t r = 0;\n"
    code += f"{prefix}for (size_t ii = 0; ii < {n}; ++ii) {{\n"
    code += f"{2*prefix}if (ii == i) continue;\n"
    code += f"{2*prefix}size_t c = 0;\n"
    code += f"{2*prefix}for (size_t jj = 0; jj < {n}; ++jj) {{\n"
    code += f"{3*prefix}if (jj == j) continue;\n"
    code += f"{3*prefix}result(r, c) = data_[ii][jj];\n"
    code += f"{3*prefix}++c;\n"
    code += f"{2*prefix}}}\n"
    code += f"{2*prefix}++r;\n"
    code += f"{prefix}}}\n"
    code += f"{prefix}return result;\n"
    code += f"}}"

    return code


def gen_matrix_adj(n, prefix="  "):
    code = ""

    a = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))

    # Now compute the adjugate (classical adjoint)
    adj = a.adjugate()

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix adjugate.\n"
    code += f" * @param A the matrix for which we seek the adjugate.\n"
    code += f" * @return the matrix adjugate.\n"
    code += f" */\n"

    code += f"template <typename T>\n"
    code += f"constexpr Matrix<T, {n}>\n"
    code += f"adj(const Matrix<T, {n}>& A) {{\n"
    code += f"{prefix}Matrix<T, {n}> adj;\n"

    for i in range(n):
        for j in range(n):
            expr = adj[i, j]
            c_str = sy.ccode(expr)
            # Apply indexify to each variable name
            for s in expr.free_symbols:
                c_str = c_str.replace(str(s), mat_indexify(str(s)))
            code = code + f"{prefix}adj({i}, {j}) = {c_str};" + "\n"

    code += f"{prefix}return adj;\n"
    code += f"}}"

    return code


def gen_matrix_det(n, prefix="  "):
    code = ""

    a = sy.Matrix(n, n, lambda i, j: sy.symbols(f"A_{i}_{j}"))

    # Now compute the determinant.
    det = a.det()

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix determinant.\n"
    code += f" * @param A the matrix for which we seek the determinant.\n"
    code += f" * @return the matrix determinant.\n"
    code += f" */\n"

    code += f"template <typename T>\n"
    code += f"constexpr T\n"
    code += f"det(const Matrix<T, {n}>& A) {{\n"

    c_str = sy.ccode(det)
    # Apply indexify to each variable name
    for s in det.free_symbols:
        c_str = c_str.replace(str(s), mat_indexify(str(s)))
    # code = code + f"{prefix}adj[{i}][{j}] = {c_str};" + "\n"
    #
    code += f"{prefix}return {c_str};\n"
    code += f"}}"

    return code


def gen_matrix_inv(n, prefix="  "):
    code = ""

    # Generate C code
    code += f"/**\n"
    code += f" * Matrix inverse.\n"
    code += f" * @param A the matrix for which we seek the inverse.\n"
    code += f" * @return the matrix inverse.\n"
    code += f" */\n"

    code += f"template <typename T>\n"
    code += f"constexpr Matrix<T, {n}>\n"
    code += f"inv(const Matrix<T, {n}>& A) {{\n"

    code += f"{prefix}return adj(A) / det(A);\n"

    code += f"}}"

    return code


def gen_matrix_default_constructor(n, prefix="  "):
    code = ""

    # The default constructor creates the unit matrix
    code += f"/**\n"
    code += f" * Default constructor generates the {n} x {n} unit matrix.\n"
    code += f" */\n"

    code += f"constexpr Matrix() {{\n"
    code += f"{1*prefix}for(size_t i = 0; i < {n}; ++i)\n"
    code += f"{2*prefix}for(size_t j = 0; j < {n}; ++j)\n"
    code += f"{3*prefix}data_[i][j] = (i == j ? T(1) : T(0));\n"
    code += f"}}"

    return code


def gen_matrix_class(n, prefix="  "):
    code = ""

    code += f"template <typename T>\n"
    code += f"class Matrix<T, {n}> {{\n"

    code += f"public:\n"

    code += textwrap.indent(gen_matrix_default_constructor(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_access(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_access_const(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_matrix_sum(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_matrix_difference(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_negation(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_scalar_matrix_prod(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_scalar_prod(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_scalar_div(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_matrix_prod(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_vector_prod(n), prefix=prefix)

    code += "\n\n"

    code += textwrap.indent(gen_matrix_minor(n), prefix=prefix)

    code += "\n\n"

    code += f"private:\n"
    code += f"{prefix}std::array<std::array<T, {n}>, {n}> data_{{}};\n"

    code += f"}};"

    code += "\n\n"

    code += gen_matrix_adj(n)

    code += "\n\n"

    code += gen_matrix_det(n)

    code += "\n\n"

    code += gen_matrix_inv(n)

    return code
