#
# This is a code to generate tests for the linear algebra library for small dense matrices.
#

import re
import textwrap
import sys

import sympy as sy

from random import randint


def gen_includes():
    code = ""

    code += "#define CATCH_CONFIG_MAIN\n"
    code += "#include <catch/catch.hpp>\n"
    code += "#include <mpreal.h>"

    code += "\n\n"

    code += "#include \"linalg_vector.hpp\""

    code += "\n"

    return code


def gen_initializer_list_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test list initializer list \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u = {{{', '.join(str(u[i]) for i in range(n))}}};\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(u({i}) - {u[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_sum_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector addition for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    v = sy.Matrix([randint(1, 10) for i in range(n)])

    w = u + v

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v, w;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    for i in range(n):
        code += f"{1*prefix}v({i}) = {v[i]};\n"

    code += f"{1*prefix}w = u + v;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(w({i}) - {w[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_difference_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector difference for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    v = sy.Matrix([randint(1, 10) for i in range(n)])

    w = u - v

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v, w;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    for i in range(n):
        code += f"{1*prefix}v({i}) = {v[i]};\n"

    code += f"{1*prefix}w = u -v;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(w({i}) - {w[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_multiplication_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar product for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    alpha = randint(1, 10)

    v = u * alpha

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"
    code += f"{1*prefix}{data_type} alpha = {alpha};\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}v = u * alpha;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(v({i}) - {v[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_scalar_vector_multiplication_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test scalar-vector product for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    alpha = randint(1, 10)

    v = alpha * u

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"
    code += f"{1*prefix}{data_type} alpha = {alpha};\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}v = alpha * u;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(v({i}) - {v[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_division_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar division for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    alpha = randint(1, 10)

    v = u / alpha

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"
    code += f"{1*prefix}{data_type} alpha = {alpha};\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}v = u / alpha;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(v({i}) - {v[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_sum_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar inplace sum for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    v = sy.Matrix([randint(1, 10) for i in range(n)])

    w = u + v

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"
        code += f"{1*prefix}v({i}) = {v[i]};\n"

    code += f"{1*prefix}u += v;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(u({i}) - {w[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_difference_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar inplace difference for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    v = sy.Matrix([randint(1, 10) for i in range(n)])

    w = u - v

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"
        code += f"{1*prefix}v({i}) = {v[i]};\n"

    code += f"{1*prefix}u -= v;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(u({i}) - {w[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_product_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar inplace product for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    alpha = randint(1, 10)

    w = u * alpha

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}{data_type} alpha = {alpha};\n"

    code += f"{1*prefix}u *= alpha;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(u({i}) - {w[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_scalar_inplace_division_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector-scalar inplace division for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    alpha = randint(1, 10)

    w = u / alpha

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}{data_type} alpha = {alpha};\n"

    code += f"{1*prefix}u /= alpha;\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(u({i}) - {w[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_dot_product_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector dot product for \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])
    v = sy.Matrix([randint(1, 10) for i in range(n)])

    w = u.dot(v)

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u, v;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    for i in range(n):
        code += f"{1*prefix}v({i}) = {v[i]};\n"

    code += f"{1*prefix}{data_type} w = dot(u, v);\n"

    code += f"{1*prefix}REQUIRE(abs(w - {w.evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_cross_product_test(n, data_type, prefix):

    def reference_cross_product(vectors):
        """
        Computes the generalised cross-product in R^n by taking the Hodge dual of the wedge product
        of n-1 vectors. This returns a vector in R^n.
        """
        n = len(vectors[0])
        if len(vectors) != n - 1:
            raise ValueError("Expected n-1 vectors in R^n")

        if n == 2:
            # Special case: rotate (x, y) -> (-y, x) for CCW perp
            x, y = vectors[0]
            return sy.Matrix([-y, x])

        # Construct standard-basis
        basis = [sy.Matrix([int(i == j) for i in range(n)]) for j in range(n)]

        dual = []
        for i in range(n):
            # Insert basis[i] as column i
            mtx = sy.Matrix.hstack(*vectors[:i], basis[i], *vectors[i:])
            cofactor = (-1)**i * mtx.det()
            dual.append(cofactor)

        return sy.Matrix(dual)

    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector cross product for \'{data_type}\'", "Vector") {{\n'

    # We generate n-1 vectors for the cross-product, where n is the number of components
    vectors = []
    for i in range(n-1):
        vectors.append(sy.Matrix([randint(1, 10) for i in range(n)]))

    # Build an n x n matrix by appending the standard basis

    result = reference_cross_product(vectors)

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    # Generate the vectors that will participate in the cross-product
    vars = [f"u{i}" for i in range(n-1)]
    for i in range(n-1):
        code += f"{1*prefix}Vector<{data_type}, {n}> {vars[i]};\n"
        for j in range(n):
            code += f"{1*prefix}{vars[i]}({j}) = {vectors[i][j]};\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> result = cross({', '.join(vars)});\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(result({i}) - {result[i]}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_norm_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector norm \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])

    v = sy.sqrt(u.dot(u))

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}{data_type} w = norm(u);\n"

    code += f"{1*prefix}REQUIRE(abs(w - {v.evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_rnorm_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector rnorm \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])

    v = sy.sqrt(u.dot(u) + 1E-4)

    code += f"{1*prefix}{data_type} eps(1E-12);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}, 2> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}{data_type} w = rnorm(u);\n"

    code += f"{1*prefix}REQUIRE(abs(w - {v.evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_normalize_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector normalize \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])

    v = u / sy.sqrt(u.dot(u))

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}Vector v = normalize(u);\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(v({i}) - {v[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_rnormalize_test(n, data_type, prefix):
    code = ""

    code += f'{0*prefix}TEST_CASE("Test vector rnormalize \'{data_type}\'", "Vector") {{\n'

    u = sy.Matrix([randint(1, 10) for i in range(n)])

    v = u / sy.sqrt(u.dot(u) + 1e-4)

    code += f"{1*prefix}{data_type} eps(1E-7);\n"

    code += f"{1*prefix}Vector<{data_type}, {n}, 2> u;\n"

    for i in range(n):
        code += f"{1*prefix}u({i}) = {u[i]};\n"

    code += f"{1*prefix}Vector v = rnormalize(u);\n"

    for i in range(n):
        code += f"{1*prefix}REQUIRE(abs(v({i}) - {v[i].evalf()}) < eps);\n"

    code += f"{0*prefix}}}"

    return code


def gen_vector_tests(n, data_type, prefix="  "):
    code = ""

    code += gen_initializer_list_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_sum_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_difference_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_multiplication_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_scalar_vector_multiplication_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_division_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_inplace_sum_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_inplace_difference_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_inplace_product_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_scalar_inplace_division_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_dot_product_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_cross_product_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_norm_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_rnorm_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_normalize_test(n, data_type, prefix)

    code += "\n\n"

    code += gen_vector_rnormalize_test(n, data_type, prefix)

    return code


if __name__ == "__main__":
    dim = 2
    print(gen_includes())
    print(gen_vector_tests(dim, 'mpfr::mpreal'))
    print("")
    print(gen_vector_tests(dim, 'double'))
