#!/usr/bin/env python

from sympy.vector import CoordSys3D
from sympy import *

import numpy as np
import matplotlib.pyplot as plt

import h5py

C = CoordSys3D("C")

eps = symbols("eps")

x, y, z = symbols("rx ry rz")
xp, yp, zp = symbols("xp yp zp")


def d(r1, r2):
    return sqrt((r1 - r2).dot(r1 - r2) + eps**2)


def we_fun(r1, r2):
    def we(r):
        return log( ( d(r1, r) + d(r2, r) + d(r2, r1) ) / ( d(r1, r) + d(r2, r) - d(r2, r1) ) )
    return we

def generate_we_test_data():

    r1x, r1y, r1z = symbols("r1x r1y r1z")
    r2x, r2y, r2z = symbols("r2x r2y r2z")
    rx, ry, rz = symbols("rx ry rz")

    r1 = r1x*C.i + r1y*C.j + r1z*C.k
    r2 = r2x*C.i + r2y*C.j + r2z*C.k
    r = rx*C.i + ry*C.j + rz*C.k

    we = we_fun(r1, r2)

    expr = we(r)
    print(latex(expr))

    result = expr.evalf(20, subs={r1x:0.0, r1y:0.0, r1z:0.0,
                                  r2x:1.0, r2y:0.0, r2z:0.0,
                                  rx:0.5, ry:0.0, rz:0.0,
                                  eps:1E-10})

    n = 10
    xlist = np.linspace(-2.0, 2.0, n)
    ylist = np.linspace(-2.0, 2.0, n)
    X, Y = np.meshgrid(xlist, ylist)
    Z = np.zeros((n, n))

    expr = we(r).evalf(20).subs({r1x:-1.0, r1y: 0.0, r1z:0.0,
                                 r2x: 1.0, r2y: 0.0, r2z:0.0,
                                 rz:0.0, eps:1E-10})

    for i in range(n):
        for j in range(n):
            x = X[i,j]
            y = Y[i,j]
            z = expr.evalf(20).subs({rx:x, ry:y})
            Z[i,j] = z

    hf = h5py.File("we.h5", "w")

    hf.create_dataset("x", data=X)
    hf.create_dataset("y", data=Y)
    hf.create_dataset("z", data=Z)

    hf.close()

    print("x:")
    print(X)

    print("y:")
    print(Y)

    print("z:")
    print(Z)


if __name__ == "__main__":

    generate_we_test_data()

